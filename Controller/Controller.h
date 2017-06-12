#ifndef __Controller_H__
#define __Controller_H__
#include <stdio.h>
#include <stdbool.h>
#include "Instruction/Instruction.h"
#include "Block/Block.h"

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

CacheLine* ProcessL1Instruction(Instruction instruction);
void WriteToController(Instruction instruction, char value[64]);
CacheLine* L1_read(Instruction instruction);
void SetL1ControllerData();

bool CheckL2WriteBuffer(Block block2Write);
void WriteBlockToL2Controller(Block block);
void L2WriteBlock(Block block);

#endif
