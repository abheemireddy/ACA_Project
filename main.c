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
    L2Controller* l2Controller = Constructor_L2Controller();
    Processor* processor = Constructor_Processor(l1Controller,l2Controller);

    processor->StoreFileInstructionsIntoProcessorQueue(processor);

    int ClockCycleCount = 0;
    while(!processor->InstructionHolder->TransferQueue->isEmpty(processor->InstructionHolder->TransferQueue)){
        Instruction* nextInstructionFromProcessor = processor->InstructionHolder->GetNextInstruction(processor->InstructionHolder);
        if(nextInstructionFromProcessor != NULL){
            printf("%d\n",nextInstructionFromProcessor->instruction);
        }
        ClockCycleCount += 1;
    }
    printf("Clock Cycles taken:%d\n",ClockCycleCount);

    run_examples();//Examples of using the data structures
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

