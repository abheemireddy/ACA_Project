#include "Processor/processor.h"
#include <Data_Structure_Examples/DataStore/DataStore_Examples.h>
#include <Data_Structure_Examples/BlockTransferer/BlockTransferer_Examples.h>
#include "Data_Structure_Examples/Set/Set_and_Block_Examples.h"
#include "Data_Structure_Examples/Queue/Queue_the_examples.h"
#include "Data_Structure_Examples/Block/Block_CacheLine_HashTable_Examples.h"
#include "Data_Structure_Examples/DRAM/DRAM_Examples.h"
#include "L1_Cache.h"
#include <sys/resource.h>
#include "Buffers/buffers.h"
#include "Global_Variables.h"

void changeStackSize();
int run_examples();

int main(){
    l1WriteBuffer = Constructor_Buffer();
    l1VictimCache = Constructor_Buffer();

    l1Controller = Constructor_L1Controller();
    l2Controller = Constructor_L2Controller();
    processor = Constructor_Processor(l1Controller,l2Controller);

    StoreFileInstructionsIntoProcessorQueue(processor);

    int ClockCycleCount = 0;
    while(!isEmpty(processor->InstructionHolder->TransferQueue)){
        if(!isEmpty(processor->InstructionHolder->TransferQueue)){
            if(l1Controller->waiting == false){
                Instruction nextInstructionFromProcessor = GetNextInstruction(processor->InstructionHolder);
                printf("%d\n",nextInstructionFromProcessor.instruction);
                Enqueue(l1Controller->transferer->TransferQueue,nextInstructionFromProcessor);
                Instruction nextInstructionForL1ControllerToProcess = GetNextInstruction(l1Controller->transferer);
                L1ProcessInstruction(nextInstructionForL1ControllerToProcess);
            }
            if(l2Controller->waiting == false){

            }
        }
        ClockCycleCount += 1;
    }
    printf("Clock Cycles taken:%d\n",ClockCycleCount);

    //run_examples();//Examples of using the data structures
}

int run_examples() {
    AddCacheLinesToBlock();
    ExampleUsingSetHash();
    AddTooManyBlocksTest();
    Work_with_queue();

    Cache* cache = Constructor_Cache(8);
    BuildL1Cache(cache);

    Sample_Add_Overlapping_Key_to_set();

    Add_to_DRAM();

    DataStore_Example();

    StoreAndGetFromBlockTransferer();
}

//Not an issue.  I thought maybe the stack size was an issue, but it was not.
void changeStackSize()
{
    const rlim_t kStackSize = 128 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }
}