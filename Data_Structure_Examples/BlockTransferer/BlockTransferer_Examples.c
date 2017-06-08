//
// Created by chad on 6/7/17.
//
#include "BlockTransferer_Examples.h"

void StoreAndGetFromBlockTransferer(){
    Address address1 = Constructor_Address("00000000000000000");
    Transferer transferer = Constructor_Transferer();
    Transferer* ptransferer = &transferer;
    Instruction instruction = Constructor_Instruction(0,"this is the stored data",address1);

    Node node = Constructor_Node(instruction);
    ptransferer->TransferQueue.Enqueue(&ptransferer->TransferQueue,&node);

    instruction = Constructor_Instruction(1,"different data",address1);
    Node node2 = Constructor_Node(instruction);
    ptransferer->TransferQueue.Enqueue(&ptransferer->TransferQueue,&node);

    Instruction nextToBeExecuted =  ptransferer->GetNextInstruction(ptransferer);
    printf("\nNext Instruction's data:%s",nextToBeExecuted.data);

}