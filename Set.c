//
// Created by chad on 5/24/17.
//

#include "Block.h"
#include "Set.h"
#include <stdio.h>


Set Constructor_Set(){
    Set set = {};
    set.put = &put;
    set.Add_Or_Replace = &Add_Or_Replace;
    set.get = &get;
    set.removeFromTable = &removeFromTable;
    set.delete_all = &delete_all;
    set.Count = &Count;
    set.HashTable = NULL;
    return set;
}

void put(Block** HashTable,Block *value) {  //key is tag of the block.  Seems magical
    HASH_ADD_INT( *HashTable, tag, value );//add s and id to hashmap
    //The last parameter is a pointer to the structure being added
}

//HASH_REPLACE  is equivalent to HASH_ADD but it finds and deletes that item first
void Add_Or_Replace(Block** HashTable,int key) {
    struct BlockTag *hashTableStoresInThisBlock;//to store getter

    HASH_FIND_INT(*HashTable, &key, hashTableStoresInThisBlock);  /* id already in the hash? */
    if (hashTableStoresInThisBlock==NULL) {
        hashTableStoresInThisBlock = (struct BlockTag*)malloc(sizeof(struct BlockTag));
        hashTableStoresInThisBlock->tag = key;
        HASH_ADD_INT( *HashTable, tag, hashTableStoresInThisBlock );  /* id: name of key field */
    }
}


//look up item in hashmap
Block* get(Block** HashTable,int key) {
    Block *hashTableStoresInThisBlock;

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into s
    return hashTableStoresInThisBlock;
}

//delete from hashmap
void removeFromTable(Block** HashTable,Block *blockToRemove) {
    HASH_DEL( *HashTable, blockToRemove);//removes blocks of type block
}

//Delete all items from hash
void delete_all(Block** HashTable) {
    struct BlockTag *current_block, *tmp;

    HASH_ITER(hh, *HashTable, current_block, tmp) {
        HASH_DEL(*HashTable,current_block);  /* delete; users advances to next */
        free(current_block);            /* optional- if you want to free  */
    }
}

//count items
int Count(Block** HashTable){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(*HashTable);
    return num_in_hashtable;
}
