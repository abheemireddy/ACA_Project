cmake_minimum_required(VERSION 3.7)
project(ACA_Project)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(uthash/include)

set(SOURCE_FILES main.c Block.h Set.h Cache.h Block.c Set.c Queue.h CacheLine.c Cache.c Queue.c Data_Structure_Examples/Set/Set_and_Block_Examples.c Data_Structure_Examples/Set/Set_and_Block_Examples.h Data_Structure_Examples/Queue/Queue_the_examples.h Data_Structure_Examples/Queue/Queue_the_examples.c CacheLine.h Data_Structure_Examples/Block/Block_CacheLine_HashTable_Examples.h Data_Structure_Examples/Block/Block_CacheLine_HashTable_Examples.c L1_Cache.h Address.h Address.c)

add_executable(ACA_Project2 ${SOURCE_FILES})

