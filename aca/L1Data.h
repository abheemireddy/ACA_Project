#ifndef __L1DATA_H__
#define __L1DATA_H__

typedef struct CacheBlock
{
	int valid;  // is the block valid?
	int dirty;  // is the block dirty?
	unsigned char data[64]; // the actual data in the block
	int tag;    // only 3 bits
} cb;

extern struct CacheBlock L1Data[256];

void initL1Data();

#endif
