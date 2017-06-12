//
// Created by root on 6/12/17.
//

#ifndef ACA_PROJECT_BLOCKONBUS_H
#define ACA_PROJECT_BLOCKONBUS_H

#include <Block/Block.h>

typedef struct BlockOnBusTag{
    Block blockOnBus;
    int clockCycleWhenBlockIsAvailable;
    char valueBeingTransferred[64];
}BlockOnBus;

BlockOnBus* Constructor_BlockOnBus(Block block,int howLongUntiBlockIsTransferred,char value[64]);

#endif //ACA_PROJECT_BLOCKONBUS_H
