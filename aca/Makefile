processor: processor.c L1Controller.o L1Data.o L2Controller.o L2Data.o MainMemory.o 
	gcc processor.c L1Controller.o L1Data.o L2Controller.o L2Data.o MainMemory.o -o processor.o

L1Controller: L1Controller.c L1Data.o
	gcc L1Controller.c -c -o L1Controller.o

L1Data: L1Data.c
	gcc L1Data.c -c -o L1Data.o

L2Controller: L2Controller.c L2Data.o
	gcc L2Controller.c -c -o L2Controller.o

L2Data: L2Data.c
	gcc L2Data.c -c -o L2Data.o

MainMem: MainMemory.c
	gcc MainMemory.c -c -o MainMemory.o

