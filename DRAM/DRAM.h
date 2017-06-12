//
// Created by chad on 6/5/17.
//

#ifndef ACA_PROJECT_DRAM_H
#define ACA_PROJECT_DRAM_H
#include "uthash.h"

typedef struct TransfererTag Transferer;
typedef struct BlockQueueTag BlockQueue;

typedef struct DRAMTag {
    Transferer* transferer;
    UT_hash_handle hh; /* make this structure hashable*/
    struct BlockTag *HashTable; //This is my hashTable for blocks
    BlockQueue* blockQueue;

    void (*removeBlockFromDRAM)(struct BlockTag** HashTable,struct BlockTag* blockToRemove);
    void (*putBlock)(struct BlockTag** HashTable,struct BlockTag *value);
    int (*CountBlocks)(struct BlockTag** HashTable);
    struct BlockTag* (*getBlock)(struct BlockTag** HashTable,int key);
    void (*print_all_blocks)(struct BlockTag** HashTable);

} DRAM;

DRAM Constructor_DRAM();

void removeBlockFromDRAM(struct BlockTag** HashTable,struct BlockTag* blockToRemove);
void putBlock(struct BlockTag** HashTable,struct BlockTag *value);
int CountBlocks(struct BlockTag** HashTable);
struct BlockTag* getBlock(struct BlockTag** HashTable,int key);
void print_all_blocks(struct BlockTag** HashTable);

#endif //ACA_PROJECT_DRAM_H
