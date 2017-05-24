//
// Created by chad on 5/24/17.
//
//Split, 4-way, write-back, write-allocate, 64-byte block size and size 16KB
//must support valid and dirty bits
//assume l1D is dual-ported, one read and one-write port
//I may pre-load the l1 instruction cache from an input file of instructions
//you may use an additional 64-byte register file to refer to data in the 8 byte instructions

#ifndef ACA_PROJECT2_L1_CC_H
#define ACA_PROJECT2_L1_CC_H

#include <stdbool.h>

typedef struct{
    bool validBit;
    bool dirtyBit;
    char* tag;
    int blockSize;//16 KB
} Block;

typedef struct{
    //contain blocks
    //maybe store how many blocks
} Set;

typedef struct{
    //some reference to sets
    //maybe how many sets
} Cache;

#endif //ACA_PROJECT2_L1_CC_H
