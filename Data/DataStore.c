//
// Created by chad on 6/6/17.
//

#include <stdlib.h>
#include <memory.h>
#include "DataStore.h"

DataStore* Constructor_DataStore(){
    DataStore* data = malloc(sizeof(DataStore));
    data->currentLine = 0;
    return data;
}

char* GetData(DataStore* dataStore,int lineNumber){
    return dataStore->Data[lineNumber];
}

int StoreData(DataStore* dataStore,char dataToStore[8]){
    strcpy(dataStore->Data[dataStore->currentLine],dataToStore);
    dataStore->currentLine += 1;
    return dataStore->currentLine-1;
}