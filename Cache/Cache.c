//
// Created by chad on 5/25/17.
//
#include "Cache.h"
#include "Global_Variables.h"
#include "Set/Set.h"
#include "BlockTransferer/BlockTransferer.h"
#include "Set/Set.h"

Cache* Constructor_Cache(int numberOfSets){
    Cache* cache = malloc(sizeof(Cache));
    cache->NumberOfSets = numberOfSets;
    cache->HashTable = NULL;
    int i;
    int setAddress = 0;
    for(i = 0;i<cache->NumberOfSets;i++){
        char bitString[18];
        strcpy(bitString,int2bin(setAddress));
        Address* address = malloc(sizeof(Address));
        if(numberOfSets == 1024){
            address = Constructor_AddressConvertForL2(bitString);
        }else if(numberOfSets == 512){
            address = Constructor_Address(bitString);
        }
        Set* set = Constructor_Set(4,*address);
        putSet(&cache->HashTable,set);
        setAddress += 8;
    }
    return cache;
}

void putSet(Set** HashTable,Set* value) {  //key is useFrequency of the block.  Seems magical
    Set *hashTableStoresInThisBlock = malloc(sizeof(Set));
    Set* tmp = malloc(sizeof(Set));;
    HASH_REPLACE_INT(*HashTable, address.Index, value,tmp );
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
    Set* hashTableStoresInThisBlock = malloc(sizeof(Set));

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into s
    return hashTableStoresInThisBlock;
}

//delete from hashmap
void removeSetFromTable(Set** HashTable,Set* blockToRemove) {
    HASH_DEL( *HashTable, blockToRemove);//removes blocks of type block
}

//Delete all items from hash
void deleteAllSet(Set** HashTable) {
    Set *current_block = malloc(sizeof(Set));
    Set* tmp = malloc(sizeof(Set));

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
    Set* s = malloc(sizeof(Set));
    Set* tmp = malloc(sizeof(Set));
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("address.Index: %d",s->address.Index);
    }
}

