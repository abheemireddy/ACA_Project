//
// Created by chad on 6/7/17.
//

#ifndef ACA_PROJECT_PROCESSOR_H
#define ACA_PROJECT_PROCESSOR_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Controller/Controller.h"

typedef struct TransfererTag Transferer;

typedef struct ProcessorTag{
    void (*StoreFileInstructionsIntoProcessorQueue)(struct ProcessorTag* processor);

    Transferer* InstructionHolder;
    Controller l1Controller;
    Controller l2Controller;
} Processor;

Processor* Constructor_Processor(Controller* l1Controller,Controller* l2Controller);

void StoreFileInstructionsIntoProcessorQueue(Processor* processor);

void print_current_directory();

#endif //ACA_PROJECT_PROCESSOR_H
