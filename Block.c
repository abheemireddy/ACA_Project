//
// Created by chad on 5/24/17.
//

#include <Block.h>

Block Constructor_Block(int numberOfCacheLines){
    Block block = {dirtyBit:false,validBit:false,useFrequency:0};
    //*block.cacheLines = (struct CacheLineTag*)malloc(numberOfCacheLines*sizeof(struct CacheLineTag));
    block.SetCacheLines = &SetCacheLines;
    block.Set_Data = &Set_Data;
    block.data = "";
    return block;
}

void Set_Data(Block* block,char* data){
    block->data = data;
}

void SetCacheLines(Block block,CacheLine* cacheLines[]){
    block.cacheLines = cacheLines;
}

void IncrementBlockFrequency(Block** block){
    (*block)->useFrequency += 1;
}