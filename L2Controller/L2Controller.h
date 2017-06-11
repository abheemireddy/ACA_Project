#ifndef __L2CONTROLLER_H__
#define __L2CONTROLLER_H__
#include "aca/L2Data.h"
#include "aca/MainMemory.h"
#include <stdio.h>
#include <string.h>
#include <Address/Address.h>
#include <BlockTransferer/BlockTransferer.h>
#include <Block_Queue/Block_Queue.h>
#include <Block/Block.h>
#include <Queue/Queue.h>

typedef struct BlockQueueTag BlockQueue;

typedef struct L2ControllerTag{
    Transferer* transferer;
    bool waiting;
    Block* dataFromDRAM;
    BlockQueue* blockQueue;

    void (*l2Read)(Address address, unsigned char * block);
    void (*l2Write)(Address address, int value);
    void (*l2WriteBack)(Address address, unsigned char * data);
} L2Controller;

L2Controller* Constructor_L2Controller();

void l2Read(Address address, unsigned char * block);
void l2Write(Address address, int value);
void l2WriteBack(Address address, unsigned char * data);

#endif
