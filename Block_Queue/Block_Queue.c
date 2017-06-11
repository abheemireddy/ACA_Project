//
// Created by root on 6/10/17.
//
//
// Created by chad on 5/30/17.
//
#include "Block_Queue.h"

Node* Constructor_BlockNode(Block block){
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
        printf("Node Instruction:%d\n",current->block.address.bitStringValue);
        current = current->prev;
    }
}

bool EnqueueBlock(BlockQueue *queue, Block block) {
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

Block PeekBlock(BlockQueue *queue) {
    if (isBlockQueueEmpty(queue)){
        Block emptyInstruction = {};
        printf("Empty BlockQueue");
        return emptyInstruction;
    }
    Node* node = queue->head;
    return node->block;
}

Block DequeueBlock(BlockQueue *queue) {
    if (isBlockQueueEmpty(queue)){
        Block emptyInstruction = {};
        printf("Trying to dequeue from empty queue");
        return emptyInstruction;
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


