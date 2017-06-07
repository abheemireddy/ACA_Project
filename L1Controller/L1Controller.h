#ifndef __L1Controller_H__
#define __L1Controller_H__
#include <stdio.h>
#include "aca/L1Data.h"
#include "L2Controller/L2Controller.h"

void L1_write(int address, int value);
int L1_read(int address);

#endif
