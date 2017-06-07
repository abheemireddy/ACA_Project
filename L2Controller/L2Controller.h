#ifndef __L2CONTROLLER_H__
#define __L2CONTROLLER_H__
#include "aca/L2Data.h"
#include "aca/MainMemory.h"
#include <stdio.h>
#include <string.h>

void initL2Controller();
void l2Read(int address, unsigned char * block);
void l2Write(int address, int value);
void l2WriteBack(int address, unsigned char * data);

#endif
