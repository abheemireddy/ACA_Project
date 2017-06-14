//
// Created by chad on 6/5/17.
//

#ifndef ACA_PROJECT_DRAM_H
#define ACA_PROJECT_DRAM_H
#include "uthash.h"
#include "Address/Address.h"
#include "Block/Block.h"

typedef struct TransfererTag Transferer;
typedef struct BlockQueueTag BlockQueue;
typedef struct BlockOnBusTag BlockOnBus;

typedef struct DRAMTag {
    Transferer* transferer;
    UT_hash_handle hh; /* make this structure hashable*/
    BlockOnBus *HashTable; //This is my hashTable for blocks
    BlockQueue* writeBlockQueue;
} DRAM;

DRAM* Constructor_DRAM();

void removeBlockFromDRAM(BlockOnBus** HashTable,BlockOnBus* blockToRemove);
void putBlock(BlockOnBus** HashTable,BlockOnBus *value);
int CountBlocks(BlockOnBus** HashTable);
BlockOnBus* getBlock(BlockOnBus** HashTable,int key);
void print_all_blocks(BlockOnBus** HashTable);

BlockOnBus* Constructor_BlockOnBusDRAM(Block* block);
#endif //ACA_PROJECT_DRAM_H
