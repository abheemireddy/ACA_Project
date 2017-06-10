//
// Created by chad on 6/7/17.
//
#include "BlockTransferer_Examples.h"

void StoreAndGetFromBlockTransferer(){
    Address* address1 = Constructor_Address("0000000000000000");
    Transferer* transferer = Constructor_Transferer();
    Instruction* instruction = Constructor_Instruction(0,"this is the stored data",address1);

    transferer->TransferQueue->Enqueue(transferer->TransferQueue,*instruction);

    instruction = Constructor_Instruction(1,"different data",address1);
    transferer->TransferQueue->Enqueue(transferer->TransferQueue,*instruction);

    Instruction nextToBeExecuted =  transferer->GetNextInstruction(transferer);
    printf("\nNext Instruction's data:%s",nextToBeExecuted.data);

}