#ifndef __L1Controller_H__
#define __L1Controller_H__
#include <stdio.h>
#include "aca/L1Data.h"
#include "Address/Address.h"
#include "Block/Block.h"
#include "Queue/Queue.h"
#include "Instruction/Instruction.h"

typedef struct CacheTag Cache;
typedef struct TransfererTag Transferer;
typedef struct BlockQueueTag BlockQueue;

typedef struct ControllerTag{
    bool waiting;
    Cache* cache;
    Transferer* transferer;
    BlockQueue* blockQueue;
    Block* dataFromL2;
} Controller;

Controller* Constructor_L1Controller();
Controller* Constructor_L2Controller();

CacheLine* L1ProcessInstruction(Instruction instruction);
void L1_write(Instruction instruction, char value[64]);
CacheLine* L1_read(Instruction instruction);
void SetL1ControllerData();

#endif
