//
// Created by chad on 6/5/17.
//

#include "buffers.h"
#include "Block/Block.h"

Buffer Constructor_Buffer(){
    Buffer buffer = {};
    //Transferer transferer = Con
    buffer.HashTable = NULL;
    buffer.putBlock = &putBlockInBuffer;
    buffer.getBlock = &getBlockFromBuffer;
    buffer.removeBlockFromBuffer = &removeBlockFromBuffer;
    buffer.CountBlocks = &CountBlocksInBuffer;
    buffer.print_all_blocks = &print_all_blocks_in_buffer;
    buffer.removeBlockFromBuffer = &removeBlockFromBuffer;
    return buffer;
}

void putBlockInBuffer(Block** HashTable,Block *value) {  //key is useFrequency of the block.  Seems magical
    if(value->address.bitString == NULL){
        printf("The passed block needs to have attribute address set");
    }
    /*Block* alreadyInHashTable = getBlock(HashTable,value->address.bitStringValue);//overwrite duplicate keys
    if(alreadyInHashTable != NULL){
        removeBlockFromBuffer(HashTable,alreadyInHashTable);
    }*/
    HASH_ADD_INT(*HashTable, address.bitStringValue,value );
}

void removeBlockFromBuffer(Block** HashTable,Block* blockToRemove) {
    HASH_DEL( *HashTable, blockToRemove);//removes blocks of type block
}

Block* getBlockFromBuffer(Block** HashTable,int key) {
    Block *hashTableStoresInThisBlock;

    HASH_FIND_INT( *HashTable, &key, hashTableStoresInThisBlock );//find block_id and put into hashTableStoresInThisBlock
    return hashTableStoresInThisBlock;
}

int CountBlocksInBuffer(Block** HashTable){
    int num_in_hashtable;
    num_in_hashtable = HASH_COUNT(*HashTable);
    return num_in_hashtable;
}

void print_all_blocks_in_buffer(Block** HashTable) {
    Block* s;
    Block* tmp;
    HASH_ITER(hh,*HashTable,s,tmp){
        printf("address: %d\n",s->address.bitStringValue);
    }
}
