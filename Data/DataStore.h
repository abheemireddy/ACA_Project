//
// Created by chad on 6/6/17.
//

#ifndef ACA_PROJECT_DATASTORE_H
#define ACA_PROJECT_DATASTORE_H

typedef struct DataStoreTag{
    int currentLine;
    char Data[8][8];
} DataStore;


DataStore* Constructor_DataStore();

char* GetData(DataStore* dataStore,int lineNumber);
int StoreData(DataStore* dataStore,char* dataToStore);

#endif //ACA_PROJECT_DATASTORE_H
