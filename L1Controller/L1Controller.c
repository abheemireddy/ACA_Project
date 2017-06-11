#include "Queue/Queue.h"
#include "L1Controller.h"
#include "Global_Variables.h"
#include "Cache/Cache.h"

L1Controller* Constructor_L1Controller(){
    L1Controller* l1Controller = malloc(sizeof(l1Controller));
    l1Controller->cache = Constructor_Cache(64);
    l1Controller->transferer = Constructor_Transferer();
    l1Controller->waiting = false;
    l1Controller->dataFromL2 = NULL;
    return l1Controller;
}

void CheckSetSize(Set* set){
    int countInSet = Count(&set->HashTable);
    if(countInSet >= 4){
        SortHash(&set->HashTable);
        Block* leastUsed = GetLeastUsed(&set->HashTable);
        removeFromTable(&set->HashTable,leastUsed);
        if(leastUsed->dirtyBit == true){
            putBlockInBuffer(&l1WriteBuffer->HashTable,leastUsed);
        }else{
            putBlockInBuffer(&l1VictimCache->HashTable,leastUsed);
        }
    }
}

void PutInWriteBuffer(Block* existing){
    if(CountBlocksInBuffer(&l1VictimCache->HashTable) >= 2){
        WriteBackToL2(&l1VictimCache->HashTable);
    }
    putBlockInBuffer(&l1VictimCache->HashTable,existing);
}

void PutInVictimCache(Block* existing){
    if(CountBlocksInBuffer(&l1WriteBuffer->HashTable) >= 5){
        WriteBackToL2(&l1WriteBuffer->HashTable);
    }
    putBlockInBuffer(&l1VictimCache->HashTable,existing);
}

void SetL1ControllerData(){
    Block* toStore = l1Controller->dataFromL2;
    Set* set = l1Controller->cache->getSetByIndex(&l1Controller->cache->HashTable,toStore->address.Index);
    Block* existing = get(&set->HashTable,toStore->address.Tag);
    if(existing != NULL){
        if(existing->dirtyBit == false){
            PutInWriteBuffer(existing);
        }else{
            PutInVictimCache(existing);
        }
    }
    CheckSetSize(set);
    put(&set->HashTable,toStore);
}

void L1ProcessInstruction(Instruction instruction){
    if(instruction.instruction == 1){
        L1_write(instruction,instruction.data);
    }else if(instruction.instruction == 2){
        L1_read(instruction);
    }
}

void WriteToBlock(Block* existing,Instruction instruction,char value[64]){
    CacheLine* toWriteTo = getCacheLineByOffset(&existing->HashTable,instruction.address.Offset);
    strcpy(toWriteTo->data,value);
    existing->dirtyBit = true;
    printf("Wrote to set:%s\n",toWriteTo->data);
    Dequeue(l1Controller->transferer->TransferQueue);
}
void CheckVictimCacheAndWriteBuffer(Block* existing,Instruction instruction,char value[64]){
    Block* victimBlock = getBlockFromBuffer(&l1VictimCache->HashTable,instruction.address.bitStringValue);
    Block* writeBlock = getBlockFromBuffer(&l1WriteBuffer->HashTable,instruction.address.bitStringValue);
    if(victimBlock == NULL && writeBlock == NULL){
        Enqueue(l2Controller->transferer->TransferQueue,instruction);
        l1Controller->waiting = true;
    }else{
        if(victimBlock != NULL){
            CacheLine* victimCacheLine = getCacheLineByOffset(&victimBlock->HashTable,instruction.address.Offset);
            strcpy(victimCacheLine->data,value);
            existing->dirtyBit = true;
            existing->isIdle = false;
        }else if(writeBlock != NULL){
            CacheLine* writeBufferCacheLine = getCacheLineByOffset(&victimBlock->HashTable,instruction.address.Offset);
            strcpy(writeBufferCacheLine->data,value);
            existing->dirtyBit = true;
            existing->isIdle = false;
        }
    }
}
void L1_write(Instruction instruction, char value[64])
{
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,instruction.address.Index);
    Block* existing = get(&set->HashTable,instruction.address.Tag);
    if(existing != NULL){
        WriteToBlock(existing,instruction,value);
    }else{
        CheckVictimCacheAndWriteBuffer(existing,instruction,value);
    }
	/*printf("P to L1C: CPUWrite (%d)\n", address.bitStringValue);
	// check if address is valid
	if (!L1Data[address.Index].valid) // block not valid
	{
		printf("L1C to L1D: Data\n");
		printf("Hit\n");
		L1Data[address.Index].data[address.Offset] = (unsigned char)value;
		L1Data[address.Index].valid = 1;
		L1Data[address.Index].dirty = 1;
		L1Data[address.Index].tag = address.Tag;
	}
	else if (L1Data[address.Index].valid && L1Data[address.Index].tag == address.Tag)
	{
		printf("L1C to L1D: Data\n");
		printf("Hit\n");
		L1Data[address.Index].data[address.Offset] = (unsigned char)value;
		L1Data[address.Index].dirty = 1;
	}
	else if (L1Data[address.Index].valid && L1Data[address.Index].tag != address.Tag) // not in Cache!
	{
		// check if dirty, we need to writeback
		if (L1Data[address.Index].dirty)
		{
			printf("L1C to L2D: CPUWrite\n");
			l2Write(address, value);
		}
		printf("L1C to L2C: CPURead\n");
		L1Data[address.Index].dirty = 0;
		L1Data[address.Index].tag = address.Tag;
		//TODO : push the given address to read queue
		l2Read(address, L1Data[address.Index].data);  // get data from L2
		printf("L2C to L1C: Data\n");

	}*/
}

CacheLine* L1_read(Instruction instruction)
{
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,instruction.address.Index);
    Block* block = get(&set->HashTable,instruction.address.Tag);
    if(block != NULL){
        if(block->validBit == true){
            CacheLine* cacheLine = getCacheLineByOffset(&block->HashTable,instruction.address.Offset);
            return cacheLine;
        }else{
            block = NULL;
        }
    }
	if (block == NULL) {
        //check victim and write buffer
        Block *victimBlock = getBlockFromBuffer(&l1VictimCache->HashTable, instruction.address.bitStringValue);
        Block *writeBlock = getBlockFromBuffer(&l1WriteBuffer->HashTable, instruction.address.bitStringValue);
        if (victimBlock == NULL && writeBlock == NULL) {
            Enqueue(l2Controller->transferer->TransferQueue, instruction);
            l1Controller->waiting = true;
            return NULL;
        } else {
            if (victimBlock != NULL) {
                CacheLine *victimCacheLine = getCacheLineByOffset(&victimBlock->HashTable, instruction.address.Offset);
                if (CountBlocksInBuffer(&l1VictimCache->HashTable) >= 2) {
                    WriteBackToL2(&l1VictimCache->HashTable);
                }
                return victimCacheLine;
            } else if (writeBlock != NULL) {
                CacheLine *writeBufferCacheLine = getCacheLineByOffset(&victimBlock->HashTable,
                                                                       instruction.address.Offset);
                if (CountBlocksInBuffer(&l1WriteBuffer->HashTable) >= 5) {
                    WriteBackToL2(&l1WriteBuffer->HashTable);
                }
                return writeBufferCacheLine;
            }
        }
    }
    /*
	else if (L1Data[address.Index].valid && L1Data[address.Index].tag != address.Tag) // reading from a different tag
	{
		// first we need to send the block to the victim cache
		int vaddress = (L1Data[address.Index].tag << 14) | address.Index << 6; // starting address of current stored block

		//TODO:  send the block to the victim cache

		if (L1Data[address.Index].dirty) // dirty... we need to writeback the block
		{
			printf("L1C to L2C: Data (Writeback)\n");
			//int wbAddress = (L1Data[address.Index].tag << 14) | address.Index << 6;
			l2WriteBack(address, L1Data[address.Index].data);
		}

		// first check if the block is in victim cache and then get victim cache data to block
		//TODO: check if the block is in victim cache
		int checkAddress(int address)
		{
			return 1; //check if the block is in victim cache if so return 1
						//else return 0;
		}

		if (checkAddress(address.bitStringValue))
		{
			L1Data[address.Index].dirty = 0;
			L1Data[address.Index].tag = address.Tag;
			printf("L1C to Victim: CPURead (%d)\n", address.bitStringValue);
			//TODO:get victim cache data to block
		}
		else // block not in victim cache
		{
			L1Data[address.Index].dirty = 0;
			L1Data[address.Index].tag = address.Tag;
			printf("L1C to L2C: CPURead (%d)\n", address.bitStringValue);
			// TODO: push the given address into the read queue of L2
			l2Read(address, L1Data[address.Index].data);  // get data from L2
			printf("L2C to L1C: Data\n");
		}
		return L1Data[address.Index].data[address.Offset];

	}*/

	return NULL;
}
