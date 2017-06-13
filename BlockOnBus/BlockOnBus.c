//
// Created by root on 6/12/17.
//
#include "BlockOnBus.h"

BlockOnBus* Constructor_BlockOnBus(Block block,int howLongUntiBlockIsTransferred,char value[64]){
    BlockOnBus* blockOnBus = malloc(sizeof(BlockOnBus));
    blockOnBus->blockOnBus = block;
    blockOnBus->clockCycleWhenBlockIsAvailable = howLongUntiBlockIsTransferred;
    strcpy(blockOnBus->valueBeingTransferred,value);
}

