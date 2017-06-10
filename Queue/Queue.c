//
// Created by chad on 5/30/17.
//
#include "Queue.h"

//used queue implementation from https://gist.github.com/ArnonEilat/4471278

Instruction* Constructor_Instruction(int instructionNumber,char data[64],Address address){
    Instruction* instruction = malloc(sizeof(Instruction));
    instruction->instruction = instructionNumber;
    instruction->address = address;
    if(data != NULL){
        strcpy(instruction->data,data);
    }else{
        data = NULL;
    }
    return instruction;
}

Node* Constructor_Node(Instruction instruction){
    Node* node = malloc(sizeof(Node));
    node->data = instruction;
    return node;
}

Queue* Queue_Constructor() {
    Queue* queue = malloc(sizeof(Queue));
    queue->limit = 10000;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    queue->Dequeue = &Dequeue;
    queue->Enqueue = &Enqueue;
    queue->isEmpty = &isEmpty;
    queue->Queue_Destructor = &Queue_Destructor;
    queue->print_queue = &print_queue;
    return queue;
}

void Queue_Destructor(Queue *queue) {
    while (!isEmpty(queue)) {
        Dequeue(queue);
    }
    free(queue);
}

void print_queue(Queue* queue){
    Node* current = queue->head;
    while (current->prev != NULL) {
        printf("Node Instruction:%s\n",current->data.data);
        current = current->prev;
    }
}

bool Enqueue(Queue *queue, Instruction instruction) {
    Node* node = Constructor_Node(instruction);
    if ((queue == NULL) || (node == NULL)) {
        return false;
    }

    //good size check!
    if (queue->size >= queue->limit) {
        return false;
    }

    node->prev = NULL;
    if (queue->size == 0) {
        queue->tail = node;
        queue->head = node;

    } else {
        queue->tail->prev = node;
        queue->tail = node;
    }
    queue->size++;
    return true;
}

Instruction Dequeue(Queue *queue) {
    if (isEmpty(queue)){
        Instruction emptyInstruction = {};
        printf("Trying to dequeue from empty queue");
        return emptyInstruction;
    }
    Node* node = queue->head;
    queue->head = (queue->head)->prev;
    queue->size -= 1;
    return node->data;
}

bool isEmpty(Queue* queue) {
    if(queue == NULL){
        return false;
    }
    if (queue->size == 0) {
        return true;
    } else {
        return false;
    }
}

