//
// Created by chad on 6/3/17.
//

#include "Address.h"
#include <stdio.h>

int fromBinary(char bitString[]){//method from https://stackoverflow.com/questions/30696320/how-to-convert-bit-string-into-integer
    int ret = 0;
    for(int i = 0; i < 32; i++)
        if(bitString[i] == '1')
            ret |= 1 << (31-i);

    return ret;
}


char* GetChar(char* originalString,int start,int length){
    char substring[length + 1];
    memcpy( substring, &originalString[start], length );
    substring[length] = '\0';
    return substring;
}

Address Constructor_Address(char* bitString){
    char* TagString = GetChar(bitString,0,8);
    char* IndexString = GetChar(bitString,8,6);
    char* OffsetString = GetChar(bitString,14,3);
    int Tag = fromBinary(TagString);
    int Index = fromBinary(IndexString);
    int Offset = fromBinary(OffsetString);
    Address address = {Tag:Tag,Index:Index,Offset:Offset,bitString:bitString};
    return address;
}