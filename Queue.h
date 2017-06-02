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

    void (*Queue_Destructor)(struct QueueTag *queue);
    bool (*Enqueue)(struct QueueTag **queue, Node **node);
    char* (*Dequeue)(struct QueueTag *pQueue);
    bool (*isEmpty)(struct QueueTag* pQueue);
    void (*print_queue)(struct QueueTag* queue);

} Queue;

Queue *Queue_Constructor(int limit);
void Queue_Destructor(Queue *queue);
bool Enqueue(Queue **queue, Node **node);
char* Dequeue(Queue *pQueue);
bool isEmpty(Queue* pQueue);
void print_queue(Queue* queue);

#endif //ACA_PROJECT_QUEUE_H
