//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_CACHE_H
#define ACA_PROJECT_CACHE_H
#include "Set.h"


typedef struct CacheTag{
    int setAssociativity;
    Set ** sets;
    //write-back for L1 & L2
    //write-allocate for L1 & L2
} Cache;

Cache Constructor_Cache(int setAssociativity);

#endif //ACA_PROJECT_CACHE_H
