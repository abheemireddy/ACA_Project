#include "L2Controller.h"
#include "Global_Variables.h"

L2Controller* Constructor_L2Controller(){
    L2Controller* l2Controller = malloc(sizeof(L2Controller));
	Transferer* transferer = Constructor_Transferer();
	l2Controller->transferer = transferer;
	l2Controller->waiting = false;
	l2Controller->dataFromDRAM = NULL;
    return l2Controller;
}

// write value to l2 cache
void l2Write(Address address, int value)
{
	printf("P to L1C: CPUWrite (%d)\n", address.bitStringValue);
	// check if address is valid
	if (!L2Data[address.Index].valid) // block not valid
	{
		printf("L2C to L2D: Data\n");
		printf("Hit\n");
		L2Data[address.Index].data[address.Offset] = (unsigned char)value;
		L2Data[address.Index].valid = 1;
		L2Data[address.Index].dirty = 1;
		L2Data[address.Index].tag = address.Tag;
	}
	else if (L2Data[address.Index].valid && L2Data[address.Index].tag == address.Tag)
	{
		printf("L2C to L2D: Data\n");
		printf("Hit\n");
		L2Data[address.Index].data[address.Offset] = (unsigned char)value;
		L2Data[address.Index].dirty = 1;
	}
	else if (L2Data[address.Index].valid && L2Data[address.Index].tag != address.Tag) // not in Cache!
	{
		// check if dirty, we need to send to victim cache
		if (L2Data[address.Index].dirty)
		{
			printf("L1C to L2D: CPUWrite\n");
			l2Write(address, value);
		}
		printf("L2C to Memory: CPUWrite\n");
		L2Data[address.Index].dirty = 0;
		L2Data[address.Index].tag = address.Tag;
		l2Read(address, L2Data[address.Index].data);  // get data from L2
		printf("Memory to L1C: Data\n");

	}
}

// write back given line to address
void writeBack(int line, int address)
{
	line += 0;
}

void l2Read(Address address, unsigned char * block)
{
	// TODO:pop the address from queue, for now assuming the address is 100
	//address = 100; // We have to assign the value popped from queue to address variable
	printf("L2C to L1C: CPURead (%d)\n", address.bitStringValue);
	// check if address is valid

	if (!L2Data[address.Index].valid) // load from main mem
	{
		printf("L2C to Main Memory: CPURead (%d)\n", address.bitStringValue);
		printf("Main Memory to L2C: Data\n");
		printf("L2C to L2D: Data\n");
		memcpy(L2Data[address.Index].data, mem + address.bitStringValue, 64);
		memcpy(block, mem + address.bitStringValue, 64);  // read from memory
		L2Data[address.Index].tag = address.Tag;
		L2Data[address.Index].valid = 1;
		L2Data[address.Index].dirty = 0;
	}
	else if (L2Data[address.Index].valid)  // valid block
	{
		if (L2Data[address.Index].tag == address.Tag)  // same address.Tag!
		{
			memcpy(block, L2Data[address.Index].data, 64);
		}
		else  // other address.Tag! we need to load from memory
		{
			if (L2Data[address.Index].dirty) // dirty block... writeback
			{
				int wbAddress = (L2Data[address.Index].tag << 15) | address.Index << 6;
				writeBack(address.Index, wbAddress);
			}
			printf("L2C to Main Memory: CPURead (%d)\n", address.bitStringValue);
			printf("Main Memory to L2C: Data\n");
			printf("L2C to L2D: Data\n");
			memcpy(L2Data[address.Index].data, mem + address.bitStringValue, 64);
			memcpy(block, mem + address.bitStringValue, 64);  // read from memory
			L2Data[address.Index].tag = address.Tag;
			L2Data[address.Index].valid = 1;
			L2Data[address.Index].dirty = 0;
		}
	}
}

// writebacks data
void l2WriteBack(Address address, unsigned char * data)
{

	if (L2Data[address.Index].valid && L2Data[address.Index].tag == address.Tag)
	{
		memcpy(L2Data[address.Index].data, data, 64); // copy data to block
	}
	else // required block not in L2
	{
		// we need to load the block
		if (L2Data[address.Index].valid == 0) // not a valid block, get it from memory
		{
			printf("L2C to Main Memory: CPURead (%d)\n", address.bitStringValue);
			printf("Main Memory to L2C: Data\n");
			printf("L2C to L2D: Data\n");
			memcpy(L2Data[address.Index].data, data, 64);
			L2Data[address.Index].tag = address.Tag;
			L2Data[address.Index].valid = 1;
			L2Data[address.Index].dirty = 1;
		}
		else // valid block, wrong address.Tag
		{
			int wbAddress = (L2Data[address.Index].tag << 15) | address.Index << 6;
			if (L2Data[address.Index].dirty) writeBack(address.Index, wbAddress); // dirty block... write back
			printf("L2C to Main Memory: CPURead (%d)\n", address.bitStringValue);
			printf("Main Memory to L2C: Data\n");
			printf("L2C to L2D: Data\n");
			memcpy(L2Data[address.Index].data, data, 64);
			L2Data[address.Index].tag = address.Tag;
			L2Data[address.Index].valid = 1;
			L2Data[address.Index].dirty = 1;
		}
	}
}
