#ifndef __Controller_H__
#define __Controller_H__
#include <stdio.h>
#include <stdbool.h>
#include "Instruction/Instruction.h"

typedef struct CacheTag Cache;
typedef struct TransfererTag Transferer;
typedef struct BlockQueueTag BlockQueue;
typedef struct CacheLineTag CacheLine;

typedef struct ControllerTag{
    bool waiting;
    Cache* cache;
    Transferer* transferer;
    BlockQueue* blockQueue;
} Controller;

Controller* Constructor_L1Controller();
Controller* Constructor_L2Controller();

CacheLine* L1ProcessInstruction(Instruction instruction);
void L1_write(Instruction instruction, char value[64]);
CacheLine* L1_read(Instruction instruction);
void SetL1ControllerData();

#endif
