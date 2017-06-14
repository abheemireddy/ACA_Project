#ifndef __Controller_H__
#define __Controller_H__
#include <stdio.h>
#include <stdbool.h>
#include "Instruction/Instruction.h"
#include "Block/Block.h"
#include "BlockOnBus/BlockOnBus.h"

typedef struct CacheTag Cache;
typedef struct TransfererTag Transferer;
typedef struct CacheLineTag CacheLine;
typedef struct BlockQueueTag BlockQueue;
typedef struct SetTag Set;

typedef struct ControllerTag{
    bool waiting;
    Cache* cache;
    Transferer* transferer;
    BlockQueue* writeBlockQueue;
} Controller;

Controller* Constructor_L1Controller();
Controller* Constructor_L2Controller();

CacheLine* ProcessL1Instruction(Instruction instruction);
void WriteToController(Instruction instruction, char value[64]);
CacheLine* L1_read(Instruction instruction);
void WriteBlockToL1Controller(Block* toStore);

bool CheckL2WriteBuffer(Block block2Write);
void WriteBlockToL2Controller(BlockOnBus* blockOnBus2Write);
void L2WriteBlock(Block block);
void FindBlockInL2(Instruction instruction);
void CheckL2SetSize(struct SetTag* set);
void CheckL2BufferSize();
void PutInL2WriteBuffer(Block* existing);

void ProcessDRamInstruction(Instruction instruction);
void WriteBlockToDRAM(BlockOnBus* block2Write);


#endif
