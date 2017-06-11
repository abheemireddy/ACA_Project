//
// Created by chad on 6/6/17.
//

#ifndef ACA_PROJECT_DATASTORE_H
#define ACA_PROJECT_DATASTORE_H

typedef struct DataStoreTag{
    int currentLine;
    char Data[64][64];
    int (*StoreData)(struct DataStoreTag* dataStore,char* dataToStore);
    char* (*GetData)(struct DataStoreTag* dataStore,int lineNumber);
} DataStore;


DataStore* Constructor_DataStore();

char* GetData(DataStore* dataStore,int lineNumber);
int StoreData(DataStore* dataStore,char* dataToStore);

#endif //ACA_PROJECT_DATASTORE_H
