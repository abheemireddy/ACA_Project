//
// Created by chad on 6/5/17.
//

#ifndef ACA_PROJECT_DRAM_H
#define ACA_PROJECT_DRAM_H
#include "uthash.h"
#include "Address/Address.h"

typedef struct TransfererTag Transferer;
typedef struct BlockQueueTag BlockQueue;

typedef struct DRamBlockTag{
    Address address;
    char data[64];
    UT_hash_handle hh; /* make this structure hashable*/
} DRamBlock;

DRamBlock* Constructor_DRamBlock(Address address,char value[64]);

typedef struct DRAMTag {
    Transferer* transferer;
    UT_hash_handle hh; /* make this structure hashable*/
    DRamBlock *HashTable; //This is my hashTable for blocks
    BlockQueue* writeBlockQueue;
} DRAM;

DRAM Constructor_DRAM();

void removeBlockFromDRAM(DRamBlock** HashTable,DRamBlock* blockToRemove);
void putBlock(DRamBlock** HashTable,DRamBlock *value);
int CountBlocks(DRamBlock** HashTable);
DRamBlock* getBlock(DRamBlock** HashTable,int key);
void print_all_blocks(DRamBlock** HashTable);

#endif //ACA_PROJECT_DRAM_H
