#include "ultra.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    char * str1 = "50000000";
    char * str2 = "50000000";
    char * target = "-1000000";

    // ultraInt * num1 = (ultraInt *)string_toUltraInt(str1, 8);
    // ultraInt * num2 = (ultraInt *)string_toUltraInt(str2, 8);
    ultraInt * num3 = (ultraInt *)string_toUltraInt(target, 8);
    printNum(num3);

    int l1, l2;
    for (l1 = 0; str1[l1] != '\0'; l1++);
    for (l2 = 0; str2[l2] != '\0'; l2++);
    // printf("Length of str1: %d\n", l1);
    // printf("Length of str2: %d\n", l2);
    ultraInt * num1 = (ultraInt *)string_toUltraInt(str1, l1);
    ultraInt * num2 = (ultraInt *)string_toUltraInt(str2, l2);
    // printf("num1>num2: %d\n", ultraInt_StrCmp(str1, l1, str2, l2));
    // printNum(num1);
    // printNum(num2);
    // ultraInt * num3 = UltraSub(num1, l1, num2, l2);
    // printf("Result addition: \n");
    // printNum(num3);
    int count = 0;
    char ** nums = (char **)malloc(2 * sizeof(char *));
    nums[0] = str1;
    nums[1] = str2;
    // printf("CHECKPOINT\n");
    // count = count_pairs(nums, target, 2);
    // printf("Count [in main]: %d\n", count);
    char ** numsSupply = (char **)malloc(2 * sizeof(char *));
    nums[0] = str1;
    nums[1] = str2;
    printf("%d",count_pairs(nums, target, 2));



    return 0;

}