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

typedef struct L1ControllerTag{
    bool waiting;
    Cache* cache;
    Transferer* transferer;
    Block* dataFromL2;
} L1Controller;

L1Controller* Constructor_L1Controller();

CacheLine* L1ProcessInstruction(Instruction instruction);
void L1_write(Instruction instruction, char value[64]);
CacheLine* L1_read(Instruction instruction);
void SetL1ControllerData();

#endif
