//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_HASHMAP_H
#define ACA_PROJECT_HASHMAP_H
//example of using hashMap

#include "uthash.h"
#include "Block.h"

struct my_struct {
    int id;            /* we'll use this field as the key */
    char name[10];
    UT_hash_handle hh; /* makes this structure hashable */
};

Block *block = NULL;

void add_user(Block *s) {
    HASH_ADD_INT( block, id, s );
}

//look up item in hashmap
Block *find_user(int block_id) {
    Block *s;

    HASH_FIND_INT( block, &block_id, s );
    return s;
}


//delete from hashmap
void delete_user(Block *blocks) {
    HASH_DEL( block, blocks);
}


#endif //ACA_PROJECT_HASHMAP_H
