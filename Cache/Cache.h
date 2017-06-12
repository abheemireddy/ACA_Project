//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_CACHE_H
#define ACA_PROJECT_CACHE_H
#include <stdlib.h>
#include <stdio.h>
#include "uthash_files/include/uthash.h"

typedef struct SetTag Set;

typedef struct CacheTag{
    Set *HashTable;
    int NumberOfSets;
} Cache;

Cache* Constructor_Cache(int numberOfSets);

void putSet( Set** HashTable,  Set* value);
 Set* getSetByIndex( Set** HashTable,int key);
void removeSetFromTable( Set** HashTable, Set* blockToRemove);
void deleteAllSet( Set** HashTable);
int CountSets( Set** HashTable);
void replaceSet(UT_hash_handle hh, Set** HashTable, Set* value);
void print_sets( Set** HashTable);

#endif //ACA_PROJECT_CACHE_H
