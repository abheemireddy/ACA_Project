//
// Created by chad on 5/24/17.
//
#ifndef ACA_PROJECT_BLOCK_QUEUE_H
#define ACA_PROJECT_BLOCK_QUEUE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <BlockOnBus/BlockOnBus.h>

typedef struct NodeTag {
    BlockOnBus block;
    struct NodeTag* prev;
} Node;

Node* Constructor_BlockNode(BlockOnBus block);

typedef struct BlockQueueTag {
    Node *head;
    Node *tail;
    int size;
    int limit;
} BlockQueue;

BlockQueue* Constructor_BlockQueue();

BlockOnBus PeekBlock(struct BlockQueueTag *blockQueue);
bool EnqueueBlock(struct BlockQueueTag *queue, BlockOnBus block);
BlockOnBus DequeueBlock(struct BlockQueueTag *blockQueue);
bool isBlockQueueEmpty(struct BlockQueueTag* blockQueue);
void print_BlockQueue(struct BlockQueueTag* blockQueue);

#endif //ACA_PROJECT_BLOCK_QUEUE_H
