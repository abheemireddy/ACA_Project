//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_SET_H
#define ACA_PROJECT_SET_H
#include "uthash.h"

struct BlockTag;//forward declaration

typedef struct SetTag { //4 blocks per set, 4000 blocks in cache = 1000 sets, 64KB/16B = 4000

    int numberOfBlocks;

    void (*put)(struct BlockTag** HashTable,struct BlockTag *value);
    void (*replace)(struct BlockTag** HashTable,int key);
    struct BlockTag* (*get)(struct BlockTag** HashTable,int key);
    void (*removeFromTable)(struct BlockTag** HashTable,struct BlockTag *blockToRemove);
    void (*delete_all)(struct BlockTag** HashTable);
    int (*Count)(struct BlockTag** HashTable);

    //---------Used in HashMap
    int index;/* use this field as the key */
    UT_hash_handle hh; /* make this structure hashable*/
    //---------Used in HashMap

    struct BlockTag *HashTable; //This is my hashTable for blocks
    //contain blocks
    //maybe store how many blocks
} Set;

Set Constructor_Set(int numberOfBlocks);

void put(struct BlockTag** HashTable,struct BlockTag *value);
void replace(struct BlockTag** HashTable,int key);
struct BlockTag* get(struct BlockTag** HashTable,int key);
void removeFromTable(struct BlockTag** HashTable,struct BlockTag *blockToRemove);
void delete_all(struct BlockTag** HashTable);
int Count(struct BlockTag** HashTable);

#endif //ACA_PROJECT_SET_H
