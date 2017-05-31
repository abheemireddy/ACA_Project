//
// Created by chad on 5/24/17.
//
/*
 * I want to implement the following functions
    empty
    size
    front
    back
    push_back
    pop_front

 */



#ifndef ACA_PROJECT_QUEUE_H
#define ACA_PROJECT_QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//borrowed linkedlist code from http://www.learn-c.org/en/Linked_lists

typedef struct node {
    int val;
    struct node * next;
} node_t;

typedef struct QueueTag {
    int head;
    int tail;
    node_t* valueArray[];
} Queue;

Queue Queue_Constructor();

bool isEmpty(Queue queue){
    if(queue.valueArray[0] == NULL){
        return true;
    }
    return false;
}

node_t* front(Queue queue){
    return queue.valueArray[queue.head];
}

node_t* tail(Queue queue){
    return queue.valueArray[queue.tail];
}

void print_queue(Queue queue) {
    struct node * current = queue.valueArray[queue.head];
    while(current != NULL){
        printf("%d\n",current->val);
        current = current->next;
    }
}

void push_back(Queue queue,char* valueToPush) {
    char** temp = queue.head.
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

//push back
//pop front

int pop_front(Queue queue) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}


int remove_last(node_t * head) {
    int retval = 0;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        return retval;
    }

    /* get to the last node in the list */
    node_t * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the last item of the list, so let's remove current->next */
    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;

}


#endif //ACA_PROJECT_QUEUE_H
