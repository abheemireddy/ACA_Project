//
// Created by chad on 5/24/17.
//
#include "Block.h"
#include "CacheLine/CacheLine.h"

Block* Constructor_Block(Address address){
    Block* block = malloc(sizeof(Block));
    block->dirtyBit = false;
    block->validBit = false;
    block->useFrequency = 0;
    block->address = address;
    block->isIdle = false;
    block->HashTable = NULL;

    /*int i;
    int cacheAddressValue = address.bitStringValue;
    for(i = 0;i<8;i++){
        char* bitString = int2bin(cacheAddressValue);
        Address* cacheAddress = Constructor_Address(bitString);
        CacheLine* cacheLine = Constructor_CacheLine(*cacheAddress,"No Data Yet");
        block->validBit = false;
        putCacheLine(&block->HashTable,cacheLine);
        cacheAddressValue += 1;
    }*/
    return block;
}

void Set_Data(Block* block,Address address){
    block->address = address;
}

void IncrementBlockFrequency(Block** block){
    (*block)->useFrequency += 1;
}


bool IsInBlock(Address address){
    return true;
}

void putCacheLine(CacheLine** HashTable,CacheLine* value) {  //key is useFrequency of the block.  Seems magical
    if(value->address.bitString == NULL){
        printf("The passed block needs to have attribute address.bitString set");
    }
    HASH_ADD_INT(*HashTable, address.Offset, value );
    //The last parameter is a pointer to the structure being added
}

void replaceCacheLine(UT_hash_handle hh,CacheLine** HashTable,CacheLine *value) {
    CacheLine *hashTableStoresInThis;//to store getter

    HASH_FIND_INT( *HashTable, &value->address.Offset, hashTableStoresInThis );
    if (hashTableStoresInThis==NULL) {
        hashTableStoresInThis = (CacheLine*)malloc(sizeof(CacheLine));
        strcpy(hashTableStoresInThis->address.bitString,value->address.bitString);
        HASH_ADD_INT(*HashTable, address.Offset, value );
    }
}

//look up item in hashmap
CacheLine* getCacheLineByOffset(CacheLine** HashTable,int key) {
    CacheLine* hashTableStoresInThisBlock = malloc(sizeof(CacheLine));

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into s
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
    CacheLine* s  = malloc(sizeof(CacheLine));
    CacheLine* tmp = malloc(sizeof(CacheLine));
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("address.bitString: %s",s->address.bitString);
    }
}

