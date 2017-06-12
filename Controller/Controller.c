#include "Address/Address.h"
#include "BlockTransferer/BlockTransferer.h"
#include "Controller.h"
#include "CacheLine/CacheLine.h"
#include "Block_Queue/Block_Queue.h"
#include "Queue/Queue.h"
#include "Global_Variables.h"
#include "Cache/Cache.h"
#include "Set/Set.h"

void CheckBufferSize();
void PutInWriteBuffer(Block* existing);
void PutInVictimCache(Block* existing);

Controller* Constructor_L1Controller(){
    Controller* l1ControllerCon = malloc(sizeof(l1ControllerCon));
    l1ControllerCon->blockQueue = Constructor_BlockQueue();
    l1ControllerCon->cache = Constructor_Cache(64);
    l1ControllerCon->transferer = Constructor_Transferer();
    l1ControllerCon->waiting = false;
    return l1ControllerCon;
}

Controller* Constructor_L2Controller(){
    Controller* l2ControllerCon = malloc(sizeof(l2ControllerCon));
    l2ControllerCon->cache = Constructor_Cache(256);
    l2ControllerCon->transferer = Constructor_Transferer();
    l2ControllerCon->waiting = false;
    return l2ControllerCon;
}

void CheckSetSize(Set* set){
    int countInSet = Count(&set->HashTable);
    if(countInSet >= 4){
        SortHash(&set->HashTable);
        Block* leastUsed = GetLeastUsed(&set->HashTable);
        removeFromTable(&set->HashTable,leastUsed);
        if(leastUsed->dirtyBit == true){
            PutInWriteBuffer(leastUsed);
        }else{
            PutInVictimCache(leastUsed);
        }
    }
    CheckBufferSize();
}
void CheckBufferSize(){
    int victimCacheCount = CountBlocksInBuffer(&l1VictimCache->HashTable);
    int writeBufferCount = CountBlocksInBuffer(&l1WriteBuffer->HashTable);
    if(victimCacheCount >= 2){
        WriteBackToL2(l1VictimCache,&l1VictimCache->HashTable);
    }
    if(writeBufferCount >= 5){
        WriteBackToL2(l1WriteBuffer,&l1WriteBuffer->HashTable);
    }
}

void PutInWriteBuffer(Block* existing){
    if(CountBlocksInBuffer(&l1WriteBuffer->HashTable) >= 2){
        WriteBackToL2(l1WriteBuffer,&l1WriteBuffer->HashTable);
    }
    putBlockInBuffer(&l1WriteBuffer->HashTable,existing);
}

void PutInVictimCache(Block* existing){
    if(CountBlocksInBuffer(&l1VictimCache->HashTable) >= 5){
        WriteBackToL2(l1VictimCache,&l1VictimCache->HashTable);
    }
    putBlockInBuffer(&l1VictimCache->HashTable,existing);
}

void WriteBlockToL1Controller(Block toStore){
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,toStore.address.Index);
    Block* existing = get(&set->HashTable,toStore.address.Tag);
    if(existing != NULL){
        if(existing->dirtyBit == false){
            PutInWriteBuffer(existing);
        }else{
            PutInVictimCache(existing);
        }
    }
    CheckSetSize(set);
    put(&set->HashTable,&toStore);
}

CacheLine* ProcessL1Instruction(Instruction instruction){
    if(instruction.instruction == 1){
        WriteToController(instruction,instruction.data);
        return NULL;
    }else if(instruction.instruction == 2){
        CacheLine* cacheLineRead =  L1_read(instruction);
        return cacheLineRead;
    }
}

void WriteToBlock(Block* existing,Instruction instruction,char value[64]){
    CacheLine* toWriteTo = getCacheLineByOffset(&existing->HashTable,instruction.address.Offset);
    if(toWriteTo == NULL){
        CacheLine* cacheLine = Constructor_CacheLine(instruction.address,value);
        putCacheLine(&existing->HashTable,cacheLine);
        toWriteTo = getCacheLineByOffset(&existing->HashTable,instruction.address.Offset);
    }
    toWriteTo->dataLine = StoreData(l1Data,value);
    existing->dirtyBit = true;
    existing->validBit = true;
    printf("Wrote to set:%d val:%s\n",toWriteTo->address.bitStringValue,GetData(l1Data,toWriteTo->dataLine));
    Dequeue(l1Controller->transferer->TransferQueue);
}

bool CheckVictimCacheAndWriteBuffer(Instruction instruction,char value[64]){
    Block* victimBlock = getBlockFromBuffer(&l1VictimCache->HashTable,instruction.address.bitStringValue);
    Block* writeBlock = getBlockFromBuffer(&l1WriteBuffer->HashTable,instruction.address.bitStringValue);
    if(victimBlock == NULL && writeBlock == NULL){
        Enqueue(l2Controller->transferer->TransferQueue,instruction);
        l1Controller->waiting = true;
    }else{
        if(victimBlock != NULL){
            CacheLine* victimCacheLine = getCacheLineByOffset(&victimBlock->HashTable,instruction.address.Offset);
            victimCacheLine->dataLine = StoreData(l1Data,value);
            victimBlock->dirtyBit = true;
            victimBlock->isIdle = false;
            return true;
        }else if(writeBlock != NULL){
            CacheLine* writeBufferCacheLine = getCacheLineByOffset(&victimBlock->HashTable,instruction.address.Offset);
            writeBufferCacheLine->dataLine = StoreData(l1Data,value);
            writeBlock->dirtyBit = true;
            writeBlock->isIdle = false;
            return true;
        }
    }
    return false;
}

bool CheckL2WriteBuffer(Block block2Write){
    Block* writeBlock = getBlockFromBuffer(&l2WriteBuffer->HashTable,block2Write.address.bitStringValue);
    if(writeBlock != NULL){
        removeBlockFromBuffer(&l2WriteBuffer->HashTable,&block2Write);
        putBlockInBuffer(&l2WriteBuffer->HashTable,&block2Write);
        return true;
    }
    return false;
}

void TEMP_putInL1Set(Address* address,Set* set,char value[64]){
    Block* block = Constructor_Block(*address);
    put(&set->HashTable,block);
    CacheLine* cacheLine = Constructor_CacheLine(*address,value);
    putCacheLine(&block->HashTable,cacheLine);
    CacheLine* toWriteTo = getCacheLineByOffset(&block->HashTable,address->Offset);
    toWriteTo->dataLine = StoreData(l1Data,value);
    l1Controller->waiting = false;
    block->dirtyBit = true;
    block->validBit = true;
    //Dequeue(l1Controller->transferer->TransferQueue);
    printf("Temp write:%s\n",GetData(l1Data,toWriteTo->dataLine));
}

void WriteBlockToL2Controller(Block block2Write){
    Set* set = getSetByIndex(&l2Controller->cache->HashTable,block2Write.address.Index);
    Block* block = get(&set->HashTable,block2Write.address.Tag);
    if(block != NULL){
        removeFromTable(&set->HashTable,block);
        put(&set->HashTable,&block2Write);
    }else if(block == NULL){
        bool found = CheckL2WriteBuffer(block2Write);
        if(found == false){
            printf("ERROR. Data in L1 that is not in L2");
        }
        BlockOnBus* blockOnBus = Constructor_BlockOnBus(block2Write,10,"some value");
        EnqueueBlock(dRAM->blockQueue,*blockOnBus);
    }
    CheckSetSize(set);
    CheckBufferSize();
}
void ProcessL2Instruction(Instruction instruction){
    Set* set = getSetByIndex(&l2Controller->cache->HashTable,instruction.address.Index);
    Block* block = get(&set->HashTable,instruction.address.Tag);
    if(block != NULL){
        BlockOnBus* blockOnBus = Constructor_BlockOnBus(*block,10,"some value");
        EnqueueBlock(l1Controller->blockQueue,*blockOnBus);
    }else{
        Enqueue(dRAM->transferer->TransferQueue,instruction);
    }
}

void ProcessDRamInstruction(Instruction instruction){
    DRamBlock* dramBlock = getBlock(&dRAM->HashTable,instruction.address.bitStringValue);
    Block* block = Constructor_Block(instruction.address);
    if(block != NULL){
        BlockOnBus* blockOnBus = Constructor_BlockOnBus(*block,10,"some value");
        EnqueueBlock(l2Controller->blockQueue,*blockOnBus);
    }else{
        printf("ERROR. Block not found in DRAM");
    }
}

void WriteBlockToDRAM(Block block2Write){
    DRamBlock* ramBlock = dRAM->getBlock(&dRAM->HashTable,block2Write.address.bitStringValue);
    DRamBlock* newdRam = Constructor_DRamBlock(block2Write.address,"Some value");
    if(ramBlock != NULL){
        removeBlockFromDRAM(&dRAM->HashTable,ramBlock);
    }
    putBlock(&dRAM->HashTable,newdRam);
}

void WriteToController(Instruction instruction, char value[64])
{
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,instruction.address.Index);
    Block* existing = get(&set->HashTable,instruction.address.Tag);
    if(existing != NULL){
        WriteToBlock(existing,instruction,value);
    }else if(existing == NULL){
        bool found = CheckVictimCacheAndWriteBuffer(instruction,value);
        if(found == false){
            Enqueue(l2Controller->transferer->TransferQueue,instruction);
            //TEMP_putInL1Set(&instruction.address,set,value);
        }
    }
    CheckSetSize(set);
    CheckBufferSize();
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
                    WriteBackToL2(l1VictimCache,&l1VictimCache->HashTable);
                }
                return victimCacheLine;
            } else if (writeBlock != NULL) {
                CacheLine *writeBufferCacheLine = getCacheLineByOffset(&writeBlock->HashTable,
                                                                       instruction.address.Offset);
                if (CountBlocksInBuffer(&l1WriteBuffer->HashTable) >= 5) {
                    WriteBackToL2(l1WriteBuffer,&l1WriteBuffer->HashTable);
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

/*void L2WriteBlock(Block block){
    Set* set = getSetByIndex(&l2Controller->cache->HashTable,block.address.Index);
    Block* existing = get(&set->HashTable,&block);
    if(existing == NULL){

    }
}*/