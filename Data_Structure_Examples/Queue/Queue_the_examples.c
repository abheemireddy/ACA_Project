//
// Created by chad on 6/2/17.
//
#include "Queue_the_examples.h"
void Work_with_queue(){
    Queue* queue = Queue_Constructor();
    Instruction data = {instruction:"Store 0001"};
    Node node1 = {data:data};
    Node* pnode1 = &node1;
    queue->Enqueue(&queue,&pnode1);

    Instruction data2 = {instruction:"Store 0010"};
    Node node2 = {data:data2};
    Node* pnode2 = &node2;
    queue->Enqueue(&queue,&pnode2);

    Instruction data3 = {instruction:"Store 0011"};
    Node node3 = {data:data3};
    Node* pnode3 = &node3;
    queue->Enqueue(&queue,&pnode3);

    Instruction data4 = {instruction:"Store 1101"};
    Node node4 = {data:data4};
    Node* pnode4 = &node4;
    queue->Enqueue(&queue,&pnode4);

    print_queue(queue);
    Instruction val = queue->Dequeue(queue);
    printf("dequeued: %s",val.instruction);
}