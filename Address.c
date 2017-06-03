//
// Created by chad on 6/3/17.
//

#include "Address.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>

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

Address Constructor_Address(char* bitString){
    char* output = malloc(9);
    GetChar(bitString,0,8,output);
    char* TagString = output;
    output = malloc(7);
    GetChar(bitString,8,6,output);
    char* IndexString = output;
    output = malloc(4);
    GetChar(bitString,14,3,output);
    char* OffsetString = output;
    int Tag = fromBinary(TagString);
    int Index = fromBinary(IndexString);
    int Offset = fromBinary(OffsetString);
    Address address = {Tag:Tag,Index:Index,Offset:Offset,bitString:bitString};
    return address;
}