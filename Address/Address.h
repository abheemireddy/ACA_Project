//
// Created by chad on 6/3/17.
//

#ifndef ACA_PROJECT_ADDRESS_H
#define ACA_PROJECT_ADDRESS_H

#include <uthash_files/include/uthash.h>

typedef struct AddressTag{
    int Tag;
    int Index;
    int Offset;
    int bitStringValue;
    char* bitString;
    UT_hash_handle hh;
} Address;

char* GetChar(char* originalString,int start,int length,char* substring);
int fromBinary(char *s);
Address Constructor_Address(char* bitString);
char *int2bin(int n);
#endif //ACA_PROJECT_ADDRESS_H
