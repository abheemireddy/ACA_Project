#ifndef __L1Controller_H__
#define __L1Controller_H__
#include <stdio.h>
#include "aca/L1Data.h"
#include "L2Controller/L2Controller.h"
#include "Address/Address.h"
#include <BlockTransferer/BlockTransferer.h>
#include <Cache/Cache.h>

typedef struct L1ControllerTag{
    Cache* cache;
    Transferer* transferer;
    void (*L1_write)(Address address, char* value);
    int (*L1_read)(Address address);
    void (*ProcessInstruction)(struct L1ControllerTag* l1Controller,Instruction* instruction);
} L1Controller;

L1Controller* Constructor_L1Controller();

void ProcessInstruction(L1Controller* l1Controller,Instruction* instruction);
void L1_write(Address address, char* value);
int L1_read(Address address);

#endif
