#include <Data_Structure_Examples/DataStore/DataStore_Examples.h>
#include "Data_Structure_Examples/Set/Set_and_Block_Examples.h"
#include "Data_Structure_Examples/Queue/Queue_the_examples.h"
#include "Data_Structure_Examples/Block/Block_CacheLine_HashTable_Examples.h"
#include "Data_Structure_Examples/DRAM/DRAM_Examples.h"
#include "L1_Cache.h"


int main() {
    AddCacheLinesToBlock();
    ExampleUsingSetHash();
    AddTooManyBlocksTest();
    Work_with_queue();

    Cache cache = Constructor_Cache(256);
    Cache* pcache = &cache;
    BuildL1Cache(&pcache);

    Sample_Add_Overlapping_Key_to_set();

    Add_to_DRAM();

    DataStore_Example();
}