//
// Created by chad on 5/24/17.
//

#include <Block.h>

Block Constructor_Block(int numberOfCacheLines){
    Block block = {dirtyBit:false,validBit:false,useFrequency:0};
    //*block.cacheLines = (struct CacheLineTag*)malloc(numberOfCacheLines*sizeof(struct CacheLineTag));
    block.SetCacheLines = &SetCacheLines;
    return block;
}

void SetCacheLines(Block block,CacheLine* cacheLines[]){
    block.cacheLines = cacheLines;
}