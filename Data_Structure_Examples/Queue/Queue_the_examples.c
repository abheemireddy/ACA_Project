//
// Created by chad on 6/2/17.
//
#include "Queue_the_examples.h"
void Work_with_queue(){
    Address address1 = Constructor_Address("00000000000000000");

    Queue* queue = Queue_Constructor();
    Instruction* data = Constructor_Instruction(1,"Store 001",address1);
    queue->Enqueue(queue,data);

    Instruction* data2 = Constructor_Instruction(1,"Store 0011",address1);
    queue->Enqueue(queue,data2);

    Instruction* data3 = Constructor_Instruction(1,"Store 0011",address1);//{data:"Store 0011",instruction:1,address:address1};
    queue->Enqueue(queue,data3);

    Instruction* data4 = Constructor_Instruction(1,"Store 1101",address1);//{data:"Store 1101",instruction:1,address:address1};
    queue->Enqueue(queue,data4);

    print_queue(queue);
    Instruction* val = queue->Dequeue(queue);
    printf("dequeued: %s",val->data);
}