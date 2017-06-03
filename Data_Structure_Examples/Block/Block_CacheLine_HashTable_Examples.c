//
// Created by chad on 6/3/17.
//
#include "Block_CacheLine_HashTable_Examples.h"

int AddCacheLinesToBlock(){
    Block block = Constructor_Block("001");
    CacheLine case1 = {offset:"1000000"};
    CacheLine case2 = {offset:"0000001"};
    CacheLine* cacheLine1 = malloc(sizeof(CacheLine));
    cacheLine1 = &case1;
    block.putCacheLine(&block.HashTable,cacheLine1);
    CacheLine* cacheLine2 = &case2;
    block.putCacheLine(&block.HashTable,cacheLine2);
    CacheLine* returned = block.getCacheLine(&block.HashTable,cacheLine2->offset);
    printf("use Frequency: %s\n",returned->offset);
}