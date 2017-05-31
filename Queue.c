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
    return queue;
}

void Queue_Destructor(Queue *queue) {
    Node *node2Free;
    while (!isEmpty(queue)) {
        node2Free = Dequeue(queue);
        free(node2Free);
    }
    free(queue);
}

bool Enqueue(Queue *queue, Node *item) {
    if ((queue == NULL) || (item == NULL)) {
        return false;
    }

    //good size check!
    if (queue->size >= queue->limit) {
        return false;
    }

    item->prev = NULL;
    if (queue->size == 0) {
        queue->tail = item;
        queue->head = item;

    } else {
        queue->tail->prev = item;
        queue->tail = item;
    }
    queue->size++;
    return true;
}

Node * Dequeue(Queue *queue) {
    Node *node;
    if (isEmpty(queue))
        return NULL;
    node = queue->head;
    queue->head = (queue->head)->prev;
    queue->size -= 1;
    return node;
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
