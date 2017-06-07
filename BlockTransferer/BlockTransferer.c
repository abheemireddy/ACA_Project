//
// Created by chad on 6/5/17.
//

#include "BlockTransferer.h"

Transferer Constructor_Transferer(){
    Transferer transferer = {};
    transferer.GetNextInstruction = &GetNextInstruction;
    transferer.TransferQueue = Queue_Constructor();
}

Instruction GetNextInstruction(Transferer* transferer){
    Instruction nextInstruction = transferer->TransferQueue->Dequeue(transferer->TransferQueue);
}
