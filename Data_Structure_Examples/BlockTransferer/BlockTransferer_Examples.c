//
// Created by chad on 6/7/17.
//
#include "BlockTransferer_Examples.h"

void StoreAndGetFromBlockTransferer(){
    Transferer transferer = Constructor_Transferer();
    Transferer* ptransferer = &transferer;
    Instruction instruction = Constructor_Instruction(0,"this is the stored data");
    Node node = Constructor_Node(instruction);
    Node* pnode = &node;
    ptransferer->TransferQueue->Enqueue(&ptransferer->TransferQueue,&pnode);

    instruction = Constructor_Instruction(1,"different data");
    node = Constructor_Node(instruction);
    pnode = &node;
    ptransferer->TransferQueue->Enqueue(&ptransferer->TransferQueue,&pnode);

    ptransferer->GetNextInstruction(ptransferer);

}