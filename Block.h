//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_BLOCK_H
#define ACA_PROJECT_BLOCK_H
#include <stdbool.h>

typedef struct BlockTag{
    bool validBit;
    bool dirtyBit;
    char* tag;
    int blockSize;//16 KB
} Block;

#endif //ACA_PROJECT_BLOCK_H
