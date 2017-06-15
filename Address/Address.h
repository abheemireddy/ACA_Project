//
// Created by chad on 6/3/17.
//

#ifndef ACA_PROJECT_ADDRESS_H
#define ACA_PROJECT_ADDRESS_H

#include "uthash_files/include/uthash.h"

typedef struct AddressTag{
    int Tag;
    int Index;
    int Offset;
    int bitStringValue;
    int StartOfBlockBitStringValue;
    char bitString[18];
    UT_hash_handle hh;

} Address;

Address* Constructor_Address(char bitString[18]);
Address* Constructor_AddressConvertForL2(char bitString[18]);

char* GetChar(char originalString[18],int start,int length,char* substring);
int fromBinary(char *s);
char *int2bin(int n);
#endif //ACA_PROJECT_ADDRESS_H
