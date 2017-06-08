//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_QUEUE_H
#define ACA_PROJECT_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Address/Address.h"

typedef struct InstructionTag{
    int clockCycleWhenThisCanBeRead;
    int instruction;
    char* data; //data stored as char* in char[64][64]
    Address address;
} Instruction;

Instruction Constructor_Instruction(int instructionNumber,char* data,Address address);

typedef struct NodeTag {
    Instruction data;
    struct NodeTag *prev;
} Node;

Node Constructor_Node(Instruction instruction);

typedef struct QueueTag {
    Node *head;
    Node *tail;
    int size;
    int limit;

    void (*Queue_Destructor)(struct QueueTag *queue);
    bool (*Enqueue)(struct QueueTag *queue, Node* node);
    Instruction (*Dequeue)(struct QueueTag *pQueue);
    bool (*isEmpty)(struct QueueTag* pQueue);
    void (*print_queue)(struct QueueTag* queue);

} Queue;

Queue Queue_Constructor();
void Queue_Destructor(Queue *queue);
bool Enqueue(Queue *queue, Node *node);
Instruction Dequeue(Queue *queue);
bool isEmpty(Queue* pQueue);
void print_queue(Queue* queue);

#endif //ACA_PROJECT_QUEUE_H
