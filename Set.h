//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_SET_H
#define ACA_PROJECT_SET_H
#include "uthash.h"

struct BlockTag;//forward declaration

typedef struct SetTag {

    int numberOfBlocks;

    void (*put)(UT_hash_handle hh,struct BlockTag** HashTable,struct BlockTag *value);
    void (*replaceByUseFrequency)(struct BlockTag** HashTable,int key);
    struct BlockTag* (*getByUseFrequency)(struct BlockTag** HashTable,int key);
    void (*removeFromTable)(struct BlockTag** HashTable,struct BlockTag *blockToRemove);
    void (*delete_all)(struct BlockTag** HashTable);
    int (*Count)(struct BlockTag** HashTable);

    void (*replace)(UT_hash_handle hh,struct BlockTag** HashTable,struct BlockTag *value);
    struct BlockTag* (*get)(struct BlockTag** HashTable,char* key);

    int tag;
    int index;
    int offset;

    //---------Used in Cache HashMap to find set
    UT_hash_handle hh; /* make this structure hashable*/
    //---------Used in HashMap

    struct BlockTag *HashTable; //This is my hashTable for blocks
    //contain blocks
    //maybe store how many blocks
} Set;

Set Constructor_Set(int numberOfBlocks);
void AddBlock(struct BlockTag* block);

//HashTable functions
void put(UT_hash_handle hh,struct BlockTag** HashTable,struct BlockTag *value);
void replaceByUseFrequency(struct BlockTag** HashTable,int key);
struct BlockTag* getByUseFrequency(struct BlockTag** HashTable,int key);
void removeFromTable(struct BlockTag** HashTable,struct BlockTag *blockToRemove);
void delete_all(struct BlockTag** HashTable);
int Count(struct BlockTag** HashTable);

void replace(UT_hash_handle hh,struct BlockTag** HashTable,struct BlockTag *value);
struct BlockTag* get(struct BlockTag** HashTable,char* key);

#endif //ACA_PROJECT_SET_H
