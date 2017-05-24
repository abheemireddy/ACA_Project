//
// Created by chad on 5/24/17.
//

#include "Block.h"
#include "Set.h"
#include <stdio.h>

Block *HashTable = NULL;

void Add_Block(Block *s) { //The first parameter to HASH_ADD_INT  is the hash table.  the second parameter is the NAME of the key field in the object.  This is macro magic
    HASH_ADD_INT( HashTable, id, s );//add s and id to hashmap
    //The last parameter is a pointer to the structure being added
}


//HASH_REPLACE  is equivalent to HASH_ADD but it finds and deletes that item first
void Add_Block_Check_If_Exists(int id, Block* value) {
    struct BlockTag *s;

    HASH_FIND_INT(HashTable, &id, s);  /* id already in the hash? */
    if (s==NULL) {
        s = (struct my_struct*)malloc(sizeof(struct my_struct));
        s->id = id;
        HASH_ADD_INT( HashTable, id, s );  /* id: name of key field */
    }
}




//look up item in hashmap
Block* Get_Block(int block_id) {
    Block *s;

    HASH_FIND_INT( HashTable, &block_id, s );//find block_id and put into s
    return s;
}


//delete from hashmap
void Delete_Block(Block *blocks) {
    HASH_DEL( HashTable, blocks);//removes blocks of type block
}

void InitializeSet(){
    Set set = {};
    set.Add_Block = Add_Block;
    set.Get_Block = Get_Block;
    set.Delete_Block = Delete_Block;
}

//Delete all items from hash
void delete_all() {
    struct BlockTag *current_block, *tmp;

    HASH_ITER(hh, HashTable, current_block, tmp) {
        HASH_DEL(HashTable,current_block);  /* delete; users advances to next */
        free(current_block);            /* optional- if you want to free  */
    }
}

//count items
int Count(){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(HashTable);
    return num_in_hashtable;
}
