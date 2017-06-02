//
// Created by chad on 5/30/17.
//
#include "Queue.h"

//used queue implementation from https://gist.github.com/ArnonEilat/4471278

Queue *Queue_Constructor(int limit) {
    Queue *queue = (Queue*) malloc(sizeof (Queue));
    queue->limit = limit;
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
        printf("Node Value:%s\n",current->val);
        current = current->prev;
    }
}

bool Enqueue(Queue **queue, Node **node) {
    if (((*queue) == NULL) || (node == NULL)) {
        return false;
    }

    //good size check!
    if ((*queue)->size >= (*queue)->limit) {
        return false;
    }

    (*node)->prev = NULL;
    if ((*queue)->size == 0) {
        (*queue)->tail = *node;
        (*queue)->head = *node;

    } else {
        (*queue)->tail->prev = *node;
        (*queue)->tail = *node;
    }
    (*queue)->size++;
    return true;
}

char * Dequeue(Queue *queue) {
    Node *node;
    if (isEmpty(queue))
        return NULL;
    node = queue->head;
    //free(node);
    queue->head = (queue->head)->prev;
    queue->size -= 1;
    return node->val;
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

