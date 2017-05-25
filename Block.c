//
// Created by chad on 5/24/17.
//

#include <Block.h>

Block BlockConstructor(int tag){
    Block block = {tag:tag,size:64};
    return block;
}



//Below, assume block contains char* data

