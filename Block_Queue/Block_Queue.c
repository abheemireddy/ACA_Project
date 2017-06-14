//
// Created by root on 6/10/17.
//
//
// Created by chad on 5/30/17.
//
#include "Cache/Cache.h"
#include "Block_Queue.h"
#include "Global_Variables.h"
#include "Set/Set.h"

Node* Constructor_BlockNode(BlockOnBus* block){
    Node* node = malloc(sizeof(Node));
    node->block = block;
    return node;
}

BlockQueue* Constructor_BlockQueue() {
    BlockQueue* queue = malloc(sizeof(BlockQueue));
    queue->limit = 10000;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void print_BlockQueue(BlockQueue* blockQueue){
    Node* current = blockQueue->head;
    while (current->prev != NULL) {
        printf("Node Instruction:%d\n",current->block->blockOnBus->address.bitStringValue);
        current = current->prev;
    }
}

bool EnqueueBlock(BlockQueue *queue, BlockOnBus* block) {
    Node* node = Constructor_BlockNode(block);
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

BlockOnBus* PeekBlock(BlockQueue *queue) {
    if (isBlockQueueEmpty(queue)){
        printf("Peeking from empty queue");
        return NULL;
    }
    Node* node = queue->head;
    return node->block;
}

BlockOnBus* DequeueBlock(BlockQueue *queue) {
    if (isBlockQueueEmpty(queue)){
        printf("Trying to dequeue from empty queue\n");
        return NULL;
    }
    Node* node = queue->head;
    queue->head = (queue->head)->prev;
    queue->size -= 1;
    return node->block;
}

bool isBlockQueueEmpty(BlockQueue* queue) {
    if(queue == NULL){
        return false;
    }
    if (queue->size == 0) {
        return true;
    } else {
        return false;
    }
}


