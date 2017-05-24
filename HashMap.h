//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_HASHMAP_H
#define ACA_PROJECT_HASHMAP_H
//example of using hashMap

#include "uthash.h"
#include "Block.h"


Block *block = NULL;

void add_user(Block *s) {
    HASH_ADD_INT( block, id, s );//add s and id to hashmap
}

//look up item in hashmap
Block *find_user(int block_id) {
    Block *s;

    HASH_FIND_INT( block, &block_id, s );//find block_id and put into s
    return s;
}


//delete from hashmap
void delete_user(Block *blocks) {
    HASH_DEL( block, blocks);//removes blocks of type block
}


#endif //ACA_PROJECT_HASHMAP_H
