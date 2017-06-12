//
// Created by chad on 6/5/17.
//

#include "Block/Block.h"
#include "DRAM_Examples.h"

void Add_to_DRAM(){
    DRAM dram = Constructor_DRAM();

    Address* address = Constructor_Address("0010010001000101");
    DRamBlock* block = Constructor_DRamBlock(*address,"this is the value");
    dram.putBlock(&dram.HashTable,block);

    int count = dram.CountBlocks(&dram.HashTable);

    printf("# of blocks in main memory:%d\n",count);
}