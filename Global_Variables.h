//
// Created by root on 6/10/17.
//

#ifndef ACA_PROJECT_GLOBAL_VARIABLES_H
#define ACA_PROJECT_GLOBAL_VARIABLES_H

#include <Processor/processor.h>
#include <Buffers/buffers.h>
#include <L2Controller/L2Controller.h>
#include <L1Controller/L1Controller.h>
#include <Data/DataStore.h>

//Global variables
L1Controller* l1Controller;
L2Controller* l2Controller;
Processor* processor;
Buffer* l1WriteBuffer;
Buffer* l1VictimCache;
DataStore* l1Data;

#endif //ACA_PROJECT_GLOBAL_VARIABLES_H
