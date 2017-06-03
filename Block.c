//
// Created by chad on 5/24/17.
//
#include "Block.h"

Block Constructor_Block(char* address){
    Block block = {dirtyBit:false,validBit:false,useFrequency:0,address:address};
    //*block.cacheLines = (struct CacheLineTag*)malloc(numberOfCacheLines*sizeof(struct CacheLineTag));
    block.IsInBlock = &IsInBlock;

    //HashTable Functions
    block.putCacheLine = &putCacheLine;
    block.replaceCacheLine = &replaceCacheLine;
    block.getCacheLine = &getCacheLine;
    block.getCacheLineByAddress = &getCacheLineByAddress;
    block.removeCacheLineFromTable = &removeCacheLineFromTable;
    block.deleteAllCacheLine = &deleteAllCacheLine;
    block.CountCacheLines = &CountCacheLines;
    block.print_cache_lines_in_set = &print_cache_lines_in_set;
    block.HashTable = NULL;
    return block;
}
/*
void (*putCacheLine)(struct CacheLineTag** HashTable, struct CacheLineTag* value);
struct CacheLineTag* (*getCacheLineByAddress)(struct CacheLineTag** HashTable,int key);
void (*removeCacheLineFromTable)(struct CacheLineTag** HashTable,struct CacheLineTag* blockToRemove);
void (*deleteAllCacheLine)(struct CacheLineTag** HashTable);
int (*CountCacheLines)(struct CacheLineTag** HashTable);
void (*replaceCacheLine)(UT_hash_handle hh,struct CacheLineTag** HashTable,struct CacheLineTag* value);
struct CacheLineTag* (*getCacheLine)(struct CacheLineTag** HashTable,char* key);
void (*print_cache_lines_in_set)(struct CacheLineTag** HashTable);
*/

void Set_Data(Block* block,char* address){
    block->address = address;
}

void SetCacheLines(Block block,CacheLine* cacheLines[]){
    block.cacheLines = cacheLines;
}

void IncrementBlockFrequency(Block** block){
    (*block)->useFrequency += 1;
}


bool IsInBlock(char* offset){
    return true;
}

void putCacheLine(CacheLine** HashTable,CacheLine* value) {  //key is useFrequency of the block.  Seems magical
    if(value->offset == NULL){
        printf("The passed block needs to have attribute offset set");
    }
    HASH_ADD_KEYPTR(hh,*HashTable, value->offset, strlen(value->offset),value );
    //The last parameter is a pointer to the structure being added
}

void replaceCacheLine(UT_hash_handle hh,CacheLine** HashTable,CacheLine *value) {
    CacheLine *hashTableStoresInThisBlock;//to store getter

    HASH_FIND_STR( *HashTable, value->offset, hashTableStoresInThisBlock );
    if (hashTableStoresInThisBlock==NULL) {
        hashTableStoresInThisBlock = (CacheLine*)malloc(sizeof(CacheLine));
        hashTableStoresInThisBlock->offset = value->offset;
        HASH_ADD_KEYPTR(hh,*HashTable, value->offset, strlen(value->offset),value );
    }
}

//look up item in hashmap
CacheLine* getCacheLineByAddress(CacheLine** HashTable,int key) {
    CacheLine* hashTableStoresInThisBlock;

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into s
    return hashTableStoresInThisBlock;
}
CacheLine* getCacheLine(CacheLine** HashTable,char* key) {
    CacheLine* hashTableStoresInThisBlock;

    HASH_FIND_STR( *HashTable, key, hashTableStoresInThisBlock );//find block_id and put into hashTableStoresInThisBlock
    return hashTableStoresInThisBlock;
}

//delete from hashmap
void removeCacheLineFromTable(CacheLine** HashTable,CacheLine* blockToRemove) {
    HASH_DEL( *HashTable, blockToRemove);//removes blocks of type block
}

//Delete all items from hash
void deleteAllCacheLine(CacheLine** HashTable) {
    CacheLine *current_block, *tmp;

    HASH_ITER(hh, *HashTable, current_block, tmp) {
        HASH_DEL(*HashTable,current_block);  /* delete; users advances to next */
        free(current_block);            /* optional- if you want to free  */
    }
}

//count items
int CountCacheLines(CacheLine** HashTable){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(*HashTable);
    return num_in_hashtable;
}

void print_cache_lines_in_set(CacheLine** HashTable) {
    CacheLine* s;
    CacheLine* tmp;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("offset: %s",s->offset);
    }
}

