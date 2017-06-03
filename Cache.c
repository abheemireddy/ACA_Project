//
// Created by chad on 5/25/17.
//

#include <printf.h>
#include "Cache.h"

Cache Constructor_Cache(int setAssociativity){
    Cache cache = {setAssociativity:setAssociativity};
    cache.getSetByIndex = &getSetByIndex;
    cache.putSet = &putSet;
    cache.removeSetFromTable = &removeSetFromTable;
    cache.deleteAllSet = &deleteAllSet;
    cache.CountSets = &CountSets;
    cache.replaceSet = &replaceSet;
    cache.print_sets = &print_sets;
    return cache;
}

/*
 *
 * void putSet(struct Set** HashTable, struct Set* value);
struct Set* getSetByOffset(struct Set** HashTable,int key);
void removeSetFromTable(struct Set** HashTable,struct Set* blockToRemove);
void deleteAllSet(struct Set** HashTable);
int CountSets(struct Set** HashTable);
void replaceSet(UT_hash_handle hh,struct Set** HashTable,struct Set* value);
struct Set* getSet(struct Set** HashTable,char* key);
void print_cache_lines_in_set(struct Set** HashTable);
 */


void putSet(Set** HashTable,Set* value) {  //key is useFrequency of the block.  Seems magical
    if(value->address.bitString == NULL){
        printf("The passed block needs to have attribute address.bitString set");
    }
    HASH_ADD_INT(*HashTable, address.Offset, value );
    //The last parameter is a pointer to the structure being added
}

void replaceSet(UT_hash_handle hh,Set** HashTable,Set *value) {
    Set *hashTableStoresInThis;//to store getter

    HASH_FIND_INT( *HashTable, &value->address.Offset, hashTableStoresInThis );
    if (hashTableStoresInThis==NULL) {
        hashTableStoresInThis = (Set*)malloc(sizeof(Set));
        hashTableStoresInThis->address.bitString = value->address.bitString;
        HASH_ADD_INT(*HashTable, address.Offset, value );
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
        printf("address.bitString: %s",s->address.bitString);
    }
}

