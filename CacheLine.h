//
// Created by chad on 6/3/17.
//

#ifndef ACA_PROJECT_CACHELINE_H
#define ACA_PROJECT_CACHELINE_H
#include <stdio.h>
#include <uthash.h>

typedef struct CacheLineTag{
    char* offset;
    char* data;
    UT_hash_handle hh;
} CacheLine;

#endif //ACA_PROJECT_CACHELINE_H
