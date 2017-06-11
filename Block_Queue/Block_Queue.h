//
// Created by root on 6/10/17.
//

#ifndef ACA_PROJECT_BLOCK_QUEUE_H
#define ACA_PROJECT_BLOCK_QUEUE_H
//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_QUEUE_H
#define ACA_PROJECT_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <Block/Block.h>
#include "Address/Address.h"

typedef struct NodeTag {
    Block block;
    struct NodeTag* prev;
} Node;

Node* Constructor_BlockNode(Block block);

typedef struct BlockQueueTag {
    Node *head;
    Node *tail;
    int size;
    int limit;

    Block (*PeekBlock)(struct BlockQueueTag *blockQueue);
    bool (*EnqueueBlock)(struct BlockQueueTag *blockQueue, Block block);
    Block (*DequeueBlock)(struct BlockQueueTag *blockQueue);
    bool (*isBlockQueueEmpty)(struct BlockQueueTag* blockQueue);
    void (*print_BlockQueue)(struct BlockQueueTag* blockQueue);

} BlockQueue;

BlockQueue* Constructor_BlockQueue();

Block PeekBlock(struct BlockQueueTag *blockQueue);
bool EnqueueBlock(struct BlockQueueTag *blockQueue, Block block);
Block DequeueBlock(struct BlockQueueTag *blockQueue);
bool isBlockQueueEmpty(struct BlockQueueTag* blockQueue);
void print_BlockQueue(struct BlockQueueTag* blockQueue);

#endif //ACA_PROJECT_QUEUE_H

#endif //ACA_PROJECT_BLOCK_QUEUE_H
