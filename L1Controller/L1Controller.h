#ifndef __L1Controller_H__
#define __L1Controller_H__
#include <stdio.h>
#include "aca/L1Data.h"
#include "L2Controller/L2Controller.h"
#include "Address/Address.h"
#include <BlockTransferer/BlockTransferer.h>

typedef struct L1ControllerTag{
    Transferer* transferer;
    void (*L1_write)(Address address, int value);
    int (*L1_read)(Address address);
} L1Controller;

L1Controller* Constructor_L1Controller();

void L1_write(Address address, int value);
int L1_read(Address address);

#endif
