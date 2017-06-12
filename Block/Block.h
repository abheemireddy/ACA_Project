//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_BLOCK_H
#define ACA_PROJECT_BLOCK_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <printf.h>
#include "uthash_files/include/uthash.h"
#include "Address/Address.h"

typedef struct CacheLineTag CacheLine;

typedef struct BlockTag{
    int size;

    bool isIdle;

    bool validBit;
    bool dirtyBit;

    int useFrequency;//for LRU in Set
    //CacheLine** cacheLines;//number in array is the number of cache lines in the block
    CacheLine *HashTable;

    Address address;

    void (*Set_Offset)(struct CacheLineTag* block,char* offset);
    bool (*IsInBlock)(Address address);

    void (*putCacheLine)(struct CacheLineTag** HashTable, struct CacheLineTag* value);
    struct CacheLineTag* (*getCacheLineByOffset)(struct CacheLineTag** HashTable,int key);
    void (*removeCacheLineFromTable)(struct CacheLineTag** HashTable,struct CacheLineTag* blockToRemove);
    void (*deleteAllCacheLine)(struct CacheLineTag** HashTable);
    int (*CountCacheLines)(struct CacheLineTag** HashTable);
    void (*replaceCacheLine)(UT_hash_handle hh,struct CacheLineTag** HashTable,struct CacheLineTag* value);
    struct CacheLineTag* (*getCacheLine)(struct CacheLineTag** HashTable,char* key);
    void (*print_cache_lines_in_set)(struct CacheLineTag** HashTable);


    UT_hash_handle hh; /* make this structure hashable*/
} Block;//Block is synonymous for struct BlockTag (they mean the same thing).

Block* Constructor_Block(Address address);

void Set_Offset(struct CacheLineTag* block,char* offset);
void IncrementBlockFrequency(Block** block);
bool IsInBlock(Address address);


void putCacheLine(struct CacheLineTag** HashTable, struct CacheLineTag* value);
struct CacheLineTag* getCacheLineByOffset(struct CacheLineTag** HashTable,int key);
void removeCacheLineFromTable(struct CacheLineTag** HashTable,struct CacheLineTag* blockToRemove);
void deleteAllCacheLine(struct CacheLineTag** HashTable);
int CountCacheLines(struct CacheLineTag** HashTable);
void replaceCacheLine(UT_hash_handle hh,struct CacheLineTag** HashTable,struct CacheLineTag* value);
struct CacheLineTag* getCacheLine(struct CacheLineTag** HashTable,char* key);
void print_cache_lines_in_set(struct CacheLineTag** HashTable);

#endif //ACA_PROJECT_BLOCK_H
