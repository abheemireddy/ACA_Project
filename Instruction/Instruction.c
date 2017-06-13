//
// Created by root on 6/11/17.
//
#include "Instruction.h"

Instruction* Constructor_Instruction(int instructionNumber,char data[8],Address address){
    Instruction* instruction = malloc(sizeof(Instruction));
    instruction->instruction = instructionNumber;
    instruction->address = address;
    if(data != NULL){
        strcpy(instruction->data,data);
    }else{
        data = NULL;
    }
    return instruction;
}