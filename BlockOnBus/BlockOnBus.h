//
// Created by root on 6/12/17.
//

#ifndef ACA_PROJECT_BLOCKONBUS_H
#define ACA_PROJECT_BLOCKONBUS_H

#include "Block/Block.h"

typedef struct ControllerTag Controller;

typedef struct BlockOnBusTag{
    Block blockOnBus;
    int clockCycleWhenBlockIsAvailable;
    char valueBeingTransferred[64][8];
    UT_hash_handle hh; /* make this structure hashable*/
}BlockOnBus;

BlockOnBus* Constructor_BlockOnBus(void* controller,Block block,int howLongUntiBlockIsTransferred);

#endif //ACA_PROJECT_BLOCKONBUS_H
