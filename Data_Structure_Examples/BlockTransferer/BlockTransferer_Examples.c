//
// Created by chad on 6/7/17.
//
#include "Address/Address.h"
#include "Queue/Queue.h"
#include "BlockTransferer_Examples.h"

void StoreAndGetFromBlockTransferer(){
    Address* address1 = Constructor_Address("0000000000000000");
    Transferer* transferer = Constructor_Transferer();
    Instruction* instruction = Constructor_Instruction(0,"this",*address1);

    transferer->TransferQueue->Enqueue(transferer->TransferQueue,*instruction);

    instruction = Constructor_Instruction(1,"differe",*address1);
    transferer->TransferQueue->Enqueue(transferer->TransferQueue,*instruction);

    Instruction nextToBeExecuted =  transferer->GetNextInstruction(transferer);
    printf("\nNext Instruction's data:%s",nextToBeExecuted.data);

}