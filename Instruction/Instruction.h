//
// Created by root on 6/11/17.
//

#ifndef ACA_PROJECT_INSTRUCTION_H
#define ACA_PROJECT_INSTRUCTION_H

#include "Address/Address.h"

typedef struct InstructionTag{
    int clockCycleWhenThisCanBeRead;
    int instruction;
    char data[64];
    Address address;
} Instruction;

Instruction* Constructor_Instruction(int instructionNumber,char data[64],Address address);

#endif //ACA_PROJECT_INSTRUCTION_H
