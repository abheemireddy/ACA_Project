//
// Created by chad on 6/3/17.
//

#ifndef ACA_PROJECT_BLOCK_CACHE_HASHTABLE_H
#define ACA_PROJECT_BLOCK_CACHE_HASHTABLE_H

#include <uthash/include/uthash.h>
#include "Block.h"

void put(struct CacheLineTag** HashTable, struct CacheLineTag* value);
struct CacheLineTag* getByAddress(struct CacheLineTag** HashTable,int key);
void removeFromTable(struct CacheLineTag** HashTable,struct CacheLineTag* blockToRemove);
void delete_all(struct CacheLineTag** HashTable);
int Count(struct CacheLineTag** HashTable);
void replace(UT_hash_handle hh,struct CacheLineTag** HashTable,struct CacheLineTag* value);
struct CacheLineTag* get(struct CacheLineTag** HashTable,char* key);
void SortHash(struct CacheLineTag** HashTable);
void print_cache_lines_in_set(struct CacheLineTag** HashTable);


#endif //ACA_PROJECT_BLOCK_CACHE_HASHTABLE_H
