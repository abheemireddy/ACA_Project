//
// Created by chad on 6/5/17.
//

//implement storing/getting blocks from memory
#include "DRAM.h"
#include "Block.h"

DRAM Constructor_DRAM(){
    DRAM dram = {};
    dram.HashTable = NULL;
    dram.putBlock = &putBlock;
    dram.getBlock = &getBlock;
    dram.CountBlocks = &CountBlocks;
    dram.print_all_blocks = &print_all_blocks;
    return dram;
}

void putBlock(Block** HashTable,Block *value) {  //key is useFrequency of the block.  Seems magical
    if(value->address.bitString == NULL){
        printf("The passed block needs to have attribute address set");
    }
    HASH_ADD_INT(*HashTable, address.bitStringValue,value );
    //The last parameter is a pointer to the structure being added
}

/*void replace(UT_hash_handle hh,Block** HashTable,Block *value) {
    struct BlockTag *hashTableStoresInThisBlock;//to store getter

    HASH_FIND_STR( *HashTable, value->address.bitString, hashTableStoresInThisBlock );
    if (hashTableStoresInThisBlock==NULL) {
        hashTableStoresInThisBlock = (struct BlockTag*)malloc(sizeof(struct BlockTag));
        hashTableStoresInThisBlock->address.bitString = value->address.bitString;
        HASH_ADD_KEYPTR(hh,*HashTable, value->address.bitString, strlen(value->address.bitString),value );
    }
}*/

Block* getBlock(Block** HashTable,int key) {
    Block *hashTableStoresInThisBlock;

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into hashTableStoresInThisBlock
    return hashTableStoresInThisBlock;
}

//count items
int CountBlocks(Block** HashTable){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(*HashTable);
    return num_in_hashtable;
}

void print_all_blocks(Block** HashTable) {
    Block* s;
    Block* tmp;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("address: %s, LFU:%d\n",s->address.bitString,s->useFrequency);
    }
}
