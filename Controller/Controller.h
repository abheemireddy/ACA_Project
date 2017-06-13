#ifndef __Controller_H__
#define __Controller_H__
#include <stdio.h>
#include <stdbool.h>
#include "Instruction/Instruction.h"
#include "Block/Block.h"
#include "BlockOnBus/BlockOnBus.h"

typedef struct CacheTag Cache;
typedef struct TransfererTag Transferer;
typedef struct BlockQueueTag BlockQueue;
typedef struct CacheLineTag CacheLine;
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
void WriteBlockToL1Controller(Block toStore);

bool CheckL2WriteBuffer(Block block2Write);
void WriteBlockToL2Controller(Block block);
void L2WriteBlock(Block block);
void FindBlockInL2(Address DataToFind);
void WriteBlockToDRAM(Block block);
void CheckL2SetSize(struct SetTag* set);
void CheckL2BufferSize();
void PutInL2WriteBuffer(Block* existing);

void ProcessDRamInstruction(Address blockAddressToFind);
#endif
