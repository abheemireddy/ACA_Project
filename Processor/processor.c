#include "processor.h"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>


void run_processor()
{
	initL1Data();  // init cache data
	initL2Data();  // init cache data
    initL2Controller(); // init L2 controller

	char cwd[1024];
	if(getcwd(cwd,sizeof(cwd)) != NULL){
		fprintf(stdout,"current working dir: %s\n",cwd);
	}


	FILE * f = fopen("input.txt", "r");
	while (!feof(f))
	{
        Address addressStruct;
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
