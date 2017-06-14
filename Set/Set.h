//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_SET_H
#define ACA_PROJECT_SET_H
#include <stdbool.h>
#include <printf.h>
#include "uthash_files/include/uthash.h"
#include "Address/Address.h"

typedef struct SetTag {
    struct BlockTag *HashTable;
    int numberOfBlocks;
    Address address;
    UT_hash_handle hh;
} Set;

struct BlockTag* GetLeastUsed(struct BlockTag** HashTable);
Set* Constructor_Set(int numberOfBlocks,Address address);
void AddBlock(Set set,struct BlockTag** HashTable,struct BlockTag** blockToAdd);

//HashTable functions
bool IsBlockInSet(struct SetTag set,struct BlockTag newBlock);
void put(struct BlockTag** HashTable,struct BlockTag *value);
struct BlockTag* getByUseFrequency(struct BlockTag** HashTable,int key);
void removeFromTable(struct BlockTag** HashTable,struct BlockTag *blockToRemove);
void delete_all(struct BlockTag** HashTable);
int Count(struct BlockTag** HashTable);

struct BlockTag* get(struct BlockTag** HashTable,int key);
void SortHash(struct BlockTag** HashTable);
void print_blocks_in_set(struct BlockTag** HashTable);

#endif //ACA_PROJECT_SET_H
