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
    dRAM = Constructor_DRAM();
    l1Data = Constructor_DataStore();
    l2Data = Constructor_DataStore();
    l1WriteBuffer = Constructor_Buffer();
    l2WriteBuffer = Constructor_Buffer();
    l1VictimCache = Constructor_Buffer();

    l1Controller = Constructor_L1Controller();
    l2Controller = Constructor_L2Controller();
    processor = Constructor_Processor(l1Controller,l2Controller);

    StoreFileInstructionsIntoProcessorQueue(processor);

    ClockCycleCount = 0;
    //L1 Controller

    //1. Check for blocks being sent to L1 from L2
    while(!isEmpty(processor->InstructionHolder->TransferQueue) || !isEmpty(l1Controller->transferer->TransferQueue)) {
        while (!isBlockQueueEmpty(l1Controller->writeBlockQueue)) {//check for blocks from l2
            BlockOnBus* flushedFromBufers = PeekBlock(l1Controller->writeBlockQueue);
            int clockCycleWhenAvailable = flushedFromBufers->clockCycleWhenBlockIsAvailable;
            if (clockCycleWhenAvailable <= ClockCycleCount) {
                Block* blockReceived = flushedFromBufers->blockOnBus;
                if (blockReceived->isIdle == true) {
                    blockReceived->isIdle = false;
                }
                if(l1Controller->waiting == true){
                    if(blockReceived->address.Tag == L1controllerIsIdleUntilItReceivesThisBlock.address.Tag){
                        printf("L1 Controller being released from idle\n");
                        l1Controller->waiting = false;
                    }
                }
                WriteBlockToL1Controller(blockReceived);
                //DequeueBlock(l2Controller->writeBlockQueue);
            } else {
                break;
            }
        }

        //Set* settt = getSetByIndex(&l1Controller->cache->HashTable,0);
        //2. If L1 is not blocked, process the next request from the processor
        if(l1Controller->waiting == false && (!isEmpty(processor->InstructionHolder->TransferQueue) || !isEmpty(l1Controller->transferer->TransferQueue))){
            if(!isEmpty(processor->InstructionHolder->TransferQueue)){
                Instruction nextInstructionFromProcessor = Dequeue(processor->InstructionHolder->TransferQueue);
                if(nextInstructionFromProcessor.instruction == 1){
                    printf("P to L1C: CPUWrite to %d value:%s\n",nextInstructionFromProcessor.address.bitStringValue,nextInstructionFromProcessor.data);
                }else{
                    printf("P to L1C: CPURead from %d\n",nextInstructionFromProcessor.address.bitStringValue);
                }
                Enqueue(l1Controller->transferer->TransferQueue, nextInstructionFromProcessor);
            }
            if(!isEmpty(l1Controller->transferer->TransferQueue)){
                Instruction nextInstructionForL1ControllerToProcess = GetNextInstruction(l1Controller->transferer);
                CacheLine *read = ProcessL1Instruction(nextInstructionForL1ControllerToProcess);
                if (nextInstructionForL1ControllerToProcess.instruction == 2) {
                    if (read == NULL) {
                        ///did not find in cache
                    } else {
                        printf("***Successfully read from L1: %d val %s at clock cycle:%d\n", read->address.bitStringValue, GetData(l1Data, read->dataLine),ClockCycleCount);
                        Dequeue(l1Controller->transferer->TransferQueue);
                    }
                }
            }
        }

        //L2 Controller

        //1. Check for writebacks from L1 and Data from L2
        while (!isBlockQueueEmpty(l2Controller->writeBlockQueue)) { //write back blocks from l1
            BlockOnBus* flushedFromBufers = PeekBlock(l2Controller->writeBlockQueue);
            int clockCycleWhenAvailable = flushedFromBufers->clockCycleWhenBlockIsAvailable;
            if (clockCycleWhenAvailable <= ClockCycleCount) {
                Block* blockReceived = flushedFromBufers->blockOnBus;
                if (blockReceived->isIdle == true) {
                    blockReceived->isIdle = false;
                }
                if (l2Controller->waiting == true) {
                    if (blockReceived->address.Tag ==
                        L2controllerIsIdleUntilItReceivesThisBlock.address.Tag) {
                        printf("L2 Controller being released from idle\n");
                        l2Controller->waiting = false;
                    }
                }
                WriteBlockToL2Controller(flushedFromBufers);
                DequeueBlock(l2Controller->writeBlockQueue);
            } else {
                break;
            }
        }
        //2. Process requests for data from L1
        if(!isEmpty(l2Controller->transferer->TransferQueue) && l2Controller->waiting == false) {//there is something to process
            Instruction blockInstructionFromL1 = Peek(l2Controller->transferer->TransferQueue);
            FindBlockInL2(blockInstructionFromL1);
        }

        //DRAM

        //1. Check for writebacks from L2
        while (!isBlockQueueEmpty(dRAM->writeBlockQueue)) {
            BlockOnBus* flushedFromBufers = PeekBlock(dRAM->writeBlockQueue);
            int clockCycleWhenAvailable = flushedFromBufers->clockCycleWhenBlockIsAvailable;
            if (clockCycleWhenAvailable <= ClockCycleCount) {
                Block* blockReceived = flushedFromBufers->blockOnBus;
                if (blockReceived->isIdle == true) {
                    blockReceived->isIdle = false;
                    l1Controller->waiting = false;
                }
                WriteBlockToDRAM(flushedFromBufers);
                DequeueBlock(dRAM->writeBlockQueue);
            } else {
                break;
            }
        }
        //2. Process instructions from L2
        if(!isEmpty(dRAM->transferer->TransferQueue)) {
            Instruction DRamInstruction = GetNextInstruction(dRAM->transferer);
            ProcessDRamInstruction(DRamInstruction);
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