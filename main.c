#include <stdio.h>
#include "Set.h"
#include "Block.h"

void ExampleUsingHash(){
    Set set = Constructor_Set();
    Block case1 = {useFrequency:1};
    Block case2 = {useFrequency:2};
    Block* block = malloc(sizeof(Block));
    block = &case1;
    set.put(&set.HashTable,block);
    block = &case2;
    Block* returned = set.get(&set.HashTable,2);
    printf("%d",returned->useFrequency);
}

int main() {

}