//
// Created by chad on 6/2/17.
//
#include "Queue_the_examples.h"
void Work_with_queue(){
    Queue queue = Queue_Constructor();
    Instruction data = {data:"Store 0001",instruction:1};
    Node node1 = {data:data};
    Node* pnode1 = &node1;
    queue.Enqueue(&queue,&node1);

    Instruction data2 = {data:"Store 0010",instruction:1};
    Node node2 = {data:data2};
    Node* pnode2 = &node2;
    queue.Enqueue(&queue,&node2);

    Instruction data3 = {data:"Store 0011",instruction:1};
    Node node3 = {data:data3};
    Node* pnode3 = &node3;
    queue.Enqueue(&queue,&node3);

    Instruction data4 = {data:"Store 1101",instruction:1};
    Node node4 = {data:data4};
    Node* pnode4 = &node4;
    queue.Enqueue(&queue,&node4);

    print_queue(&queue);
    Instruction val = queue.Dequeue(&queue);
    printf("dequeued: %s",val.data);
}