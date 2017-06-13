//
// Created by root on 6/12/17.
//
#include "Set/Set.h"
#include "Cache/Cache.h"
#include "BlockOnBus.h"
#include "CacheLine/CacheLine.h"
#include "Controller/Controller.h"
#include "Global_Variables.h"


BlockOnBus* Constructor_BlockOnBus(void* controller,Block block,int howLongUntiBlockIsTransferred){
    BlockOnBus* blockOnBus = malloc(sizeof(BlockOnBus));
    blockOnBus->blockOnBus = block;
    blockOnBus->clockCycleWhenBlockIsAvailable = howLongUntiBlockIsTransferred;

    int i = 0;
    CacheLine* s;
    CacheLine* tmp;
    HASH_ITER(hh,block.HashTable,s,tmp){
        if(controller == l1Controller){
            char* data = GetData(l1Data,s->dataLine);
            strcpy(blockOnBus->valueBeingTransferred[i],data);
            i += 1;
        }else if(controller == l2Controller){
            char* data = GetData(l2Data,s->dataLine);
            strcpy(blockOnBus->valueBeingTransferred[i],data);
            i += 1;
        }else if(controller == dRAM){
            /*char* data = GetData(l2Data,s->dataLine);
            strcpy(blockOnBus->valueBeingTransferred[i],data);
            i += 1;*/
        }
    }
    //strcpy(blockOnBus->valueBeingTransferred,value);
}

