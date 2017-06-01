#include <stdio.h>
#include "Set.h"
#include "Block.h"

void ExampleUsingSetHash(){
    Set set = Constructor_Set(4);
    Block case1 = {useFrequency:1,data:"bitString1"};
    Block case2 = {useFrequency:2,data:"bitString2"};
    Block* block1 = malloc(sizeof(Block));
    block1 = &case1;
    set.put(set.hh,&set.HashTable,block1);
    Block* block2 = &case2;
    set.put(set.hh,&set.HashTable,block2);
    Block* returned = set.get(&set.HashTable,block1->data);
    printf("%d",returned->useFrequency);
}
Block GetDummyBlockInstance(){
    Block toAdd = Constructor_Block(4);
    toAdd.Set_Data(&toAdd,"new data");
    return toAdd;
}
void AddTooManyBlocksTest(){
    Set set = Constructor_Set(4);
    Block block1 = GetDummyBlockInstance();
    Block block2 = GetDummyBlockInstance();
    Block block3 = GetDummyBlockInstance();
    Block block4 = GetDummyBlockInstance();
    Block block5 = GetDummyBlockInstance();
    Block block6 = GetDummyBlockInstance();
    Block block7 = GetDummyBlockInstance();
    set.AddBlock(set,&set.HashTable,&block1);
    printf("%d\n",set.Count(&set.HashTable));
    set.AddBlock(set,&set.HashTable,&block2);
    printf("%d\n",set.Count(&set.HashTable));
    set.AddBlock(set,&set.HashTable,&block3);
    printf("%d\n",set.Count(&set.HashTable));
    set.AddBlock(set,&set.HashTable,&block4);
    printf("%d\n",set.Count(&set.HashTable));
    set.AddBlock(set,&set.HashTable,&block5);
    printf("%d\n",set.Count(&set.HashTable));
    set.AddBlock(set,&set.HashTable,&block6);
    printf("%d\n",set.Count(&set.HashTable));
    set.AddBlock(set,&set.HashTable,&block7);
    printf("%d\n",set.Count(&set.HashTable));
}

int main() {
    //ExampleUsingSetHash();
    AddTooManyBlocksTest();
}