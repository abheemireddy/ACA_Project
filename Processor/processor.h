//
// Created by chad on 6/7/17.
//

#ifndef ACA_PROJECT_PROCESSOR_H
#define ACA_PROJECT_PROCESSOR_H
#include <stdio.h>
#include <string.h>
#include "L1Controller/L1Controller.h"
#include "L2Controller/L2Controller.h"
#include "aca/L1Data.h"
#include "aca/L2Data.h"
#include "Address/Address.h"

typedef struct ProcessorTag{
    void (*run_processor)();
} Processor;

Processor Constructor_Processor();

void run_processor();

void print_current_directory();

#endif //ACA_PROJECT_PROCESSOR_H
