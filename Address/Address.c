//
// Created by chad on 6/3/17.
//

#include "Address.h"

int fromBinary(char* bitString){
    char* end;
    int value = strtol(bitString,&end,2);
    return value;
}


char* GetChar(char* originalString,int start,int length,char* substring){
    memcpy( substring, &originalString[start], length );
    substring[length] = '\0';
    return substring;
}

char *int2bin(int n) { //function from quora
    // determine the number of bits needed ("sizeof" returns bytes)
    int nbits = 17;//sizeof(n) * 8;
    char *s = malloc(nbits+1);  // +1 for '\0' terminator
    s[nbits] = '\0';
    // forcing evaluation as an unsigned value prevents complications
    // with negative numbers at the left-most bit
    unsigned int u = *(unsigned int*)&n;
    int i;
    unsigned int mask = 1 << (nbits-1); // fill in values right-to-left
    for (i = 0; i < nbits; i++, mask >>= 1)
        s[i] = ((u & mask) != 0) + '0';
    return s;
}

Address* Constructor_Address(char* bitString){
    char* output = malloc(7);
    GetChar(bitString,0,6,output);
    char* TagString = output;
    output = malloc(9);
    GetChar(bitString,6,8,output);
    char* IndexString = output;
    output = malloc(4);
    GetChar(bitString,14,3,output);
    char* OffsetString = output;
    int Tag = fromBinary(TagString);
    int Index = fromBinary(IndexString);
    int Offset = fromBinary(OffsetString);
    int bitStringValue = fromBinary(bitString);

    Address* address = malloc(sizeof(Address));
    address->Tag = Tag;
    address->Index = Index;
    address->Offset = Offset;
    strcpy(address->bitString,bitString);
    address->bitStringValue = bitStringValue;
    address->StartOfBlockBitStringValue = address->bitStringValue - address->Offset;
    return address;
}