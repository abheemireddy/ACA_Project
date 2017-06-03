//
// Created by chad on 6/3/17.
//
#include "Block_CacheLine_HashTable_Examples.h"

int AddCacheLinesToBlock(){
    Address address1 = Constructor_Address("00000000000000000");
    Address address2 = Constructor_Address("00000000000000001");
    Block block = Constructor_Block(address1);
    CacheLine case1 = Constructor_CacheLine(address1,"some data");
    CacheLine case2 = Constructor_CacheLine(address2,"some other data");
    CacheLine* cacheLine1 = malloc(sizeof(CacheLine));
    cacheLine1 = &case1;
    block.putCacheLine(&block.HashTable,cacheLine1);
    CacheLine* cacheLine2 = &case2;
    block.putCacheLine(&block.HashTable,cacheLine2);
    CacheLine* returned = block.getCacheLine(&block.HashTable,cacheLine2->address.bitString);
    printf("use Frequency: %s\n",returned->address.bitString);
}