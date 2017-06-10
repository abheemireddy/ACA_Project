//
// Created by chad on 6/5/17.
//

#include "BlockTransferer.h"

Transferer* Constructor_Transferer(){
    Transferer* transferer = malloc(sizeof(Transferer));
    transferer->GetNextInstruction = &GetNextInstruction;
    transferer->TransferQueue = Queue_Constructor();
    return transferer;
}

Instruction* GetNextInstruction(Transferer* transferer){
    Queue* queue = transferer->TransferQueue;
    Instruction* nextInstruction = queue->Dequeue(queue);
    return nextInstruction;
}
