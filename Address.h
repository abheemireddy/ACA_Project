//
// Created by chad on 6/3/17.
//

#ifndef ACA_PROJECT_ADDRESS_H
#define ACA_PROJECT_ADDRESS_H

#include <uthash/include/uthash.h>

typedef struct AddressTag{
    int Tag;
    int Index;
    int Offset;
    char* bitString;
    UT_hash_handle hh;
} Address;

char* GetChar(char* originalString,int start,int length);
int fromBinary(char *s);
Address Constructor_Address(char* bitString);

#endif //ACA_PROJECT_ADDRESS_H
