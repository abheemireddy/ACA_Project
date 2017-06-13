//
// Created by root on 6/10/17.
//

#ifndef ACA_PROJECT_GLOBAL_VARIABLES_H
#define ACA_PROJECT_GLOBAL_VARIABLES_H

#include "Controller/Controller.h"
#include "Processor/processor.h"
#include "Buffers/buffers.h"
#include "Data/DataStore.h"
#include "DRAM/DRAM.h"

//Global variables
Controller* l1Controller;
Controller* l2Controller;
Processor* processor;
Buffer* l1WriteBuffer;
Buffer* l1VictimCache;
Buffer* l2WriteBuffer;
DataStore* l1Data;
DataStore* l2Data;
DRAM* dRAM;
int ClockCycleCount;

#endif //ACA_PROJECT_GLOBAL_VARIABLES_H
