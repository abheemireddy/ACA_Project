//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_BLOCK_H
#define ACA_PROJECT_BLOCK_H
#include <stdbool.h>
#include "uthash/include/uthash.h"//troydhanson.github.io/uthash

typedef struct BlockTag{
    //Used in HashMap
    int tag; /* use this field as the key */
    UT_hash_handle hh; /* make this structure hashable*/
    //Used in HashMap

    //Anu, use this to get the Block
    struct BlockTag (*Constructor)(int id,int offset);
    int (*func)(int x , int y);

    bool validBit;
    bool dirtyBit;
    int size;//64 byte block size
} Block;//Block is synonymous for struct BlockTag (they mean the same thing).



Block BlockConstructor(int tag);//function header

#endif //ACA_PROJECT_BLOCK_H
