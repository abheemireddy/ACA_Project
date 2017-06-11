#include "L1Controller.h"
#include "Global_Variables.h"

L1Controller* Constructor_L1Controller(){
    L1Controller* l1Controller = malloc(sizeof(l1Controller));
    l1Controller->cache = Constructor_Cache(64);
    l1Controller->transferer = Constructor_Transferer();
    l1Controller->waiting = false;
    l1Controller->dataFromL2 = NULL;
    return l1Controller;
}

void SetL1ControllerData(){
    Block* toStore = l1Controller->dataFromL2;
    Set* set = l1Controller->cache->getSetByIndex(&l1Controller->cache->HashTable,toStore->address.Index);
    Block* existing = get(&set->HashTable,toStore->address.Tag);
    if(existing != NULL){
        if(existing->dirtyBit == false){
            if(CountBlocksInBuffer(&l1VictimCache->HashTable) >= 2){
                //l1VictimCache->
            }
            l1VictimCache->putBlock(&l1VictimCache->HashTable,existing);
        }
    }
    put(&set->HashTable,toStore);
    //L1ProcessInstruction(nextInstructionForL1ControllerToProcess);
}

void L1ProcessInstruction(Instruction instruction){
    if(instruction.instruction == 1){
        L1_write(instruction,instruction.data);
    }else if(instruction.instruction == 2){
        L1_read(instruction);
    }
}

void L1_write(Instruction instruction, char value[64])
{
	/*printf("P to L1C: CPUWrite (%d)\n", address.bitStringValue);
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

	}*/
}

CacheLine* L1_read(Instruction instruction)
{
    Set* set = getSetByIndex(&l1Controller->cache->HashTable,instruction.address.Index);
    Block* block = get(&set->HashTable,instruction.address.Tag);
    if(block != NULL){
        if(block->validBit == true){
            CacheLine* cacheLine = getCacheLineByOffset(&block->HashTable,instruction.address.Offset);
            return cacheLine;
        }else{
            block = NULL;
        }
    }
	if (block == NULL)
	{
        //check victim and write buffer
        Enqueue(l2Controller->transferer->TransferQueue,instruction);
		//l2Read(instruction.address, L1Data[instruction.address.Index].data);  // get data from L2
		l1Controller->waiting = true;
		return NULL;
	}
    /*
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

	}*/

	return NULL;
}
