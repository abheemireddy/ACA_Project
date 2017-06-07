#include <stdio.h>
#include <string.h>
#include "L1Controller/L1Controller.h"
#include "L2Controller/L2Controller.h"
#include "aca/L1Data.h"
#include "aca/L2Data.h"

int main()
{
	initL1Data();  // init cache data
	initL2Data();  // init cache data
	initL2Controller(); // init L2 controller

	FILE * f = fopen("input.txt", "r");
	while (!feof(f))
	{
		char instruction[100];
		int  address;
		int  value;
		int  operation = -1;  // -1: invalid
		fscanf(f, "%s", instruction);
		if (!strcmp(instruction, "CPUWrite")) // write instruction
		{
			fscanf(f, "%d %d", &address, &value);
			operation = 1;
		}
		else if (!strcmp(instruction, "CPURead")) // read instruction
		{
			fscanf(f, "%d", &address);
			operation = 2;
		}

		if (operation == 1)
		{
			L1_write(address, value);
		}
		else if (operation == 2)
		{
			int value = L1_read(address);
			printf("Result: %d\n", value);
		}
		else
		{
			printf("Invalid operation: %s. Aborting\n", instruction);
			break;
		}
	}
	fclose(f);
}
