cmake_minimum_required(VERSION 2.8.7)
project(ACA_Project)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(uthash_files/include)

set(SOURCE_FILES main.c Block/Block.h Set/Set.h Cache/Cache.h Block/Block.c Set/Set.c Queue/Queue.h CacheLine/CacheLine.c Cache/Cache.c Queue/Queue.c Data_Structure_Examples/Set/Set_and_Block_Examples.c Data_Structure_Examples/Set/Set_and_Block_Examples.h Data_Structure_Examples/Queue/Queue_the_examples.h Data_Structure_Examples/Queue/Queue_the_examples.c CacheLine/CacheLine.h Data_Structure_Examples/Block/Block_CacheLine_HashTable_Examples.h Data_Structure_Examples/Block/Block_CacheLine_HashTable_Examples.c L1_Cache.h Address/Address.h Address/Address.c BlockTransferer/BlockTransferer.h DRAM/DRAM.h DRAM/DRAM.c Data_Structure_Examples/DRAM/DRAM_Examples.h Data_Structure_Examples/DRAM/DRAM_Examples.c Buffers/buffers.h Buffers/buffers.c BlockTransferer/BlockTransferer.c Data/DataStore.h Data/DataStore.c Data_Structure_Examples/DataStore/DataStore_Examples.h Data_Structure_Examples/DataStore/DataStore_Examples.c Controller/Controller.h Controller/Controller.c Processor/processor.h Processor/processor.c Data_Structure_Examples/BlockTransferer/BlockTransferer_Examples.h Data_Structure_Examples/BlockTransferer/BlockTransferer_Examples.c Global_Variables.h Block_Queue/Block_Queue.h Block_Queue/Block_Queue.c Instruction/Instruction.h Instruction/Instruction.c BlockOnBus/BlockOnBus.h BlockOnBus/BlockOnBus.c)

add_executable(ACA_Project2 ${SOURCE_FILES})
