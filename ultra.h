#include <stdlib.h>
// #include "ultra.c"

typedef struct ultraInt{
    int num;
    struct ultraInt * prev;
} ultraInt;

typedef struct idTuple{
    char * numStr;
    int numStrLen; // length of numStr without null terminator and \n character ; (-) sign included in length
    int id;
} idTuple;

ultraInt * string_toUltraInt(char * str, int len);
ultraInt * UltraSub(ultraInt * num1, int len1, ultraInt * num2, int len2);
void printNum(ultraInt * num);
int count_pairs(void * arr, char* targetStr, int numsLen);
int ultraInt_StrCmp(char * str1, int len1, char * str2, int len2);
idTuple ** mergeSort(idTuple ** arr, int len);
// ultraInt * ultraInt_sub(ultraInt * num1, int len1, ultraInt * num2, int len2); // private
// ultraInt * ultraInt_add(ultraInt * num1, int len1, ultraInt * num2, int len2); // private
char * ultraInt_toString(ultraInt * _uInt);
int * binarySearch(char * numstr ,int numstrlen, idTuple ** nums, int numsLen);
int indexCount(char * numstr,int numstrlen, idTuple ** nums, int numsLen, int idOfNumstr);
void printNum(ultraInt * num);