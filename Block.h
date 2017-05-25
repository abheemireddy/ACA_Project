//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_BLOCK_H
#define ACA_PROJECT_BLOCK_H
#include <stdbool.h>
#include "uthash/include/uthash.h"//troydhanson.github.io/uthash

typedef struct BlockTag{
    int size;

    bool validBit;
    bool dirtyBit;

    int useFrequency;


    UT_hash_handle hh; /* make this structure hashable*/
} Block;//Block is synonymous for struct BlockTag (they mean the same thing).

Block Constructor_Block();//construct to call to obtain a Block Instance

#endif //ACA_PROJECT_BLOCK_H
