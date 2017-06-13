#include "Queue/Queue.h"
#include "Block_Queue/Block_Queue.h"
#include "Controller/Controller.h"
#include "Processor/processor.h"
#include "Data_Structure_Examples/DataStore/DataStore_Examples.h"
#include "Data_Structure_Examples/BlockTransferer/BlockTransferer_Examples.h"
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
    l1Data = Constructor_DataStore();
    l2Data = Constructor_DataStore();
    l1WriteBuffer = Constructor_Buffer();
    l2WriteBuffer = Constructor_Buffer();
    l1VictimCache = Constructor_Buffer();

    l1Controller = Constructor_L1Controller();
    l2Controller = Constructor_L2Controller();
    processor = Constructor_Processor(l1Controller,l2Controller);

    StoreFileInstructionsIntoProcessorQueue(processor);

    int ClockCycleCount = 0;
    while(!isEmpty(processor->InstructionHolder->TransferQueue)){
        if(!isEmpty(processor->InstructionHolder->TransferQueue)){
            while(!isBlockQueueEmpty(l1Controller->writeBlockQueue)){//check for blocks from l2
                BlockOnBus flushedFromBufers = PeekBlock(l1Controller->writeBlockQueue);
                int clockCycleWhenAvailable = flushedFromBufers.clockCycleWhenBlockIsAvailable;
                if(clockCycleWhenAvailable >= ClockCycleCount){
                    Block blockReceived = flushedFromBufers.blockOnBus;
                    WriteBlockToL1Controller(blockReceived);
                    DequeueBlock(l2Controller->writeBlockQueue);
                    l1Controller->waiting = false;
                }else{
                    break;
                }
            }
            if(l1Controller->waiting == false){
                if(!isEmpty(l1Controller->transferer->TransferQueue)){
                    Instruction nextInstructionFromProcessor = Dequeue(processor->InstructionHolder->TransferQueue);
                    Enqueue(l1Controller->transferer->TransferQueue,nextInstructionFromProcessor);
                }
                Instruction nextInstructionForL1ControllerToProcess = GetNextInstruction(l1Controller->transferer);
                CacheLine* read = ProcessL1Instruction(nextInstructionForL1ControllerToProcess);
                if(nextInstructionForL1ControllerToProcess.instruction == 2){
                    if(read == NULL){
                        printf("Did not find in cache, waiting");
                    }else{
                        printf("Read from: %d val %s\n",read->address.bitStringValue,GetData(l1Data,read->dataLine));
                        Dequeue(l1Controller->transferer->TransferQueue);
                    }
                }
            }

            //L2 Controller
            while(!isBlockQueueEmpty(l2Controller->writeBlockQueue)){ //write back blocks from l1
                BlockOnBus flushedFromBufers = PeekBlock(l2Controller->writeBlockQueue);
                int clockCycleWhenAvailable = flushedFromBufers.clockCycleWhenBlockIsAvailable;
                if(clockCycleWhenAvailable >= ClockCycleCount){
                    Block blockReceived = flushedFromBufers.blockOnBus;
                    WriteBlockToL2Controller(blockReceived);
                    DequeueBlock(l2Controller->writeBlockQueue);
                }else{
                    break;
                }
            }
            if(l2Controller->waiting == false){
                if(!isEmpty(l2Controller->transferer->TransferQueue)) {//there is something to process
                    Address blockAddressToGetForL1 = Peek(l2Controller->transferer->TransferQueue).address;
                    FindBlockInL2(blockAddressToGetForL1);
                }
            }

            //DRAM
            while(!isBlockQueueEmpty(dRAM->blockQueue)){
                BlockOnBus flushedFromBufers = PeekBlock(dRAM->blockQueue);
                int clockCycleWhenAvailable = flushedFromBufers.clockCycleWhenBlockIsAvailable;
                if(clockCycleWhenAvailable >= ClockCycleCount){
                    Block blockReceived = flushedFromBufers.blockOnBus;
                    WriteBlockToDRAM(blockReceived);
                    DequeueBlock(dRAM->blockQueue);
                }else{
                    break;
                }
            }
            if(!isEmpty(dRAM->transferer->TransferQueue)){
                Address addressToFindInDRam = GetNextInstruction(dRAM->transferer).address;
                ProcessDRamInstruction(addressToFindInDRam);
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