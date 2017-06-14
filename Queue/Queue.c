//
// Created by chad on 5/30/17.
//
#include "Queue.h"

//used queue implementation from



QNode* Constructor_QNode(Instruction instruction){
    QNode* node = malloc(sizeof(QNode));
    node->data = instruction;
    return node;
}

Queue* Queue_Constructor() {
    Queue* queue = malloc(sizeof(Queue));
    queue->limit = 10000;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void Queue_Destructor(Queue *queue) {
    while (!isEmpty(queue)) {
        Dequeue(queue);
    }
    free(queue);
}

void print_queue(Queue* queue){
    QNode* current = queue->head;
    while (current->prev != NULL) {
        printf("QNode Instruction:%s\n",current->data.data);
        current = current->prev;
    }
}

bool Enqueue(Queue *queue, Instruction instruction) {
    QNode* node = Constructor_QNode(instruction);
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

Instruction Peek(Queue *queue) {
    if (isEmpty(queue)){
        Instruction emptyInstruction = {};
        printf("Empty Queue");
        return emptyInstruction;
    }
    QNode* node = queue->head;
    return node->data;
}

Instruction Dequeue(Queue *queue) {
    if (isEmpty(queue)){
        Instruction emptyInstruction = {};
        printf("Trying to dequeue from empty queue");
        return emptyInstruction;
    }
    QNode* node = queue->head;
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

