#include "Processor/processor.h"
#include <Data_Structure_Examples/DataStore/DataStore_Examples.h>
#include <Data_Structure_Examples/BlockTransferer/BlockTransferer_Examples.h>
#include "Data_Structure_Examples/Set/Set_and_Block_Examples.h"
#include "Data_Structure_Examples/Queue/Queue_the_examples.h"
#include "Data_Structure_Examples/Block/Block_CacheLine_HashTable_Examples.h"
#include "Data_Structure_Examples/DRAM/DRAM_Examples.h"
#include "L1_Cache.h"

int run_examples();

int main(){
    L1Controller* l1Controller = Constructor_L1Controller();
    Transferer* transferer1 = Constructor_Transferer();
    Queue* queue1 = Queue_Constructor();
    transferer1->TransferQueue = queue1;
    l1Controller->transferer = transferer1;

    L2Controller* l2Controller = Constructor_L2Controller();
    Transferer* transferer2 = Constructor_Transferer();
    Queue* queue2 = Queue_Constructor();
    transferer2->TransferQueue = queue2;
    l2Controller->transferer = transferer2;
    Processor* processor = Constructor_Processor(l1Controller,l2Controller);

    processor->run_processor(processor);


    run_examples();//Anu, these should help you with using the pre-created data structures
}


int run_examples() {
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

    StoreAndGetFromBlockTransferer();
}

