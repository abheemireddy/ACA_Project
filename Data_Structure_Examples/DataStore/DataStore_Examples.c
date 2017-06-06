//
// Created by chad on 6/6/17.
//

#include <Data/DataStore.h>

void DataStore_Example(){
    DataStore dataStore = Constructor_DataStore();
    dataStore.StoreData("hello");
    dataStore.StoreData("Another piece of data");
    dataStore.StoreData("goodbye");

}