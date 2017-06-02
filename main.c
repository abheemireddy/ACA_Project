#include <stdio.h>
#include "Set.h"
#include "Block.h"

void ExampleUsingSetHash(){
    Set set = Constructor_Set(4);
    Block case1 = {useFrequency:1,data:"bitString1"};
    Block case2 = {useFrequency:2,data:"bitString2"};
    Block* block1 = malloc(sizeof(Block));
    block1 = &case1;
    set.put(&set.HashTable,block1);
    Block* block2 = &case2;
    set.put(&set.HashTable,block2);
    Block* returned = set.get(&set.HashTable,block2->data);
    printf("use Frequency: %d\n",returned->useFrequency);
}
Block GetDummyBlockInstance(char* data){
    Block toAdd = Constructor_Block(4);
    toAdd.Set_Data(&toAdd,data);
    return toAdd;
}
void AddTooManyBlocksTest(){
    Set set = Constructor_Set(4);

    Block block1 = GetDummyBlockInstance("7");
    Block* pblock1 = &block1;
    Block block2 = GetDummyBlockInstance("6");
    Block* pblock2 = &block2;
    Block block3 = GetDummyBlockInstance("5");
    Block* pblock3 = &block3;
    Block block4 = GetDummyBlockInstance("4");
    Block* pblock4 = &block4;
    Block block5 = GetDummyBlockInstance("3");
    Block* pblock5 = &block5;
    Block block6 = GetDummyBlockInstance("2");
    Block* pblock6 = &block6;
    Block block7 = GetDummyBlockInstance("1");
    Block* pblock7 = &block7;

    IncrementBlockFrequency(&pblock1);
    IncrementBlockFrequency(&pblock1);
    IncrementBlockFrequency(&pblock1);

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

int main() {
    ExampleUsingSetHash();
    AddTooManyBlocksTest();
}