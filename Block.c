//
// Created by chad on 5/24/17.
//

#include <Block.h>

Block Constructor_Block(int numberOfCacheLines){
    Block block = {dirtyBit:false,validBit:false,useFrequency:0};
    //*block.cacheLines = (struct CacheLineTag*)malloc(numberOfCacheLines*sizeof(struct CacheLineTag));
    block.SetCacheLines = &SetCacheLines;
    block.Set_Data = &Set_Data;
    block.IsInBlock = &IsInBlock;
    block.address = "";
    return block;
}

bool IsInBlock(char* address){
    return true;
}

void Set_Data(Block* block,char* address){
    block->address = address;
}

void SetCacheLines(Block block,CacheLine* cacheLines[]){
    block.cacheLines = cacheLines;
}

void IncrementBlockFrequency(Block** block){
    (*block)->useFrequency += 1;
}