#include <stdio.h>
#include "Set.h"
#include "Block.h"

void ExampleUsingHash(){
    Set set = Constructor_Set();
    Block case1 = {tag:4};
    Block case2 = {tag:5};
    Block* block = malloc(sizeof(Block));
    block = &case1;
    set.put(&set.HashTable,block);
    block = &case2;
    Block* returned = set.get(&set.HashTable,4);
    printf("%d",returned->tag);
}

int main() {

}