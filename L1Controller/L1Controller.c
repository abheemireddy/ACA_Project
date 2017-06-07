
#include "L1Controller.h"

L1Controller Constructor_L1Controller(){
    L1Controller l1Controller = {};
    l1Controller.L1_read = &L1_read;
    l1Controller.L1_write = &L1_write;
    return l1Controller;
}


void L1_write(Address address, int value)
{
	printf("P to L1C: CPUWrite (%d)\n", address.bitStringValue);
	// check if address is valid
	if (!L1Data[address.Index].valid) // block not valid
	{
		printf("L1C to L1D: Data\n");
		printf("Hit\n");
		L1Data[address.Index].data[address.Offset] = (unsigned char)value;
		L1Data[address.Index].valid = 1;
		L1Data[address.Index].dirty = 1;
		L1Data[address.Index].tag = address.Tag;
	}
	else if (L1Data[address.Index].valid && L1Data[address.Index].tag == address.Tag)
	{
		printf("L1C to L1D: Data\n");
		printf("Hit\n");
		L1Data[address.Index].data[address.Offset] = (unsigned char)value;
		L1Data[address.Index].dirty = 1;
	}
	else if (L1Data[address.Index].valid && L1Data[address.Index].tag != address.Tag) // not in Cache!
	{
		// check if dirty, we need to writeback
		if (L1Data[address.Index].dirty)
		{
			printf("L1C to L2D: CPUWrite\n");
			l2Write(address, value);
		}
		printf("L1C to L2C: CPURead\n");
		L1Data[address.Index].dirty = 0;
		L1Data[address.Index].tag = address.Tag;
		//TODO : push the given address to read queue
		l2Read(address, L1Data[address.Index].data);  // get data from L2
		printf("L2C to L1C: Data\n");

	}
}

int L1_read(Address address)
{
	printf("P to L1C: CPURead (%d)\n", address.bitStringValue);
	// check if address is valid

	if (L1Data[address.Index].valid && L1Data[address.Index].tag == address.Tag)
	{
		printf("Hit\n");
		printf("L1 to D: CPURead (%d)\n", address.bitStringValue);
		return L1Data[address.Index].data[address.Offset];
	}
	else if (!L1Data[address.Index].valid)
	{
		printf("L1C to L2C: CPURead (%d)\n", address.bitStringValue);
		L1Data[address.Index].dirty = 0;
		L1Data[address.Index].tag = address.Tag;
		L1Data[address.Index].valid = 1;
		///TODO : push the given address to read queue
		l2Read(address, L1Data[address.Index].data);  // get data from L2
		printf("L2C to L1C: Data\n");
		return L1Data[address.Index].data[address.Offset];
	}
	else if (L1Data[address.Index].valid && L1Data[address.Index].tag != address.Tag) // reading from a different tag
	{
		// first we need to send the block to the victim cache
		int vaddress = (L1Data[address.Index].tag << 14) | address.Index << 6; // starting address of current stored block

		//TODO:  send the block to the victim cache

		if (L1Data[address.Index].dirty) // dirty... we need to writeback the block
		{
			printf("L1C to L2C: Data (Writeback)\n");
			//int wbAddress = (L1Data[address.Index].tag << 14) | address.Index << 6;
			l2WriteBack(address, L1Data[address.Index].data);
		}

		// first check if the block is in victim cache and then get victim cache data to block
		//TODO: check if the block is in victim cache
		int checkAddress(int address)
		{
			return 1; //check if the block is in victim cache if so return 1
						//else return 0;
		}

		if (checkAddress(address.bitStringValue))
		{
			L1Data[address.Index].dirty = 0;
			L1Data[address.Index].tag = address.Tag;
			printf("L1C to Victim: CPURead (%d)\n", address.bitStringValue);
			//TODO:get victim cache data to block
		}
		else // block not in victim cache
		{
			L1Data[address.Index].dirty = 0;
			L1Data[address.Index].tag = address.Tag;
			printf("L1C to L2C: CPURead (%d)\n", address.bitStringValue);
			// TODO: push the given address into the read queue of L2
			l2Read(address, L1Data[address.Index].data);  // get data from L2
			printf("L2C to L1C: Data\n");
		}
		return L1Data[address.Index].data[address.Offset];

	}

	return -1;
}
