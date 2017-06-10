#ifndef __L1Controller_H__
#define __L1Controller_H__
#include <stdio.h>
#include "aca/L1Data.h"
#include "L2Controller/L2Controller.h"
#include "Address/Address.h"
#include <BlockTransferer/BlockTransferer.h>
#include <Cache/Cache.h>

typedef struct L1ControllerTag{
    bool waiting;
    Cache* cache;
    Transferer* transferer;
} L1Controller;

L1Controller* Constructor_L1Controller();

void L1ProcessInstruction(L1Controller* l1Controller,L2Controller* l2Controller,Instruction instruction);
void L1_write(L1Controller* l1Controller,Instruction instruction, char value[64]);
CacheLine* L1_read(L1Controller* l1Controller,L2Controller* l2Controller,Instruction instruction);

#endif
