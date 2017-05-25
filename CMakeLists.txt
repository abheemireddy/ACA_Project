cmake_minimum_required(VERSION 3.7)
project(ACA_Project)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(uthash/include)

set(SOURCE_FILES main.c Block.h Set.h Cache.h Block.c Set.c Queue.h cache_line.h)

add_executable(ACA_Project2 ${SOURCE_FILES})

