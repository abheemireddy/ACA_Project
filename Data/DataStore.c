//
// Created by chad on 6/6/17.
//

#include <stdlib.h>
#include <memory.h>
#include "DataStore.h"

DataStore Constructor_DataStore(){
    DataStore data = {};
    return data;
}

int StoreData(DataStore* dataStore,char* dataToStore){
    strcpy(dataStore->Data[dataStore->currentLine],dataToStore);
    dataStore->currentLine += 1;
    return dataStore->currentLine-1;
}