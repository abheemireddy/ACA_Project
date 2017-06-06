//
// Created by chad on 6/6/17.
//

#include <stdlib.h>
#include <memory.h>
#include "DataStore.h"

DataStore Constructor_DataStore(){
    DataStore data = {currentLine:0};
    data.StoreData = &StoreData;
    data.GetData = &GetData;
    return data;
}

char* GetData(DataStore* dataStore,int lineNumber){
    return dataStore->Data[lineNumber];
}

int StoreData(DataStore* dataStore,char* dataToStore){
    strcpy(dataStore->Data[dataStore->currentLine],dataToStore);
    dataStore->currentLine += 1;
    return dataStore->currentLine-1;
}