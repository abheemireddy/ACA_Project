//
// Created by chad on 6/5/17.
//

#include "BlockTransferer.h"

Transferer Constructor_Transferer(){
    Transferer transferer = {};
    transferer.TransferQueue = Queue_Constructor();
}