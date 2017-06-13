//
// Created by chad on 6/5/17.
//

#ifndef ACA_PROJECT_BUFFERS_H
#define ACA_PROJECT_BUFFERS_H
#include <stdbool.h>
#include "uthash_files/include/uthash.h"

typedef struct BufferTag {
    bool isWriteBuffer;//otherwise is victim cache
    UT_hash_handle hh; /* make this structure hashable*/
    struct BlockTag *HashTable; //This is my hashTable for blocks

} Buffer;

Buffer* Constructor_Buffer();

void removeBlockFromBuffer(struct BlockTag** HashTable,struct BlockTag* blockToRemove);
void putBlockInBuffer(struct BlockTag** HashTable,struct BlockTag *value);
int CountBlocksInBuffer(struct BlockTag** HashTable);
struct BlockTag* getBlockFromBuffer(struct BlockTag** HashTable,int key);
void print_all_blocks_in_buffer(struct BlockTag** HashTable);
void WriteBackToL2(struct BufferTag* buffer,struct BlockTag** HashTable);
#endif //ACA_PROJECT_BUFFERS_H
