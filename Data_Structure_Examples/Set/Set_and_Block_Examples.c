//
// Created by chad on 6/2/17.
//
#include "Set_and_Block_Examples.h"

void ExampleUsingSetHash(){
    Set set = Constructor_Set(4);
    Block case1 = {useFrequency:1,address:"bitString1"};
    Block case2 = {useFrequency:2,address:"bitString2"};
    Block* block1 = malloc(sizeof(Block));
    block1 = &case1;
    set.put(&set.HashTable,block1);
    Block* block2 = &case2;
    set.put(&set.HashTable,block2);
    Block* returned = set.get(&set.HashTable,block2->address);
    printf("use Frequency: %d\n",returned->useFrequency);
}
Block GetDummyBlockInstance(char* data){
    Block toAdd = Constructor_Block("4");
    return toAdd;
}
void AddTooManyBlocksTest(){
    Set set = Constructor_Set(4);

    Block block1 = GetDummyBlockInstance("Some memory location 1");
    Block* pblock1 = &block1;
    Block block2 = GetDummyBlockInstance("Some memory location 2");
    Block* pblock2 = &block2;
    Block block3 = GetDummyBlockInstance("Some memory location 3");
    Block* pblock3 = &block3;
    Block block4 = GetDummyBlockInstance("Some memory location 4");
    Block* pblock4 = &block4;
    Block block5 = GetDummyBlockInstance("Some memory location 5");
    Block* pblock5 = &block5;
    Block block6 = GetDummyBlockInstance("Some memory location 6");
    Block* pblock6 = &block6;
    Block block7 = GetDummyBlockInstance("Some memory location 7");
    Block* pblock7 = &block7;

    IncrementBlockFrequency(&pblock1);//1 time, this will be least frequently used of the blocks

    IncrementBlockFrequency(&pblock2);//twice
    IncrementBlockFrequency(&pblock2);

    IncrementBlockFrequency(&pblock3);//three times
    IncrementBlockFrequency(&pblock3);
    IncrementBlockFrequency(&pblock3);

    IncrementBlockFrequency(&pblock4);//four uses
    IncrementBlockFrequency(&pblock4);
    IncrementBlockFrequency(&pblock4);
    IncrementBlockFrequency(&pblock4);

    IncrementBlockFrequency(&pblock5);
    IncrementBlockFrequency(&pblock5);
    IncrementBlockFrequency(&pblock5);
    IncrementBlockFrequency(&pblock5);
    IncrementBlockFrequency(&pblock5);

    IncrementBlockFrequency(&pblock6);
    IncrementBlockFrequency(&pblock6);
    IncrementBlockFrequency(&pblock6);
    IncrementBlockFrequency(&pblock6);
    IncrementBlockFrequency(&pblock6);
    IncrementBlockFrequency(&pblock6);

    IncrementBlockFrequency(&pblock7);
    IncrementBlockFrequency(&pblock7);
    IncrementBlockFrequency(&pblock7);
    IncrementBlockFrequency(&pblock7);
    IncrementBlockFrequency(&pblock7);
    IncrementBlockFrequency(&pblock7);
    IncrementBlockFrequency(&pblock7);

    set.put(&set.HashTable,pblock1);
    set.put(&set.HashTable,pblock2);
    set.put(&set.HashTable,pblock3);
    set.put(&set.HashTable,pblock4);
    set.put(&set.HashTable,pblock5);
    set.put(&set.HashTable,pblock6);
    set.put(&set.HashTable,pblock7);

    printf("\nCount:%d\n",set.Count(&set.HashTable));

    set.SortHash(&set.HashTable);
    print_blocks_in_set(&set.HashTable);
}