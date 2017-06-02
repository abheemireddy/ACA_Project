//
// Created by chad on 5/24/17.
//

#include "Block.h"
#include "Set.h"
#include <stdio.h>


Set Constructor_Set(int numberOfBlocks){
    Set set = {numberOfBlocks:numberOfBlocks};
    set.put = &put;
    set.replace = &replace;
    set.get = &get;
    set.SortHash = &SortHash;
    set.AddBlock = &AddBlock;
    set.getByUseFrequency = &getByUseFrequency;
    set.removeFromTable = &removeFromTable;
    set.delete_all = &delete_all;
    set.Count = &Count;
    set.replaceByUseFrequency = &replaceByUseFrequency;
    set.print_blocks_in_set = &print_blocks_in_set;
    set.HashTable = NULL;
    return set;
}

void AddBlock(Set set,Block** HashTable,struct BlockTag* blockToAdd){
    int blocksInSet = set.Count(HashTable);
    if(blocksInSet < set.numberOfBlocks){
        set.put(&set.hh,HashTable,blockToAdd);
    }else{
        set.SortHash(HashTable);
        Block* blockToRemove = (*HashTable)->hh.next;
        if(blockToRemove->dirtyBit == false){
            set.removeFromTable(HashTable,(*HashTable)->hh.next);//remove block from top of hash
        }else {
            //write to L2 via the L2 Queue
        }
    }
}


void put(UT_hash_handle* hh,Block** HashTable,Block *value) {  //key is useFrequency of the block.  Seems magical
    if(value->data == NULL){
        printf("The passed block needs to have attribute data set");
    }
    HASH_ADD_KEYPTR(hh,*HashTable, value->data, strlen(value->data),value );
    //The last parameter is a pointer to the structure being added
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

    HASH_FIND_STR( *HashTable, value->data, hashTableStoresInThisBlock );
    if (hashTableStoresInThisBlock==NULL) {
        hashTableStoresInThisBlock = (struct BlockTag*)malloc(sizeof(struct BlockTag));
        hashTableStoresInThisBlock->data = value->data;
        HASH_ADD_KEYPTR(hh,*HashTable, value->data, strlen(value->data),value );
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

void print_blocks_in_set(Set set,Block** HashTable) {
    Block* s;
    Block* tmp;
    struct UT_hash_handle hh = set.hh;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("%s",s->data);
    }
}

int block_comparator(void* a,void* b){
    Block* aBlock = (Block*)a;
    Block* bBlock = (Block*)b;
    if (aBlock->useFrequency < bBlock->useFrequency){
        return -1;
    }
    if (aBlock->useFrequency == bBlock->useFrequency){
        return 0;
    }
    if (aBlock->useFrequency > bBlock->useFrequency){
        return 1;
    }
}

void SortHash(Block** HashTable){
    HASH_SORT(*HashTable,block_comparator);
}