//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_BLOCK_H
#define ACA_PROJECT_BLOCK_H
#include <stdbool.h>
#include "uthash/include/uthash.h"//troydhanson.github.io/uthash

typedef struct BlockTag{
    //Used in HashMap
    int size; /* use this field as the key */
    UT_hash_handle hh; /* make this structure hashable*/
    //Used in HashMap

    bool validBit;
    bool dirtyBit;
    int offset;//set associative, so offset refers to the block
    int blockSize;//16 KB
} Block;

#endif //ACA_PROJECT_BLOCK_H
