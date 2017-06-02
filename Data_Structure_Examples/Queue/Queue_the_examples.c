//
// Created by chad on 6/2/17.
//
#include "Queue_the_examples.h"
void Work_with_queue(){
    Queue* queue = Queue_Constructor(4);
    Node node1 = {val:"Store 0001"};
    Node* pnode1 = &node1;
    queue->Enqueue(&queue,&pnode1);

    Node node2 = {val:"Store 0010"};
    Node* pnode2 = &node2;
    queue->Enqueue(&queue,&pnode2);

    Node node3 = {val:"Store 0011"};
    Node* pnode3 = &node3;
    queue->Enqueue(&queue,&pnode3);

    Node node4 = {val:"Store 0100"};
    Node* pnode4 = &node4;
    queue->Enqueue(&queue,&pnode4);

    print_queue(queue);
    char* val = queue->Dequeue(queue);
    printf("dequeued: %s",val);
}