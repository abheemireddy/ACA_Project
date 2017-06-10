//
// Created by chad on 6/2/17.
//
#include "Set_and_Block_Examples.h"

void ExampleUsingSetHash(){
    Address* address1 = Constructor_Address("0000000000000000");
    Address* address2 = Constructor_Address("0000000000000001");
    Set* set = Constructor_Set(4,*address1);
    Block* case1 = Constructor_Block(*address1);
    Block* case2 = Constructor_Block(*address2);
    put(&set->HashTable,case1);
    put(&set->HashTable,case2);
    Block* returned = get(&set->HashTable,case2->address.Tag);
    printf("use Frequency: %d\n",returned->useFrequency);
}
Block* GetDummyBlockInstance(char* data){
    Address* address1 = Constructor_Address("0000000000000000");
    Block* toAdd = Constructor_Block(*address1);
    return toAdd;
}
void AddTooManyBlocksTest(){
    Address* address1 = Constructor_Address("0000000000000000");
    Set* set = Constructor_Set(4,*address1);

    Block* block1 = GetDummyBlockInstance("Some memory location 1");
    Block* block2 = GetDummyBlockInstance("Some memory location 2");
    Block* block3 = GetDummyBlockInstance("Some memory location 3");
    Block* block4 = GetDummyBlockInstance("Some memory location 4");
    Block* block5 = GetDummyBlockInstance("Some memory location 5");
    Block* block6 = GetDummyBlockInstance("Some memory location 6");
    Block* block7 = GetDummyBlockInstance("Some memory location 7");

    IncrementBlockFrequency(&block1);//1 time, this will be least frequently used of the blocks

    IncrementBlockFrequency(&block2);//twice
    IncrementBlockFrequency(&block2);

    IncrementBlockFrequency(&block3);//three times
    IncrementBlockFrequency(&block3);
    IncrementBlockFrequency(&block3);

    IncrementBlockFrequency(&block4);//four uses
    IncrementBlockFrequency(&block4);
    IncrementBlockFrequency(&block4);
    IncrementBlockFrequency(&block4);

    IncrementBlockFrequency(&block5);
    IncrementBlockFrequency(&block5);
    IncrementBlockFrequency(&block5);
    IncrementBlockFrequency(&block5);
    IncrementBlockFrequency(&block5);

    IncrementBlockFrequency(&block6);
    IncrementBlockFrequency(&block6);
    IncrementBlockFrequency(&block6);
    IncrementBlockFrequency(&block6);
    IncrementBlockFrequency(&block6);
    IncrementBlockFrequency(&block6);

    IncrementBlockFrequency(&block7);
    IncrementBlockFrequency(&block7);
    IncrementBlockFrequency(&block7);
    IncrementBlockFrequency(&block7);
    IncrementBlockFrequency(&block7);
    IncrementBlockFrequency(&block7);
    IncrementBlockFrequency(&block7);
    put(&set->HashTable,block1);
    put(&set->HashTable,block2);
    put(&set->HashTable,block3);
    put(&set->HashTable,block4);
    put(&set->HashTable,block5);
    put(&set->HashTable,block6);
    put(&set->HashTable,block7);

    printf("\nCount:%d\n",Count(&set->HashTable));

    set->SortHash(&set->HashTable);
    print_blocks_in_set(&set->HashTable);
}