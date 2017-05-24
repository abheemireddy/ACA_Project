//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_BLOCK_H
#define ACA_PROJECT_BLOCK_H
#include <stdbool.h>
#include "uthash/include/uthash.h"//troydhanson.github.io/uthash

typedef struct BlockTag{
    //Used in HashMap
    int id; /* use this field as the key */
    UT_hash_handle hh; /* make this structure hashable*/
    //Used in HashMap

    struct BlockTag (*Constructor)(int id,int offset);
    int (*func)(int x , int y);

    bool validBit;
    bool dirtyBit;
    int tag;//set associative, so offset refers to the block
    int size;//64 byte block size
} Block;

Block BlockConstructor(int id,int offset);

#endif //ACA_PROJECT_BLOCK_H
