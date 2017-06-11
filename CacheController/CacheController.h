//
// Created by chad on 6/6/17.
//

#ifndef ACA_PROJECT_CACHECONTROLLER_H
#define ACA_PROJECT_CACHECONTROLLER_H

#include "Block/Block.h"

typedef struct CacheControllerTag{

} CacheController;

void WriteToVictimCache();
void WriteToWriteBuffer();
void WriteToL1Cache();
Block GetFromL1Cache();


#endif //ACA_PROJECT_CACHECONTROLLER_H
