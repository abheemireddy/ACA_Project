//
// Created by chad on 5/25/17.
//

//Add your cache_line functionality here
#include "Global_Variables.h"
#include "CacheLine.h"

CacheLine* Constructor_CacheLine(Address address,char* data){
    CacheLine* cacheLine = malloc(sizeof(CacheLine));
    cacheLine->address = address;
    cacheLine->dataLine = -1;//StoreData(l1Data,data);
    return cacheLine;
}