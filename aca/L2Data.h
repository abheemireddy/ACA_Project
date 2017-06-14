#ifndef __L2DATA_H__
#define __L2DATA_H__

typedef struct Cache2Block
{
	int valid;  // is the block valid?
	int dirty;  // is the block dirty?
	unsigned char data[8]; // the actual data in the block
	int tag;    // only 3 bits
} c2b;

extern struct Cache2Block L2Data[512];

void initL2Data();

#endif
