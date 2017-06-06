//
// Created by chad on 6/6/17.
//

#include <Data/DataStore.h>

void DataStore_Example(){
    DataStore dataStore = Constructor_DataStore();
    int location1 = dataStore.StoreData(&dataStore,"hello");
    dataStore.StoreData(&dataStore,"Another piece of data");
    dataStore.StoreData(&dataStore,"goodbye");

    char* data1 = dataStore.GetData(&dataStore,location1);
    printf("Stored data:%s",data1);
}