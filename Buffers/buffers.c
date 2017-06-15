//
// Created by chad on 6/5/17.
//

#include "buffers.h"
#include "Block/Block.h"
#include "Block_Queue/Block_Queue.h"
#include "BlockTransferer/BlockTransferer.h"
#include "Global_Variables.h"
#include "Queue/Queue.h"

CacheLine* SearchInBuffers(Instruction instruction){
    Block* victimBlock = getBlockFromBuffer(&l1VictimCache->HashTable,instruction.address.bitStringValue);
    Block* writeBlock = getBlockFromBuffer(&l1WriteBuffer->HashTable,instruction.address.bitStringValue);
    if(victimBlock == NULL && writeBlock == NULL){
        Enqueue(l2Controller->transferer->TransferQueue,instruction);
        return NULL;
    }else{
        if(victimBlock != NULL){
            CacheLine* victimCacheLine = getCacheLineByOffset(&victimBlock->HashTable,instruction.address.Offset);
            return victimCacheLine;
        }else if(writeBlock != NULL){
            CacheLine* writeBufferCacheLine = getCacheLineByOffset(&victimBlock->HashTable,instruction.address.Offset);
            return writeBufferCacheLine;
        }
    }
}

void WriteBackToL2(Buffer* buffer,Block** HashTable){
    Block* s = malloc(sizeof(Block));;
    Block* tmp = malloc(sizeof(Block));;

    HASH_ITER(hh,buffer->HashTable,s,tmp){
        HASH_DELETE(hh,buffer->HashTable,s);
        printf("Flushing to L2: %d\n",s->address.bitStringValue);
        if(s->dirtyBit == true){
            BlockOnBus* blockOnBus = Constructor_BlockOnBus(l1Controller,s,ClockCycleCount + 0);//assume it takes 1 clock cycle to write back to main cache
            EnqueueBlock(l2Controller->writeBlockQueue,blockOnBus);
        }
    }
}

Buffer* Constructor_Buffer(){
    Buffer* buffer = malloc(sizeof(Buffer));
    buffer->HashTable = NULL;
    return buffer;
}

void putBlockInBuffer(Block** HashTable,Block *value) {  //key is useFrequency of the block.  Seems magical
    if(value == NULL){
        printf("The passed block needs to have attribute address set");
    }
    Block* tmp = malloc(sizeof(Block));
    Block *hashTableStoresInThisBlock = malloc(sizeof(Block));
    int bitStringValue = value->address.bitStringValue;
    HASH_FIND_INT( *HashTable,&bitStringValue, hashTableStoresInThisBlock );//find block_id and put into hashTableStoresInThisBlock
    if(hashTableStoresInThisBlock != NULL){
        HASH_DELETE(hh,*HashTable,value);
    }
    Block* tmp2 = malloc(sizeof(Block));
    HASH_REPLACE_INT(*HashTable, address.bitStringValue,value,tmp );
}

void removeBlockFromBuffer(Block** HashTable,Block* blockToRemove) {
    if(*HashTable == NULL){
        return;
    }
    Block *hashTableStoresInThisBlock = malloc(sizeof(Block));
    int bitStringValue = blockToRemove->address.bitStringValue;
    HASH_FIND_INT( *HashTable,&bitStringValue, hashTableStoresInThisBlock );//find block_id and put into hashTableStoresInThisBlock
    if(hashTableStoresInThisBlock != NULL){
        HASH_DELETE(hh,*HashTable,blockToRemove);
    }
}

Block* getBlockFromBuffer(Block** HashTable,int key) {
    if(*HashTable == NULL){
        return NULL;
    }
    Block *hashTableStoresInThisBlock = malloc(sizeof(Block));
    HASH_FIND_INT( *HashTable,&key, hashTableStoresInThisBlock );//find block_id and put into hashTableStoresInThisBlock
    return hashTableStoresInThisBlock;
}

int CountBlocksInBuffer(Block** HashTable){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(*HashTable);
    return num_in_hashtable;
}

void print_all_blocks_in_buffer(Block** HashTable) {
    Block* s = malloc(sizeof(Block));
    Block* tmp = malloc(sizeof(Block));;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("address: %d\n",s->address.bitStringValue);
    }
}
