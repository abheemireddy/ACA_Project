//
// Created by chad on 6/5/17.
//

#ifndef ACA_PROJECT_BUFFERS_H
#define ACA_PROJECT_BUFFERS_H
#include <stdbool.h>
#include <uthash_files/include/uthash.h>

struct BlockTag;//forward declaration

typedef struct BufferTag {
    bool isWriteBuffer;//otherwise is victim cache
    UT_hash_handle hh; /* make this structure hashable*/
    struct BlockTag *HashTable; //This is my hashTable for blocks

    void (*removeBlockFromBuffer)(struct BlockTag** HashTable,struct BlockTag* blockToRemove);
    void (*putBlock)(struct BlockTag** HashTable,struct BlockTag *value);
    int (*CountBlocks)(struct BlockTag** HashTable);
    struct BlockTag* (*getBlock)(struct BlockTag** HashTable,int key);
    void (*print_all_blocks)(struct BlockTag** HashTable);

} Buffer;

Buffer* Constructor_Buffer();

void removeBlockFromBuffer(struct BlockTag** HashTable,struct BlockTag* blockToRemove);
void putBlockInBuffer(struct BlockTag** HashTable,struct BlockTag *value);
int CountBlocksInBuffer(struct BlockTag** HashTable);
struct BlockTag* getBlockFromBuffer(struct BlockTag** HashTable,int key);
void print_all_blocks_in_buffer(struct BlockTag** HashTable);
void WriteBackToL2(struct BlockTag** HashTable);
#endif //ACA_PROJECT_BUFFERS_H
