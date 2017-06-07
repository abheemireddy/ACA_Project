#include "L1Data.h"

struct CacheBlock L1Data[256];

void initL1Data()
{
	int i;
	for (i = 0; i < 256; i++)
	{
		L1Data[i].valid = 0;
		L1Data[i].dirty = 0;
	}
}
