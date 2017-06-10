//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_CACHE_H
#define ACA_PROJECT_CACHE_H
#include "Set/Set.h"
#include <stdlib.h>
#include <stdio.h>
#include <BlockTransferer/BlockTransferer.h>

typedef struct CacheTag{
    Set *HashTable;
    int NumberOfSets;

    void (*putSet)(Set** HashTable, Set* value);
    Set* (*getSetByIndex)(Set** HashTable,int key);
    void (*removeSetFromTable)(Set** HashTable,Set* blockToRemove);
    void (*deleteAllSet)(Set** HashTable);
    int (*CountSets)(Set** HashTable);
    void (*replaceSet)(UT_hash_handle hh,Set** HashTable,Set* value);
    Set* (*getSet)(Set** HashTable,char* key);
    void (*print_sets)(Set** HashTable);
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
