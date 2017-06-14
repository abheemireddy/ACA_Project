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

    l1ControllerCon->writeBlockQueue = Constructor_BlockQueue();
    l1ControllerCon->cache = Constructor_Cache(256);
    l1ControllerCon->transferer = Constructor_Transferer();
    l1ControllerCon->waiting = false;
    return l1ControllerCon;
}

Controller* Constructor_L2Controller(){
    Controller* l2ControllerCon = malloc(sizeof(l2ControllerCon));

    l2ControllerCon->cache = Constructor_Cache(512);
    l2ControllerCon->transferer = Constructor_Transferer();
    l2ControllerCon->writeBlockQueue = Constructor_BlockQueue();
    l2ControllerCon->waiting = false;
    return l2ControllerCon;
}

void PushDownBlockInL1(Block* block2Find){
    printf("Evicting from L2.  Checking in L1 for a block to evict.  Block value:%d\n",block2Find->address.bitStringValue);
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,block2Find->address.Index);
    Block* block = get(&set->HashTable,block2Find->address.Tag);
    Block* toWriteToMemory;
    if(block != NULL) {
        toWriteToMemory = block;
    }
    if (block == NULL) {
        //check victim and write buffer
        Block *victimBlock = getBlockFromBuffer(&l1VictimCache->HashTable, block2Find->address.bitStringValue);
        Block *writeBlock = getBlockFromBuffer(&l1WriteBuffer->HashTable, block2Find->address.bitStringValue);
        if (victimBlock == NULL && writeBlock == NULL) {
            toWriteToMemory = block2Find;//Block is not in L1, just push down what was in L2.
            printf("Did not find matching block in L1, we can safetly evict block from L2\n");
        } else {
            if (victimBlock != NULL) {
                toWriteToMemory = victimBlock;
                printf("Found L2 block in L1 in the victim cache.  Evicting...\n");
            } else if (writeBlock != NULL) {
                toWriteToMemory = writeBlock;
                printf("Found L2 block in L1 in the write buffer.  Evicting...\n");
            }
        }
    }
    BlockOnBus* toWrite = Constructor_BlockOnBus(dRAM,toWriteToMemory,ClockCycleCount + 0);
    EnqueueBlock(dRAM->writeBlockQueue,toWrite);
}

void CheckL2SetSize(Set* set){
    int countInSet = Count(&set->HashTable);
    while(countInSet > 4){
        SortHash(&set->HashTable);
        Block* leastUsed = GetLeastUsed(&set->HashTable);
        HASH_DELETE(hh,set->HashTable,leastUsed);//removed from L2
        if(leastUsed->dirtyBit == true){
            PutInL2WriteBuffer(leastUsed);
            printf("Moving block to L2's Write Buffer.  Block:%d\n",leastUsed->address.bitStringValue);
        }else{
            printf("Evicting block from L2.  It is clean, so look to evict the block from L1 too.  Block:%d\n",leastUsed->address.bitStringValue);
            Address* adjustedAddress = Constructor_AddressConvertForL2(leastUsed->address.bitString);
            leastUsed->address = *adjustedAddress;
            PushDownBlockInL1(leastUsed);
        }
    }
    //CheckBufferSize();
}
void CheckSetSize(Set* set){
    int countInSet = Count(&set->HashTable);
    if(countInSet > 4){
        SortHash(&set->HashTable);
        Block* leastUsed = GetLeastUsed(&set->HashTable);
        removeFromTable(&set->HashTable,leastUsed);
        if(leastUsed->dirtyBit == true){
            PutInWriteBuffer(leastUsed);
            printf("Moving block to L1's Write Buffer.  Block:%d\n",leastUsed->address.bitStringValue);
        }else{
            PutInVictimCache(leastUsed);
            printf("Moving block to L1's Victim Cache.  Block:%d\n",leastUsed->address.bitStringValue);
        }
    }
    CheckBufferSize();
}
void CheckBufferSize(){
    int victimCacheCount = CountBlocksInBuffer(&l1VictimCache->HashTable);
    int writeBufferCount = CountBlocksInBuffer(&l1WriteBuffer->HashTable);
    if(victimCacheCount > 5){
        printf("L1 Victim cache full.  Flushing L1's victim cache\n");
        WriteBackToL2(l1VictimCache,&l1VictimCache->HashTable);
    }
    if(writeBufferCount > 5){
        WriteBackToL2(l1WriteBuffer,&l1WriteBuffer->HashTable);
        printf("L1 Write buffer full.  Flushing L1's write buffer\n");
    }
}
void CheckL2BufferSize(){
    int writeBufferCount = CountBlocksInBuffer(&l2WriteBuffer->HashTable);
    if(writeBufferCount > 5){
        Block* s;
        Block* tmp;
        HASH_ITER(hh,l2WriteBuffer->HashTable,s,tmp){ //write everything in buffer to DRam
            Address* adjustedAddress = Constructor_AddressConvertForL2(s->address.bitString);
            s->address = *adjustedAddress;
            PushDownBlockInL1(s);
            printf("Flushing from L2's write buffer.  Also evicting these blocks from L1\n");
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

void WriteBlockToL1Controller(Block* toStore){
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,toStore->address.Index);
    Block* existing = get(&set->HashTable,toStore->address.Tag);
    if(existing != NULL){
        printf("Block in L1...Writing, Block:%d\n",toStore->address.bitStringValue);
        removeFromTable(&set->HashTable,existing);
    }
    toStore->isIdle = false;
    toStore->dirtyBit = false;
    toStore->validBit = true;
    put(&set->HashTable,toStore);
    DequeueBlock(l1Controller->writeBlockQueue);
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

CacheLine* WriteToBlock(Block* existing,Instruction instruction,char value[8]){
    CacheLine* toWriteTo = getCacheLineByOffset(&existing->HashTable,instruction.address.Offset);
    if(toWriteTo == NULL){
        printf("No Existing Valid CacheLine.  Writing to CacheLine:%d\n",instruction.address.bitStringValue);
        CacheLine* cacheLine = Constructor_CacheLine(instruction.address,value);
        putCacheLine(&existing->HashTable,cacheLine);
        toWriteTo = getCacheLineByOffset(&existing->HashTable,instruction.address.Offset);
    }else{
        //printf("CacheLine already existed.  Writing to CacheLine:%d\n",instruction.address.bitStringValue);
    }
    toWriteTo->dataLine = StoreData(l1Data,value);
    existing->dirtyBit = true;
    existing->validBit = true;
    printf("***Brought data back to Processor:%d val:%s at clock cycle:%d\n",toWriteTo->address.bitStringValue,GetData(l1Data,toWriteTo->dataLine),ClockCycleCount);
    Dequeue(l1Controller->transferer->TransferQueue);
    return toWriteTo;
}

bool CheckVictimCacheAndWriteBuffer(Instruction instruction,char value[8]){
    //printf("Checking both L1 buffers for Block:%d\n",instruction.address.bitStringValue);
    Block* victimBlock = getBlockFromBuffer(&l1VictimCache->HashTable,instruction.address.bitStringValue);
    Block* writeBlock = getBlockFromBuffer(&l1WriteBuffer->HashTable,instruction.address.bitStringValue);
    if(victimBlock == NULL && writeBlock == NULL){
        return false;
    }else{
        if(victimBlock != NULL){
            printf("Found block in victim cache\n");
            CacheLine* victimCacheLine = getCacheLineByOffset(&victimBlock->HashTable,instruction.address.Offset);
            if(victimCacheLine == NULL){
                printf("No Existing Valid CacheLine in victimCache.  Writing to CacheLine%d\n",instruction.address.bitStringValue);
                CacheLine* cacheLine = Constructor_CacheLine(instruction.address,value);
                putCacheLine(&victimBlock->HashTable,cacheLine);
                victimCacheLine = getCacheLineByOffset(&victimBlock->HashTable,instruction.address.Offset);
            }
            victimCacheLine->dataLine = StoreData(l1Data,value);
            victimBlock->dirtyBit = true;
            victimBlock->isIdle = false;
            Set* set = getSetByIndex(&l1Controller->cache->HashTable,victimBlock->address.Index);//write back to cache
            put(&set->HashTable,victimBlock);
            //removeBlockFromBuffer(&l1VictimCache->HashTable,victimBlock);
            return true;
        }else if(writeBlock != NULL){
            printf("Found block in write buffer");
            CacheLine* writeBufferCacheLine = getCacheLineByOffset(&writeBlock->HashTable,instruction.address.Offset);
            if(writeBufferCacheLine == NULL){
                printf("No Existing Valid CacheLine in victimCache.  Writing to CacheLine%d\n",instruction.address.bitStringValue);
                CacheLine* cacheLine = Constructor_CacheLine(instruction.address,value);
                putCacheLine(&writeBlock->HashTable,cacheLine);
                writeBufferCacheLine = getCacheLineByOffset(&writeBlock->HashTable,instruction.address.Offset);
            }
            writeBufferCacheLine->dataLine = StoreData(l1Data,value);
            writeBlock->dirtyBit = true;
            writeBlock->isIdle = false;
            Set* set = getSetByIndex(&l1Controller->cache->HashTable,writeBlock->address.Index);//write back to cache
            put(&set->HashTable,writeBlock);
            //removeBlockFromBuffer(&l1WriteBuffer->HashTable,writeBlock);
            return true;
        }
    }
    CheckBufferSize();
    printf("Check CheckVictimCacheAndWriteBuffer. Statements should not get this far\n");
    return false;
}

bool CheckL2WriteBuffer(Block* block2Write){
    Block* writeBlock = getBlockFromBuffer(&l2WriteBuffer->HashTable,block2Write->address.bitStringValue);
    printf("Checking L2's write buffer for Block:%d\n",block2Write->address.bitStringValue);
    if(writeBlock != NULL){
        printf("Found block in write buffer\n");
        removeBlockFromBuffer(&l2WriteBuffer->HashTable,block2Write);
        Set* set = getSetByIndex(&l2Controller->cache->HashTable,block2Write->address.Index);
        put(&set->HashTable,block2Write);//write directly from buffer to cache
        if(block2Write->isIdle == true){
            printf("Putting L2 Controller in idle from trying to access a block already being written to, Block:%d\n",block2Write->address.bitStringValue);
            l2Controller->waiting == true;
            L2controllerIsIdleUntilItReceivesThisBlock = *block2Write;
            return true;
        }
        printf("Found block in L2.  Sending to L1, Block:%d\n",block2Write->address.bitStringValue);
        BlockOnBus* blockOnBus = Constructor_BlockOnBus(l2Controller,block2Write,ClockCycleCount + 2);
        EnqueueBlock(l1Controller->writeBlockQueue,blockOnBus);
        Dequeue(l2Controller->transferer->TransferQueue);
        return true;
    }
    printf("Did not find block in L2's write buffer\n");
    return false;
}

void WriteBlockToL2Controller(BlockOnBus* blockOnBus2Write){
    Address* adjustedAddress = Constructor_AddressConvertForL2(blockOnBus2Write->blockOnBus->address.bitString);
    blockOnBus2Write->blockOnBus->address = *adjustedAddress;
    CacheLine* s;
    CacheLine* tmp;
    int i = 0;
    HASH_ITER(hh,blockOnBus2Write->blockOnBus->HashTable,s,tmp){
        s->dataLine = StoreData(l2Data,blockOnBus2Write->valueBeingTransferred[s->dataLine]); //TransferBlockDataToL2
    }

    Set* set = getSetByIndex(&l2Controller->cache->HashTable,blockOnBus2Write->blockOnBus->address.Index);
    Block* block = get(&set->HashTable,blockOnBus2Write->blockOnBus->address.Tag);

    if(block != NULL){
        printf("Found block in L2... Writing, Block:%d\n",block->address.bitStringValue);
        //removeFromTable(&set->HashTable,block);
    }
    put(&set->HashTable,blockOnBus2Write->blockOnBus);
    CheckL2SetSize(set);
    CheckL2BufferSize();
}
void FindBlockInL2(Instruction instruction){
    Address* adjustedAddress = Constructor_AddressConvertForL2(instruction.address.bitString);
    instruction.address = *adjustedAddress;
    Set* set = getSetByIndex(&l2Controller->cache->HashTable,instruction.address.Index);
    Block* block = get(&set->HashTable,instruction.address.Tag);

    if(block != NULL){
        Address nextAddress = Peek(l2Controller->transferer->TransferQueue).address;
        if(block->isIdle == true && !((nextAddress.Tag == block->address.Tag) && (nextAddress.Index == block->address.Index) && (nextAddress.Offset == block->address.Offset))){
            if(instruction.instruction == 1){
                printf("Putting L2 Controller in idle from trying to write from a block already being written to, Block:%d\n",instruction.address.bitStringValue);
            }else{
                printf("Putting L2 Controller in idle from trying to read from a block busy getting data downstream, Block::%d\n",instruction.address.bitStringValue);
            }
            l2Controller->waiting == true;
            L2controllerIsIdleUntilItReceivesThisBlock = *block;
            return;
        }
        printf("Found block in L2.  Sending to L1, Block:%d\n",instruction.address.bitStringValue);
        Address* re_adjustedAddress = Constructor_Address(instruction.address.bitString);
        block->address = *re_adjustedAddress;
        BlockOnBus* blockOnBus = Constructor_BlockOnBus(l2Controller,block,ClockCycleCount + 2);
        EnqueueBlock(l1Controller->writeBlockQueue,blockOnBus);
        Dequeue(l2Controller->transferer->TransferQueue);
    }else{
        Block* idlePlaceHolder = Constructor_Block(instruction.address);
        bool found = CheckL2WriteBuffer(idlePlaceHolder);
        if(found == true){
            return;
        }
        printf("Putting L2 block on idle, Block:%d\n",instruction.address.bitStringValue);
        idlePlaceHolder->isIdle = true;//Now we have marked this block in our set as idle
        put(&set->HashTable,idlePlaceHolder);
        Address* re_adjustedAddress = Constructor_Address(instruction.address.bitString);
        instruction.address = *re_adjustedAddress;
        Enqueue(dRAM->transferer->TransferQueue,instruction);
    }
}

void ProcessDRamInstruction(Instruction instruction){
    BlockOnBus* checkDramBlock = getBlock(&dRAM->HashTable,instruction.address.bitStringValue);
    if(checkDramBlock != NULL){
        BlockOnBus* blockOnBus = getBlock(&dRAM->HashTable,instruction.address.bitStringValue);
        blockOnBus->blockOnBus->dirtyBit = false;
        blockOnBus->blockOnBus->validBit = true;
        printf("Found block in memory, sending to L2, Block:%d\n",instruction.address.bitStringValue);
        EnqueueBlock(l2Controller->writeBlockQueue,blockOnBus);
    }else{
        printf("Storing block in memory, Block:%d\n",instruction.address.bitStringValue);
        Block* newBlockForMemory = Constructor_Block(instruction.address);//Does not exist in memory yet, i.e. first time write
        newBlockForMemory->dirtyBit = false;
        newBlockForMemory->validBit = true;
        CacheLine* cacheLine = Constructor_CacheLine(instruction.address,instruction.data);
        cacheLine->dataLine = 0;
        putCacheLine(&newBlockForMemory->HashTable,cacheLine);
        BlockOnBus* newDramBlock = Constructor_BlockOnBusDRAM(newBlockForMemory);
        strcpy(newDramBlock->valueBeingTransferred[0],instruction.data);
        putBlock(&dRAM->HashTable,newDramBlock);
        printf("Sending block to L2, Block:%d\n",newDramBlock->blockOnBus->address.bitStringValue);
        EnqueueBlock(l2Controller->writeBlockQueue,newDramBlock);//send back to l2
    }
    Dequeue(dRAM->transferer->TransferQueue);//will always process the instruction.
}



void WriteBlockToDRAM(BlockOnBus* block2Write){
    BlockOnBus* ramBlock = getBlock(&dRAM->HashTable,block2Write->blockOnBus->address.bitStringValue);
    if(ramBlock != NULL){
        removeBlockFromDRAM(&dRAM->HashTable,ramBlock);
    }
    ramBlock->blockOnBus->validBit = true;
    ramBlock->blockOnBus->dirtyBit = false;
    putBlock(&dRAM->HashTable,block2Write);
}

void WriteToController(Instruction instruction, char value[8])
{
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,instruction.address.Index);
    bool found1 = CheckVictimCacheAndWriteBuffer(instruction,value);
    Block* existing = get(&set->HashTable,instruction.address.Tag);
    if(existing != NULL){
        Address nextAddress = Peek(l1Controller->transferer->TransferQueue).address;
        if(existing->isIdle == true && !((nextAddress.Tag == existing->address.Tag) && (nextAddress.Index == existing->address.Index) && (nextAddress.Offset == existing->address.Offset))){
            printf("Putting L1 Controller in idle.  Trying to write from a block already being written to, Block:%d\n",instruction.address.bitStringValue);
            L1controllerIsIdleUntilItReceivesThisBlock = *existing;
            l1Controller->waiting = true;
            return;
        }
        WriteToBlock(existing,instruction,value);
    }else if(existing == NULL){
        Set* setTest = getSetByIndex(&l1Controller->cache->HashTable,0);
        if(setTest == NULL){
            int p = 5;
        }
        bool found = CheckVictimCacheAndWriteBuffer(instruction,value);
        if(found == false){
            printf("Block not in L1. Marking L1 block as idle, Block:%d\n",instruction.address.bitStringValue);
            Block* idlePlaceHolder = Constructor_Block(instruction.address);
            idlePlaceHolder->isIdle = true;//Now we have marked this block in our set as idle
            put(&set->HashTable,idlePlaceHolder);
            Enqueue(l2Controller->transferer->TransferQueue,instruction);
        }
    }
    CheckSetSize(set);
    CheckBufferSize();
}

CacheLine* L1_read(Instruction instruction)
{
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,instruction.address.Index);
    Block* block = get(&set->HashTable,instruction.address.Tag);
    if(block != NULL){
        Address nextAddress = Peek(l1Controller->transferer->TransferQueue).address;
        if(block->isIdle == true && !((nextAddress.Tag == block->address.Tag) && (nextAddress.Index == block->address.Index) && (nextAddress.Offset == block->address.Offset))){
            printf("Putting L1 Controller in idle.  Trying to read from a block busy getting data downstream%d\n",instruction.address.bitStringValue);
            l1Controller->waiting = true;
            L1controllerIsIdleUntilItReceivesThisBlock = *block;
            return NULL;
        }
        if(block->validBit == true){
            CacheLine* cacheLine = WriteToBlock(block,instruction,instruction.data);
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
            printf("block not in L1.  Transferring read request to L2 for Block:%d\n",instruction.address.bitStringValue);
            Enqueue(l2Controller->transferer->TransferQueue, instruction);
            return NULL;
        } else {
            if (victimBlock != NULL) {
                printf("Found block in victimBlock.  Moving block back to L1 cache, Block:%d\n",instruction.address.bitStringValue);
                CacheLine *victimCacheLine = getCacheLineByOffset(&victimBlock->HashTable, instruction.address.Offset);
                victimBlock->isIdle = false;
                put(&set->HashTable,victimBlock);
                removeBlockFromBuffer(&l1VictimCache->HashTable,victimBlock);
                CheckBufferSize();
                return victimCacheLine;
            } else if (writeBlock != NULL) {
                printf("Found block in write buffer.  Moving block back to L1 cache, Block:%d\n",instruction.address.bitStringValue);
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
	return NULL;
}
