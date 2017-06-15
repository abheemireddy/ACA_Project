//
// Created by chad on 6/5/17.
//

//implement storing/getting blocks from memory
#include <Global_Variables.h>
#include "DRAM.h"
#include "BlockOnBus/BlockOnBus.h"
#include "BlockTransferer/BlockTransferer.h"
#include "Block_Queue/Block_Queue.h"

DRAM* Constructor_DRAM(){
    DRAM* dram = malloc(sizeof(DRAM));
    dram->HashTable = NULL;
    dram->transferer = Constructor_Transferer();
    dram->writeBlockQueue = Constructor_BlockQueue();
    return dram;
}
BlockOnBus* Constructor_BlockOnBusDRAM(Block* block){
    BlockOnBus* blockOnBus = malloc(sizeof(BlockOnBus));
    blockOnBus->blockOnBus = block;
    blockOnBus->clockCycleWhenBlockIsAvailable = ClockCycleCount;
    return blockOnBus;
}

void putBlock(BlockOnBus** HashTable,BlockOnBus *value) {  //key is useFrequency of the block.  Seems magical
    if(value->blockOnBus->address.bitString == NULL){
        printf("The passed block needs to have attribute address set");
    }
    HASH_ADD_INT(*HashTable, blockOnBus->address.bitStringValue,value );
}

void removeBlockFromDRAM(BlockOnBus** HashTable,BlockOnBus* blockToRemove) {
    HASH_DEL( *HashTable, blockToRemove);//removes blocks of type block
}

BlockOnBus* getBlock(BlockOnBus** HashTable,int key) {
    BlockOnBus *hashTableStoresInThisBlock = malloc(sizeof(Block));

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into hashTableStoresInThisBlock
    return hashTableStoresInThisBlock;
}

int CountBlocks(BlockOnBus** HashTable){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(*HashTable);
    return num_in_hashtable;
}

void print_all_blocks(BlockOnBus** HashTable) {
    BlockOnBus* s;
    BlockOnBus* tmp;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("address: %d\n",s->blockOnBus->address.bitStringValue);
    }
}
