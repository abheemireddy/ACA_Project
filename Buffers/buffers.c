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
        l1Controller->waiting = true;
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
    Block* s;
    Block* tmp;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("Flushing to L2: %d\n",s->address.bitStringValue);
        removeBlockFromBuffer(&buffer->HashTable,s);
        BlockOnBus* blockOnBus = Constructor_BlockOnBus(l1Controller,*s,0);
        EnqueueBlock(l2Controller->writeBlockQueue,*blockOnBus);
    }
}

Buffer* Constructor_Buffer(){
    Buffer* buffer = malloc(sizeof(Buffer));
    //Transferer transferer = Con
    buffer->HashTable = NULL;
    return buffer;
}

void putBlockInBuffer(Block** HashTable,Block *value) {  //key is useFrequency of the block.  Seems magical
    if(value->address.bitString == NULL){
        printf("The passed block needs to have attribute address set");
    }
    /*Block* alreadyInHashTable = getBlock(HashTable,value->address.bitStringValue);//overwrite duplicate keys
    if(alreadyInHashTable != NULL){
        removeBlockFromBuffer(HashTable,alreadyInHashTable);
    }*/
    HASH_ADD_INT(*HashTable, address.bitStringValue,value );
}

void removeBlockFromBuffer(Block** HashTable,Block* blockToRemove) {
    HASH_DEL( *HashTable, blockToRemove);//removes blocks of type block
}

Block* getBlockFromBuffer(Block** HashTable,int key) {
    Block *hashTableStoresInThisBlock;

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into hashTableStoresInThisBlock
    return hashTableStoresInThisBlock;
}

int CountBlocksInBuffer(Block** HashTable){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(*HashTable);
    return num_in_hashtable;
}

void print_all_blocks_in_buffer(Block** HashTable) {
    Block* s;
    Block* tmp;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("address: %d\n",s->address.bitStringValue);
    }
}
