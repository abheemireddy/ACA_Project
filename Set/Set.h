//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_SET_H
#define ACA_PROJECT_SET_H
#include "uthash_files/include/uthash.h"
#include "Address/Address.h"
#include <stdbool.h>

struct BlockTag;//forward declaration

typedef struct SetTag {

    int numberOfBlocks;


    void (*AddBlock)(struct SetTag set,struct BlockTag** HashTable,struct BlockTag** blockToAdd);

    bool (*IsBlockInSet)(struct SetTag set,struct BlockTag newBlock);
    void (*put)(struct BlockTag** HashTable,struct BlockTag *value);
    void (*replaceByUseFrequency)(struct BlockTag** HashTable,int key);
    struct BlockTag* (*getByUseFrequency)(struct BlockTag** HashTable,int key);
    void (*removeFromTable)(struct BlockTag** HashTable,struct BlockTag *blockToRemove);
    void (*delete_all)(struct BlockTag** HashTable);
    int (*Count)(struct BlockTag** HashTable);

    struct BlockTag* (*get)(struct BlockTag** HashTable,char* key);
    void (*SortHash)(struct BlockTag** HashTable);
    void (*print_blocks_in_set)(struct BlockTag** HashTable);

    Address address;

    //---------Used in Cache HashMap to find set
    UT_hash_handle hh; /* make this structure hashable*/
    //---------Used in HashMap

    struct BlockTag *HashTable; //This is my hashTable for blocks
    //contain blocks
    //maybe store how many blocks
} Set;

Set* Constructor_Set(int numberOfBlocks,Address address);
void AddBlock(Set set,struct BlockTag** HashTable,struct BlockTag** blockToAdd);

//HashTable functions
bool IsBlockInSet(struct SetTag set,struct BlockTag newBlock);
void put(struct BlockTag** HashTable,struct BlockTag *value);
void replaceByUseFrequency(struct BlockTag** HashTable,int key);
struct BlockTag* getByUseFrequency(struct BlockTag** HashTable,int key);
void removeFromTable(struct BlockTag** HashTable,struct BlockTag *blockToRemove);
void delete_all(struct BlockTag** HashTable);
int Count(struct BlockTag** HashTable);

struct BlockTag* get(struct BlockTag** HashTable,char* key);
void SortHash(struct BlockTag** HashTable);
void print_blocks_in_set(struct BlockTag** HashTable);

#endif //ACA_PROJECT_SET_H
