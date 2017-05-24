//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_SET_H
#define ACA_PROJECT_SET_H
#include "uthash.h"

struct BlockTag;//forward declaration

typedef struct SetTag { //4 blocks per set, 4000 blocks in cache = 1000 sets, 64KB/16B = 4000

    int size; //4 in 4 way set-associative

    int (*close)(void *self);
    void (*Add_Block)(struct BlockTag* s);
    struct BlockTag* (*Get_Block)(int block_id);
    void (*Delete_Block)(struct BlockTag* blocks);

    //---------Used in HashMap
    int index;/* use this field as the key */
    UT_hash_handle hh; /* make this structure hashable*/
    //---------Used in HashMap

    //contain blocks
    //maybe store how many blocks
} Set;


void Add_Block(struct BlockTag *s);
struct BlockTag* Get_Block(int block_id);
void Delete_Block(struct BlockTag *blocks);

#endif //ACA_PROJECT_SET_H
