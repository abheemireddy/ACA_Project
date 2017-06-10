//
// Created by chad on 5/25/17.
//

#include <printf.h>
#include "Cache.h"

Cache* Constructor_Cache(int numberOfSets){
    Cache* cache = malloc(sizeof(Cache));
    cache->NumberOfSets = numberOfSets;
    cache->HashTable = NULL;
    cache->getSetByIndex = &getSetByIndex;
    cache->putSet = &putSet;
    cache->removeSetFromTable = &removeSetFromTable;
    cache->deleteAllSet = &deleteAllSet;
    cache->CountSets = &CountSets;
    cache->replaceSet = &replaceSet;
    cache->print_sets = &print_sets;
    int i;
    int setAddress = 0;
    for(i = 0;i<cache->NumberOfSets;i++){
        printf("cache on set number:%d\n",i);
        char bitString[18];
        strcpy(bitString,int2bin(setAddress));
        Address* address = Constructor_Address(bitString);
        Set* set = Constructor_Set(4,*address);
        cache->putSet(&cache->HashTable,set);
        setAddress += 8;
    }
    return cache;
}

void putSet(Set** HashTable,Set* value) {  //key is useFrequency of the block.  Seems magical
    HASH_ADD_INT(*HashTable, address.Index, value );
    //The last parameter is a pointer to the structure being added
}

void replaceSet(UT_hash_handle hh,Set** HashTable,Set *value) {
    Set *hashTableStoresInThis;//to store getter

    HASH_FIND_INT( *HashTable, &value->address.Index, hashTableStoresInThis );
    if (hashTableStoresInThis==NULL) {
        hashTableStoresInThis = (Set*)malloc(sizeof(Set));
        hashTableStoresInThis->address.Index = value->address.Index;
        HASH_ADD_INT(*HashTable, address.Index, value );
    }
}

//look up item in hashmap
Set* getSetByIndex(Set** HashTable,int key) {
    Set* hashTableStoresInThisBlock;

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into s
    return hashTableStoresInThisBlock;
}

//delete from hashmap
void removeSetFromTable(Set** HashTable,Set* blockToRemove) {
    HASH_DEL( *HashTable, blockToRemove);//removes blocks of type block
}

//Delete all items from hash
void deleteAllSet(Set** HashTable) {
    Set *current_block, *tmp;

    HASH_ITER(hh, *HashTable, current_block, tmp) {
        HASH_DEL(*HashTable,current_block);  /* delete; users advances to next */
        free(current_block);            /* optional- if you want to free  */
    }
}

//count items
int CountSets(Set** HashTable){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(*HashTable);
    return num_in_hashtable;
}

void print_sets(Set** HashTable) {
    Set* s;
    Set* tmp;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("address.Index: %d",s->address.Index);
    }
}

