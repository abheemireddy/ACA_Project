***Advanced Computer Architecture Project***
By: Chad Crowe

SOURCE CODE:
https://github.com/cpluspluscrowe/ACA_Project
    Over 280 commits to GitHub for this project.

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

