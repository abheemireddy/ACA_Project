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
    while (!isEmpty(queue)) {
        printf("Node Value:%s\n",current->val);
        current = current->prev;
        queue->Dequeue(queue);
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
/*
int main() {
    int i;
    Queue *pQ = ConstructQueue(7);
    Node *pN;

    for (i = 0; i < 9; i++) {
        pN = (Node*) malloc(sizeof (Node));
        pN->data.info = 100 + i;
        Enqueue(pQ, pN);
    }

    while (!isEmpty(pQ)) {
        pN = Dequeue(pQ);
        printf("\nDequeued: %d", pN->data);
        free(pN);
    }
    DestructQueue(pQ);
    return (EXIT_SUCCESS);
}*/
