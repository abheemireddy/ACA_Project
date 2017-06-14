***Advanced Computer Architecture Project***
By: Chad Crowe

MAKING THE EXECUTABLE:
Project was created using CMAKE
1. cd to directory ACA_Project
2. Run "cmake ."
        This will create the makefile
3. Run make
4. The executable will be ACA_Project and will take input.txt, in the ACA_Directory as input

STRUCTURE OF CONTROLLERS:
Each controller has an instruction queue, blocks from bus to be written queue, and then the necessary victim/buffer caches.
The controller checks the blocks from the bus queue.  If enough time has passed, the block dequeues from the bus and writes onto its cache.
The controller then continually reads from its instruction queue and processes it until it is forced to idle.

STRUCTURE OF THE BUSES:
Data and its corresponding block are moved onto the bus.  A clock cycle when this data will be available is specified.
All of the block's cacheLines contain an integer referring to where the data is on this char array.
When the block is taken off the bus, the char array is transferred to the cache's data and the cacheLine's indexes are changed to the new address

ADDRESS CHANGES:
All data structures contain information about the structure's address.
This address is adjusted at L2's controller to adjust for the change in Tag/Index/Offset.  This ensures that the block's are stored in the correct set.

EXPECTED BEHAVIOR OF COMPONENTS:
Processor reads from input.txt
Processor loads instructions onto a processor queue
Clock Cycles begin
L1 reads from processor queue onto an l1 instruction queue until l1 is forced to idle
L1 reads from its instruction queue and processes it.
    Data might be written/read at the Cacheline level and returned to the processor
    Anytime data is moved from the cache onto the buffer, the cache is sorted by LFU and the least frequently used item is moved in the buffer.
    Otherwise the instruction is loaded onto the L2 instruction Queue
L2 reads from its Bus Queue and processes any data that has been fully transferred
    If Set or Buffer contains too many items, L2 block is removed and L1 is searched.  If the block is found in L1, that L1 block is also evicted from L1 and put on Memory's Bus line
L2 reads from its instruction queue and processes it
    If the block is found, the data and the block are loaded onto a Bus for L1
    If the block is not found, the instruction is loaded onto Memory's instruction Queue
Memory reads from its Bus Queue and processes any data that has been fully transferred
Memory reads from its instruction Queue and processes it
    If the block is not found, a block/CacheLine are created and stored into Memory.  This is then transferred onto L2's Bus
Clock cycle count is incremented.
The loop continues until all instruction Queues are empty, i.e. all instructions are processed.

SOURCE CODE:
https://github.com/cpluspluscrowe/ACA_Project
    300+ commits to GitHub for this project

TESTS/TEST EXECUTION TRACES AND OUTPUTS
in folder:Tests
    Contains input and output files

COMPONENTS:
Processor
L1 & L2 Cache Controller: Controller folder
Memory: in DRAM folder
Write buffers & Victim Caches for L1 & L2: in Buffers folder

OTHER COMPONENTS:
Address: Contains block address functions
Block: Contains Block data
Block_Queue: Queue for transferring data between levels
BlockOnBus: Structure for Block_Queue
BlockTransferer: Queue that each level reads from to obtain the next instruction
Cache: Contains Cache data
CacheLine: How data is stored within blocks
Instruction: Read/Write instruction struct for transferring between levels
Queue: Queue for transferrign instructions between levels
Set: Contains set information
Data_Structure_Examples: Individual tests that use the data structures
utHash: This is a HashTable I used for storing components

