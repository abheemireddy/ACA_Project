//
// Created by chad on 6/5/17.
//

#ifndef ACA_PROJECT_DRAM_H
#define ACA_PROJECT_DRAM_H

#include <uthash.h>

struct BlockTag;//forward declaration

typedef struct DRAMTag {
    UT_hash_handle hh; /* make this structure hashable*/
    struct BlockTag *HashTable; //This is my hashTable for blocks

    void (*put)(struct BlockTag** HashTable,struct BlockTag *value);
    int (*Count)(struct BlockTag** HashTable);
    struct BlockTag* (*get)(struct BlockTag** HashTable,char* key);
    void (*print_all_blocks)(struct BlockTag** HashTable);

} DRAM;

#endif //ACA_PROJECT_DRAM_H
