//
// Created by chad on 6/3/17.
//

#include "Address.h"

char* GetChar(char* originalString,int start,int length){
    char substring[length + 1];
    memcpy( substring, &originalString[start], length );
    substring[length] = '\0';
    return substring;
}

int fromBinary(char *s) {
    return (int) strtol(s, NULL, 2);
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