//
// Created by chad on 5/24/17.
//

#include "Block/Block.h"
#include "Set.h"
#include <stdio.h>


Set* Constructor_Set(int numberOfBlocks,Address address){
    Set* set = malloc(sizeof(Set));
    set->address = address;
    set->numberOfBlocks = numberOfBlocks;
    set->HashTable = NULL;

    int i;
    int setAddress = address.bitStringValue;
    for(i = 0;i<set->numberOfBlocks;i++){
        char* bitString = int2bin(setAddress);
        Address* address = Constructor_Address(bitString);
        Block* block = Constructor_Block(*address);
        block->validBit = false;
        put(&set->HashTable,block);
        setAddress += 1;
    }
    return set;
}

bool IsBlockInSet(Set set,Block newBlock){
    Block* alreadyInHashTable = get(&set.HashTable,newBlock.address.bitString);
    if(alreadyInHashTable != NULL){
        return true;
    }else{
        return false;
    }
}

void put(Block** HashTable,Block *value) {  //key is useFrequency of the block.  Seems magical
    if(value->address.bitString == NULL){
        printf("The passed block needs to have attribute address set");
    }
    HASH_ADD_STR(*HashTable, address.bitString,value );
}

//HASH_REPLACE  is equivalent to HASH_ADD but it finds and deletes that item first
void replaceByUseFrequency(Block** HashTable,int key) {
    struct BlockTag *hashTableStoresInThisBlock;//to store getter

    HASH_FIND_INT(*HashTable, &key, hashTableStoresInThisBlock);  /* id already in the hash? */
    if (hashTableStoresInThisBlock==NULL) {
        hashTableStoresInThisBlock = (struct BlockTag*)malloc(sizeof(struct BlockTag));
        hashTableStoresInThisBlock->useFrequency = key;
        HASH_ADD_INT( *HashTable, useFrequency, hashTableStoresInThisBlock );  /* id: name of key field */
    }
}
void replace(UT_hash_handle hh,Block** HashTable,Block *value) {
    struct BlockTag *hashTableStoresInThisBlock;//to store getter

    HASH_FIND_STR( *HashTable, value->address.bitString, hashTableStoresInThisBlock );
    if (hashTableStoresInThisBlock==NULL) {
        hashTableStoresInThisBlock = (struct BlockTag*)malloc(sizeof(struct BlockTag));
        strcpy(hashTableStoresInThisBlock->address.bitString,value->address.bitString);
        HASH_ADD_STR(*HashTable, address.bitString,value);
    }
}

//look up item in hashmap
Block* getByUseFrequency(Block** HashTable,int key) {
    Block *hashTableStoresInThisBlock;

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into s
    return hashTableStoresInThisBlock;
}
Block* get(Block** HashTable,char* key) {
    Block *hashTableStoresInThisBlock;

    HASH_FIND_STR( *HashTable, key, hashTableStoresInThisBlock );//find block_id and put into hashTableStoresInThisBlock
    return hashTableStoresInThisBlock;
}


//delete from hashmap
void removeFromTable(Block** HashTable,Block *blockToRemove) {
    HASH_DEL( *HashTable, blockToRemove);//removes blocks of type block
}

//Delete all items from hash
void delete_all(Block** HashTable) {
    struct BlockTag *current_block, *tmp;

    HASH_ITER(hh, *HashTable, current_block, tmp) {
        HASH_DEL(*HashTable,current_block);  /* delete; users advances to next */
        free(current_block);            /* optional- if you want to free  */
    }
}

//count items
int Count(Block** HashTable){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(*HashTable);
    return num_in_hashtable;
}

void print_blocks_in_set(Block** HashTable) {
    Block* s;
    Block* tmp;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("address: %s, LFU:%d\n",s->address.bitString,s->useFrequency);
    }
}

int block_comparator(Block* a,Block* b){
    if (a->useFrequency < b->useFrequency){
        return -1;
    }
    if (a->useFrequency == b->useFrequency){
        return 0;
    }
    if (a->useFrequency > b->useFrequency){
        return 1;
    }
}

void SortHash(Block** HashTable){
    HASH_SORT(*HashTable,block_comparator);
}