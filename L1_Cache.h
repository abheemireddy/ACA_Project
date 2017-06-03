//
// Created by chad on 6/3/17.
//

#ifndef ACA_PROJECT_L1_CACHE_H
#define ACA_PROJECT_L1_CACHE_H
#include "Cache.h"
#include "Set.h"
#include "Block.h"
#include "CacheLine.h"

/*
 * 128 KB memory = 2^17 (total of 17 bits)
 * Cache Size = 16 KB = 2^14
 * Block is 64B = 2^6
 * Block Contains 8 Cache Lines (64/8), 2^3 = 8 so offset has 3 bits
 * Set has 4 blocks, set size = 64B*4 = 2^6*2^2 = 2^8
 * index bits = # of sets = cache size / set size = 2^14/2^8 = 6 bits
 * tag = tag - index bits - offset bits = 17 - 6 - 3 = 8 bits
 */


//Tag = 8 bits
//Index = 6 bits
//Offset = 3 bits
Cache BuildL1Cache(){
    Cache cache = Constructor_Cache(4);//set associativity is 4-way


}


#endif //ACA_PROJECT_L1_CACHE_H
