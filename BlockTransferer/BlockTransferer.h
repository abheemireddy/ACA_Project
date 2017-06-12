//
// Created by chad on 6/5/17.
//

#ifndef ACA_PROJECT_BLOCKTRANSFERER_H
#define ACA_PROJECT_BLOCKTRANSFERER_H

#include "Instruction/Instruction.h"
typedef struct QueueTag Queue;



//This struct will handle block transfers between memory and the L1/L2 caches.
typedef struct TransfererTag{
    Queue* TransferQueue;
    Instruction (*GetNextInstruction)(struct TransfererTag* transferer);
} Transferer;

Transferer* Constructor_Transferer();

Instruction GetNextInstruction(Transferer* transferer);

#endif //ACA_PROJECT_BLOCKTRANSFERER_H
