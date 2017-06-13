//
// Created by chad on 6/5/17.
//

//implement storing/getting blocks from memory
#include "DRAM.h"
#include "BlockTransferer/BlockTransferer.h"
#include "Block_Queue/Block_Queue.h"
#include "CacheLine/CacheLine.h"

DRAM* Constructor_DRAM(){
    DRAM* dram = malloc(sizeof(DRAM));
    dram->HashTable = NULL;
    dram->transferer = Constructor_Transferer();
    dram->writeBlockQueue = Constructor_BlockQueue();
    return dram;
}

DRamBlock* Constructor_DRamBlock(Address address,char value[64][8]){
    DRamBlock* ramBlock = malloc(sizeof(DRamBlock));
    ramBlock->address = address;
    int i;
    for(i = 0;i<8;i++){
        strcpy(ramBlock->data[i],value[i]);
    }
    
    return ramBlock;
}

void putBlock(DRamBlock** HashTable,DRamBlock *value) {  //key is useFrequency of the block.  Seems magical
    if(value->address.bitString == NULL){
        printf("The passed block needs to have attribute address set");
    }
    HASH_ADD_INT(*HashTable, address.bitStringValue,value );
}

void removeBlockFromDRAM(DRamBlock** HashTable,DRamBlock* blockToRemove) {
    HASH_DEL( *HashTable, blockToRemove);//removes blocks of type block
}

DRamBlock* getBlock(DRamBlock** HashTable,int key) {
    DRamBlock *hashTableStoresInThisBlock;

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into hashTableStoresInThisBlock
    return hashTableStoresInThisBlock;
}

int CountBlocks(DRamBlock** HashTable){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(*HashTable);
    return num_in_hashtable;
}

void print_all_blocks(DRamBlock** HashTable) {
    DRamBlock* s;
    DRamBlock* tmp;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("address: %d\n",s->address.bitStringValue);
    }
}
