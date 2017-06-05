//
// Created by chad on 6/5/17.
//

#include <Block.h>
#include "DRAM_Examples.h"

void Add_to_DRAM(){
    DRAM dram = Constructor_DRAM();

    Address address = Constructor_Address("00100010001000101");
    Block block = Constructor_Block(address);
    Block* pblock = &block;
    dram.putBlock(&dram.HashTable,pblock);

    int count = dram.CountBlocks(&dram.HashTable);

    printf("# of blocks in main memory:%d\n",count);
}