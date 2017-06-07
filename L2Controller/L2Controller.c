#include <stdio.h>
#include <string.h>
#include "L2Controller.h"
#include "aca/L2Data.h"
#include "aca/MainMemory.h"

void initL2Controller()
{
	// TODO: create a queue of read instructions and initialize it.
}

// write value to l2 cache
void l2Write(int address, int value)
{
	printf("P to L1C: CPUWrite (%d)\n", address);
	// check if address is valid
	int offset = address & 0x3f;
	int tag = address >> 15;
	int line = (address >> 6) & 0x1ff;
	if (!L2Data[line].valid) // block not valid
	{
		printf("L2C to L2D: Data\n");
		printf("Hit\n");
		L2Data[line].data[offset] = (unsigned char)value;
		L2Data[line].valid = 1;
		L2Data[line].dirty = 1;
		L2Data[line].tag = tag;
	}
	else if (L2Data[line].valid && L2Data[line].tag == tag)
	{
		printf("L2C to L2D: Data\n");
		printf("Hit\n");
		L2Data[line].data[offset] = (unsigned char)value;
		L2Data[line].dirty = 1;
	}
	else if (L2Data[line].valid && L2Data[line].tag != tag) // not in Cache!
	{
		// check if dirty, we need to send to victim cache
		if (L2Data[line].dirty)
		{
			printf("L1C to L2D: CPUWrite\n");
			l2Write(address, value);
		}
		printf("L2C to Memory: CPUWrite\n");
		L2Data[line].dirty = 0;
		L2Data[line].tag = tag;
		l2Read(address, L2Data[line].data);  // get data from L2
		printf("Memory to L1C: Data\n");

	}
}

// write back given line to address
void writeBack(int line, int address)
{
	line += 0;
}

void l2Read(int address, unsigned char * block)
{
	// TODO:pop the address from queue, for now assuming the address is 100
	address = 100; // We have to assign the value popped from queue to address variable
	printf("L2C to L1C: CPURead (%d)\n", address);
	// check if address is valid
	int offset = address & 0x3f;
	int tag = address >> 15;
	int line = (address >> 6) & 0xff;

	if (!L2Data[line].valid) // load from main mem
	{
		printf("L2C to Main Memory: CPURead (%d)\n", address);
		printf("Main Memory to L2C: Data\n");
		printf("L2C to L2D: Data\n");
		memcpy(L2Data[line].data, mem + address, 64);
		memcpy(block, mem + address, 64);  // read from memory
		L2Data[line].tag = tag;
		L2Data[line].valid = 1;
		L2Data[line].dirty = 0;
	}
	else if (L2Data[line].valid)  // valid block
	{
		if (L2Data[line].tag == tag)  // same tag!
		{
			memcpy(block, L2Data[line].data, 64);
		}
		else  // other tag! we need to load from memory
		{
			if (L2Data[line].dirty) // dirty block... writeback
			{
				int wbAddress = (L2Data[line].tag << 15) | line << 6;
				writeBack(line, wbAddress);
			}
			printf("L2C to Main Memory: CPURead (%d)\n", address);
			printf("Main Memory to L2C: Data\n");
			printf("L2C to L2D: Data\n");
			memcpy(L2Data[line].data, mem + address, 64);
			memcpy(block, mem + address, 64);  // read from memory
			L2Data[line].tag = tag;
			L2Data[line].valid = 1;
			L2Data[line].dirty = 0;
		}
	}
}

// writebacks data
void l2WriteBack(int address, unsigned char * data)
{
	int offset = address & 0x3f;
	int tag = address >> 15;
	int line = (address >> 6) & 0x1ff;

	if (L2Data[line].valid && L2Data[line].tag == tag)
	{
		memcpy(L2Data[line].data, data, 64); // copy data to block
	}
	else // required block not in L2
	{
		// we need to load the block
		if (L2Data[line].valid == 0) // not a valid block, get it from memory
		{
			printf("L2C to Main Memory: CPURead (%d)\n", address);
			printf("Main Memory to L2C: Data\n");
			printf("L2C to L2D: Data\n");
			memcpy(L2Data[line].data, data, 64);
			L2Data[line].tag = tag;
			L2Data[line].valid = 1;
			L2Data[line].dirty = 1;
		}
		else // valid block, wrong tag
		{
			int wbAddress = (L2Data[line].tag << 15) | line << 6;
			if (L2Data[line].dirty) writeBack(line, wbAddress); // dirty block... write back
			printf("L2C to Main Memory: CPURead (%d)\n", address);
			printf("Main Memory to L2C: Data\n");
			printf("L2C to L2D: Data\n");
			memcpy(L2Data[line].data, data, 64);
			L2Data[line].tag = tag;
			L2Data[line].valid = 1;
			L2Data[line].dirty = 1;
		}
	}
}
