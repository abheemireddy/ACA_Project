#include "L2Data.h"

struct Cache2Block L2Data[512];

void initL2Data()
{
	int i;
	for (i = 0; i < 512; i++)
	{
		L2Data[i].valid = 0;
		L2Data[i].dirty = 0;
	}
}
