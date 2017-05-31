//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_QUEUE_H
#define ACA_PROJECT_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct NodeTag {
    char* val;
    struct NodeTag *prev;
} Node;

typedef struct QueueTag {
    Node *head;
    Node *tail;
    int size;
    int limit;
} Queue;

Queue *Queue_Constructor(int limit);
void Queue_Destructor(Queue *queue);
bool Enqueue(Queue *pQueue, Node *item);
Node* Dequeue(Queue *pQueue);
bool isEmpty(Queue* pQueue);

#endif //ACA_PROJECT_QUEUE_H
