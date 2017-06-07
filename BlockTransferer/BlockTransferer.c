//
// Created by chad on 6/5/17.
//

#include "BlockTransferer.h"

Transferer Constructor_Transferer(){
    Transferer transferer = {};
    transferer.GetNextInstruction = &GetNextInstruction;
    Queue queue = Queue_Constructor();
    transferer.TransferQueue = queue;
    return transferer;
}

Instruction GetNextInstruction(Transferer* transferer){
    Queue queue = transferer->TransferQueue;
    Instruction nextInstruction = queue.Dequeue(&queue);
    return nextInstruction;
}
