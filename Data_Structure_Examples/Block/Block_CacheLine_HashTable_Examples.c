//
// Created by chad on 6/3/17.
//
#include "Global_Variables.h"
#include "Block_CacheLine_HashTable_Examples.h"

int AddCacheLinesToBlock(){
    Address* address1 = Constructor_Address("0000000000000000");
    Address* address2 = Constructor_Address("0000000000000001");
    Block* block = Constructor_Block(*address1);
    CacheLine* case1 = Constructor_CacheLine(*address1,"some data");
    CacheLine* case2 = Constructor_CacheLine(*address2,"some other data");
    putCacheLine(&block->HashTable,case1);
    CacheLine* cacheLine2 = case2;
    putCacheLine(&block->HashTable,case2);
    int count = CountCacheLines(&block->HashTable);
    printf("Count: %d",count);
    CacheLine* returned = getCacheLineByOffset(&block->HashTable,cacheLine2->address.Offset);
    char data[8];
    strcpy(data,GetData(l1Data,returned->dataLine));
}