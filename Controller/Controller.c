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
    Address* address = Constructor_Address("0000000000000000");
    l1ControllerCon->controllerIsIdleUntilItReceivesThisBlock = *Constructor_Block(*address);//will be overwritten later on

    l1ControllerCon->writeBlockQueue = Constructor_BlockQueue();
    l1ControllerCon->cache = Constructor_Cache(64);
    l1ControllerCon->transferer = Constructor_Transferer();
    l1ControllerCon->waiting = false;
    return l1ControllerCon;
}

Controller* Constructor_L2Controller(){
    Controller* l2ControllerCon = malloc(sizeof(l2ControllerCon));
    Address* address = Constructor_Address("0000000000000000");
    l2ControllerCon->controllerIsIdleUntilItReceivesThisBlock = *Constructor_Block(*address);//will be overwritten later on

    l2ControllerCon->cache = Constructor_Cache(256);
    l2ControllerCon->transferer = Constructor_Transferer();
    l2ControllerCon->writeBlockQueue = Constructor_BlockQueue();
    l2ControllerCon->waiting = false;
    return l2ControllerCon;
}
void CheckL2SetSize(Set* set){
    int countInSet = Count(&set->HashTable);
    while(countInSet >= 4){
        SortHash(&set->HashTable);
        Block* leastUsed = GetLeastUsed(&set->HashTable);
        removeFromTable(&set->HashTable,leastUsed);
        if(leastUsed->dirtyBit == true){
            PutInL2WriteBuffer(leastUsed);
        }
    }
    CheckBufferSize();
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
    if(victimCacheCount > 2){
        WriteBackToL2(l1VictimCache,&l1VictimCache->HashTable);
    }
    if(writeBufferCount > 5){
        WriteBackToL2(l1WriteBuffer,&l1WriteBuffer->HashTable);
    }
}
void CheckL2BufferSize(){
    int writeBufferCount = CountBlocksInBuffer(&l2WriteBuffer->HashTable);
    if(writeBufferCount > 5){
        Block* s;
        Block* tmp;
        HASH_ITER(hh,l2WriteBuffer->HashTable,s,tmp){ //write everything in buffer to DRam
            if(s->dirtyBit == true){
                BlockOnBus* toWriteBack = Constructor_BlockOnBus(dRAM,*s,ClockCycleCount + 2);
                EnqueueBlock(dRAM->writeBlockQueue,toWriteBack);
            }
        }
    }
}

void PutInL2WriteBuffer(Block* existing){
    putBlockInBuffer(&l1WriteBuffer->HashTable,existing);
    CheckL2BufferSize();
}

void PutInWriteBuffer(Block* existing){
    putBlockInBuffer(&l1WriteBuffer->HashTable,existing);
    CheckBufferSize();
}

void PutInVictimCache(Block* existing){
    putBlockInBuffer(&l1VictimCache->HashTable,existing);
    CheckBufferSize();
}

void WriteBlockToL1Controller(Block toStore){
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,toStore.address.Index);
    Block* existing = get(&set->HashTable,toStore.address.Tag);
    if(existing != NULL){
        removeFromTable(&set->HashTable,existing);
        DequeueBlock(l1Controller->writeBlockQueue);
    }
    toStore.isIdle = false;
    put(&set->HashTable,&toStore);
    CheckSetSize(set);
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
        return false;
    }else{
        if(victimBlock != NULL){
            CacheLine* victimCacheLine = getCacheLineByOffset(&victimBlock->HashTable,instruction.address.Offset);
            victimCacheLine->dataLine = StoreData(l1Data,value);
            victimBlock->dirtyBit = true;
            victimBlock->isIdle = false;
            Set* set = getSetByIndex(&l1Controller->cache->HashTable,victimBlock->address.Index);//write back to cache
            put(&set->HashTable,victimBlock);
            removeBlockFromBuffer(&l1VictimCache->HashTable,victimBlock);
            return true;
        }else if(writeBlock != NULL){
            CacheLine* writeBufferCacheLine = getCacheLineByOffset(&victimBlock->HashTable,instruction.address.Offset);
            writeBufferCacheLine->dataLine = StoreData(l1Data,value);
            writeBlock->dirtyBit = true;
            writeBlock->isIdle = false;
            Set* set = getSetByIndex(&l1Controller->cache->HashTable,writeBlock->address.Index);//write back to cache
            put(&set->HashTable,writeBlock);
            removeBlockFromBuffer(&l1WriteBuffer->HashTable,writeBlock);
            return true;
        }
    }
    CheckBufferSize();
    printf("Error in CheckVictimCacheAndWriteBuffer.  Statements should not get this far");
    return false;
}

bool CheckL2WriteBuffer(Block block2Write){
    Block* writeBlock = getBlockFromBuffer(&l2WriteBuffer->HashTable,block2Write.address.bitStringValue);
    //checkBuffer
    if(writeBlock != NULL){
        removeBlockFromBuffer(&l2WriteBuffer->HashTable,&block2Write);
        Set* set = getSetByIndex(&l2Controller->cache->HashTable,block2Write.address.Index);
        put(&set->HashTable,&block2Write);//no need to put on block queue, just write directly from buffer to cache
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

void WriteBlockToL2Controller(BlockOnBus* blockOnBus2Write){
    CacheLine* s;
    CacheLine* tmp;
    int i = 0;
    HASH_ITER(hh,blockOnBus2Write->blockOnBus.HashTable,s,tmp){
        s->dataLine = StoreData(l2Data,blockOnBus2Write->valueBeingTransferred[s->dataLine]); //TransferBlockDataToL2
    }
    Block block2Write = blockOnBus2Write->blockOnBus;

    Set* set = getSetByIndex(&l2Controller->cache->HashTable,block2Write.address.Index);
    Block* block = get(&set->HashTable,block2Write.address.Tag);

    if(block != NULL){
        removeFromTable(&set->HashTable,block);
    }
    put(&set->HashTable,&block2Write);
    /*else if(block == NULL){
        bool found = CheckL2WriteBuffer(block2Write);
        if(found == false){
            printf("ERROR. Data in L1 that is not in L2");
        }
        BlockOnBus* blockOnBus = Constructor_BlockOnBus(l2Controller,block2Write,ClockCycleCount + 2);
        EnqueueBlock(dRAM->writeBlockQueue,blockOnBus);
    }*/
    CheckL2SetSize(set);
    CheckL2BufferSize();
}
void FindBlockInL2(Instruction instruction){
    Set* set = getSetByIndex(&l2Controller->cache->HashTable,instruction.address.Index);
    Block* block = get(&set->HashTable,instruction.address.Tag);
    if(block != NULL){
        if(block->isIdle == true){
            l2Controller->waiting == true;
            l2Controller->controllerIsIdleUntilItReceivesThisBlock = *block;
            return;
        }
        BlockOnBus* blockOnBus = Constructor_BlockOnBus(l2Controller,*block,ClockCycleCount + 2);
        EnqueueBlock(l1Controller->writeBlockQueue,blockOnBus);
    }else{
        Block* idlePlaceHolder = Constructor_Block(instruction.address);
        idlePlaceHolder->isIdle = true;//Now we have marked this block in our set as idle
        put(&set->HashTable,idlePlaceHolder);
        Enqueue(dRAM->transferer->TransferQueue,instruction);
    }
}

void ProcessDRamInstruction(Instruction instruction){
    BlockOnBus* dramBlock = getBlock(&dRAM->HashTable,instruction.address.bitStringValue);
    if(dramBlock != NULL){
        BlockOnBus* blockOnBus = getBlock(&dRAM->HashTable,instruction.address.bitStringValue);
        EnqueueBlock(l2Controller->writeBlockQueue,blockOnBus);
    }else{
        Block* newBlockForMemory = Constructor_Block(instruction.address);//Does not exist in memory yet, i.e. first time write
        CacheLine* cacheLine = Constructor_CacheLine(instruction.address,instruction.data);
        putCacheLine(&newBlockForMemory->HashTable,cacheLine);
        BlockOnBus* dramBlock = Constructor_BlockOnBusDRAM(*newBlockForMemory);
        putBlock(&dRAM->HashTable,dramBlock);
        EnqueueBlock(l2Controller->writeBlockQueue,dramBlock);//send back to l2
    }
    Dequeue(dRAM->transferer->TransferQueue);//will always process the instruction.
}



void WriteBlockToDRAM(BlockOnBus* block2Write){
    BlockOnBus* ramBlock = getBlock(&dRAM->HashTable,block2Write->blockOnBus.address.bitStringValue);
    if(ramBlock != NULL){
        removeBlockFromDRAM(&dRAM->HashTable,ramBlock);
    }
    putBlock(&dRAM->HashTable,block2Write);
}

void WriteToController(Instruction instruction, char value[64])
{
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,instruction.address.Index);
    Block* existing = get(&set->HashTable,instruction.address.Tag);
    if(existing != NULL){
        if(existing->isIdle == true){
            l1Controller->controllerIsIdleUntilItReceivesThisBlock = *existing;
            l1Controller->waiting = true;
            return;
        }
        WriteToBlock(existing,instruction,value);
    }else if(existing == NULL){
        bool found = CheckVictimCacheAndWriteBuffer(instruction,value);
        if(found == false){
            Block* idlePlaceHolder = Constructor_Block(instruction.address);
            idlePlaceHolder->isIdle = true;//Now we have marked this block in our set as idle
            put(&set->HashTable,idlePlaceHolder);
            Enqueue(l2Controller->transferer->TransferQueue,instruction);
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
        if(block->isIdle == true){
            l1Controller->waiting = true;
            l1Controller->controllerIsIdleUntilItReceivesThisBlock = *block;
            return NULL;
        }
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
            Block* idlePlaceHolder = Constructor_Block(instruction.address);
            idlePlaceHolder->isIdle = true;//Now we have marked this block in our set as idle
            put(&set->HashTable,idlePlaceHolder);
            Enqueue(l2Controller->transferer->TransferQueue, instruction);
            return NULL;
        } else {
            if (victimBlock != NULL) {
                CacheLine *victimCacheLine = getCacheLineByOffset(&victimBlock->HashTable, instruction.address.Offset);
                victimBlock->isIdle = false;
                put(&set->HashTable,victimBlock);
                removeBlockFromBuffer(&l1VictimCache->HashTable,victimBlock);
                CheckBufferSize();
                return victimCacheLine;
            } else if (writeBlock != NULL) {
                CacheLine *writeBufferCacheLine = getCacheLineByOffset(&writeBlock->HashTable,
                                                                       instruction.address.Offset);
                writeBlock->isIdle = false;
                put(&set->HashTable,writeBlock);
                removeBlockFromBuffer(&l1WriteBuffer->HashTable,writeBlock);
                CheckBufferSize();
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