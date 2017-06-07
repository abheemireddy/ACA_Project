
#include "L1Controller.h"


void L1_write(int address, int value)
{
	printf("P to L1C: CPUWrite (%d)\n", address);
	// check if address is valid
	int offset = address & 0x3f;
	int tag = address >> 14;
	int line = (address >> 6) & 0xff;
	if (!L1Data[line].valid) // block not valid
	{
		printf("L1C to L1D: Data\n");
		printf("Hit\n");
		L1Data[line].data[offset] = (unsigned char)value;
		L1Data[line].valid = 1;
		L1Data[line].dirty = 1;
		L1Data[line].tag = tag;
	}
	else if (L1Data[line].valid && L1Data[line].tag == tag)
	{
		printf("L1C to L1D: Data\n");
		printf("Hit\n");
		L1Data[line].data[offset] = (unsigned char)value;
		L1Data[line].dirty = 1;
	}
	else if (L1Data[line].valid && L1Data[line].tag != tag) // not in Cache!
	{
		// check if dirty, we need to writeback
		if (L1Data[line].dirty)
		{
			printf("L1C to L2D: CPUWrite\n");
			l2Write(address, value);
		}
		printf("L1C to L2C: CPURead\n");
		L1Data[line].dirty = 0;
		L1Data[line].tag = tag;
		//TODO : push the given address to read queue
		l2Read(address, L1Data[line].data);  // get data from L2
		printf("L2C to L1C: Data\n");

	}
}

int L1_read(int address)
{
	printf("P to L1C: CPURead (%d)\n", address);
	// check if address is valid
	int offset = address & 0x3f;
	int tag = address >> 14;
	int line = (address >> 6) & 0xff;

	if (L1Data[line].valid && L1Data[line].tag == tag)
	{
		printf("Hit\n");
		printf("L1 to D: CPURead (%d)\n", address);
		return L1Data[line].data[offset];
	}
	else if (!L1Data[line].valid)
	{
		printf("L1C to L2C: CPURead (%d)\n", address);
		L1Data[line].dirty = 0;
		L1Data[line].tag = tag;
		L1Data[line].valid = 1;
		///TODO : push the given address to read queue
		l2Read(address, L1Data[line].data);  // get data from L2
		printf("L2C to L1C: Data\n");
		return L1Data[line].data[offset];
	}
	else if (L1Data[line].valid && L1Data[line].tag != tag) // reading from a different tag
	{
		// first we need to send the block to the victim cache
		int vaddress = (L1Data[line].tag << 14) | line << 6; // starting address of current stored block

		//TODO:  send the block to the victim cache

		if (L1Data[line].dirty) // dirty... we need to writeback the block
		{
			printf("L1C to L2C: Data (Writeback)\n");
			int wbAddress = (L1Data[line].tag << 14) | line << 6;
			l2WriteBack(wbAddress, L1Data[line].data);
		}

		// first check if the block is in victim cache and then get victim cache data to block
		//TODO: check if the block is in victim cache
		int checkAddress(int address)
		{
			return 1; //check if the block is in victim cache if so return 1
						//else return 0;
		}

		if (checkAddress(address))
		{
			L1Data[line].dirty = 0;
			L1Data[line].tag = tag;
			printf("L1C to Victim: CPURead (%d)\n", address);
			//TODO:get victim cache data to block
		}
		else // block not in victim cache
		{
			L1Data[line].dirty = 0;
			L1Data[line].tag = tag;
			printf("L1C to L2C: CPURead (%d)\n", address);
			// TODO: push the given address into the read queue of L2
			l2Read(address, L1Data[line].data);  // get data from L2
			printf("L2C to L1C: Data\n");
		}
		return L1Data[line].data[offset];

	}

	return -1;
}
