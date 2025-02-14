#include "ultra.h"

#include <stdio.h>

//RULE:
//we will be partitioning the input string into 4 digit chunks converted to int
//we will be storing the 4 digit chunks in a linked list
//then we will perform the subtraction operation on corresponding chunks

// void printnumStr(ultraInt * num){ //ultraInt_toString not working yet
//     char * str = ultraInt_toString(num);
//     printf("%s\n", str);
// }

void freeUltraInt(ultraInt * num){
    ultraInt * temp = num;
    while (temp != NULL){
        ultraInt * temp2 = temp;
        temp = temp->prev;
        free(temp2);
    }
}

void printNum(ultraInt * num){
    ultraInt * temp = num;
    // printf("printing num\n");
    while (temp != NULL){
        printf("%d\n", temp->num);
        temp = temp->prev;
    }
}

int chunktoInt(char * str){
    int num = 0;
    while (*str != '\0'){
        num = num * 10 + (*str - '0');
        str++;
    }    
    return num;
}

char * inttoChunk(int num){
    char * str = (char *)malloc(4* sizeof(char));
    int i = 3;
    for (; i >= 0; i--){
        str[i] = num % 10 + '0';
        num = num / 10;
    }
    //fill the rest with 0
    for (;i >= 0; i--){
        str[i] = '0';
    }
    return str;
}

char * lastInttoChunk(int num){
    char * str = (char *)malloc(4* sizeof(char));
    if (num < 0){
        num *= -1;
    } 
    char* tempStr = inttoChunk(num);
    for (int i = 0; i < 4; i++){
        str[i] = tempStr[i];
    }
    return str;
}

char * ultraInt_toString(ultraInt * _uInt){
    //special case if the number is 0
    if(_uInt->num == 0 && _uInt->prev == NULL){
        char * str = (char *)malloc(2);
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    int blocks = 0;
    ultraInt * tempUInt = _uInt;
    while(tempUInt->prev != NULL){
        blocks++;
        tempUInt = tempUInt->prev;
    }
    int isNeg = 0;
    if(tempUInt->num < 0){
        isNeg = 1;
    }
    blocks++; //for the last block

    int allocatedLen = blocks*4;
    char * str = (char *)malloc(allocatedLen+1+isNeg); //last char for null char //+1 for negative sign
    // printf("Allocated length: %d at %p\n", allocatedLen, str);
    str[allocatedLen+isNeg] = '\0';
    tempUInt = _uInt;
    char * ptrToCurrent = str+(allocatedLen-1+isNeg)-4+1;

    while(tempUInt->prev != NULL){//for all but the last block
        char * tempStr = inttoChunk(tempUInt->num);
        // printf("tempStr %s\n", tempStr);
        for(int i=0; i<4; i++){
            *(ptrToCurrent+i) = tempStr[i];
        }
        ptrToCurrent -= 4;
        tempUInt = tempUInt->prev;
    }
    //for the last block
    char * tempStr = lastInttoChunk(tempUInt->num);
    // printf("tempStr %s\n", tempStr);
    for(int i=0; i<4; i++){
        *(ptrToCurrent+i) = tempStr[i];
    }
    // printf("String: %s\n", ptrToCurrent);
    int count_zero = 0;
    for (int i = 0; i < allocatedLen; i++){
        if(ptrToCurrent[i] == '0'){
            count_zero++;
        } else{
            break;
        }
    }
    // printf("count_zero %d\n", count_zero);
    char * finalStr = (char *)malloc(allocatedLen+1+isNeg-count_zero);
    // printf("final len %d\n", allocatedLen+1+isNeg-count_zero);
    finalStr[allocatedLen+isNeg-count_zero] = '\0';
    if(isNeg){
        finalStr[0] = '-';
    }
    for (int i = 0; i < allocatedLen-count_zero; i++){
        finalStr[i+isNeg] = ptrToCurrent[i+count_zero];
    }
    // printf("Final String: %s\n", finalStr);
    free(str);
    return finalStr;
}

ultraInt * string_toUltraInt(char * str, int len) //len is the length of the string
{   
    // printf("Num received %s\n", str);
    // printf("len received %d\n", len);
    int isNeg = 0;
    if(str[0] == '-'){
        isNeg = 1;
        len--; //for the negative sign
        str++;
    }
    //calculation if index for last full size chunk
    int lastChunkId = len % 4 - 1;

    // ultraInt num = {0, NULL};
    ultraInt * numPtr = (ultraInt *)malloc(sizeof(ultraInt));
    // ultraInt passingNum = num;
    ultraInt * passingNumPtr = numPtr;

    // printf("%p\n", passingNumPtr);


    for (int i = len; i > lastChunkId+1; ){
        // printf("passed ptr %p\n", passingNumPtr);

        i-=4;

        char * tempStr = (char *)malloc(5);
        for (int j = 0; j < 4; j++){
            tempStr[j] = str[i+j];
        }
        tempStr[4] = '\0';
        int _no = chunktoInt(tempStr);
        //storing data in linked list elem
        passingNumPtr-> num = _no;


        //preparing next elem str
        ultraInt * tempUInt_ = (ultraInt *)malloc(sizeof(ultraInt));
        passingNumPtr->prev = tempUInt_;
        ultraInt tempUInt = {0, NULL};
        // printf("new temp ptr %p\n", tempUInt_);
        passingNumPtr = passingNumPtr->prev;
        // printf("new passed ptr %p\n", passingNumPtr);
        // printf("current chunk number %d\n", _no);
        // printf("passingNumPtr %p\n", passingNumPtr);

        
    }
    passingNumPtr->prev = NULL; //for the last elem

    //for rest of the string, 0 to lastChunkId
    if(lastChunkId != -1)
    {
    char * tempStr = (char *)malloc(lastChunkId+2);
    for (int j = 0; j < lastChunkId+1; j++){
        tempStr[j] = str[j];
    }
    tempStr[lastChunkId+1] = '\0';
    int _no = chunktoInt(tempStr);
    //storing data in linked list elem
    passingNumPtr-> num = _no;
    // printf("%p\n", passingNumPtr);
    // printf("current chunk number %d\n", _no);
    passingNumPtr->prev = NULL; //for the last elem
    // free(tempStr);
    } else {
        ultraInt * tempUInt_ = numPtr;
        while(tempUInt_->prev->prev != NULL){
            tempUInt_ = tempUInt_->prev;
        }
        free(tempUInt_->prev);
        tempUInt_->prev = NULL; 
        passingNumPtr = tempUInt_;       
    }
    if(isNeg){
        passingNumPtr->num *= -1;
    }
    // printf("passingNumPtr %p\n", passingNumPtr);

    return numPtr;
}

ultraInt * ultraInt_sub(ultraInt * num1, int len1, ultraInt * num2, int len2){
    
    //TODO: implement subtraction for +ve/-ve , -ve/+ve, -ve/-ve



    int isNeg = 0; //for result

    ultraInt * result = (ultraInt *)malloc(sizeof(ultraInt));
    ultraInt * resultPtr = result;

    int blocks1 = len1 / 4 + (len1 % 4 != 0)*1;
    int blocks2 = len2 / 4 + (len2 % 4 != 0)*1;

    int carry = 0;

    if(num1 == NULL || num2 == NULL){
        return NULL;
    }

    //make same number of blocks
    int maxblocks = blocks1 > blocks2 ? blocks1 : blocks2;

    ultraInt * tempPtr1 = num1;
    ultraInt * tempPtr2 = num2;

    for (int i = 0; i < maxblocks-1 ; i++){
        if(tempPtr1->prev == NULL){
            ultraInt * tempUInt1 = (ultraInt *)malloc(sizeof(ultraInt));
            tempUInt1->num = 0;
            tempUInt1->prev = NULL;
            tempPtr1->prev = tempUInt1;
            tempPtr1 = tempPtr1->prev;
            tempPtr2 = tempPtr2->prev;  
            // printnumStr(num1);
            // printnumStr(num2);

            continue;       
        }
        if(tempPtr2->prev == NULL){
            ultraInt * tempUInt2 = (ultraInt *)malloc(sizeof(ultraInt));
            tempUInt2->num = 0;
            tempUInt2->prev = NULL;
            tempPtr2->prev = tempUInt2;
            tempPtr1 = tempPtr1->prev;
            tempPtr2 = tempPtr2->prev;


            continue;           
        }
        tempPtr1 = tempPtr1->prev;
        tempPtr2 = tempPtr2->prev;
    }

    // printf("CHECK\n");
    

    while(1){
        // printf("Ptr received %p\n", resultPtr);
        int temp = num1->num - num2->num - carry;
        // printf("num1 %d\n", num1->num);
        // printf("num2 %d\n", num2->num);
        // printf("temp %d\n", temp);
        if(temp < 0){
            temp += 10000;
            carry = 1;
        }
        else{
            carry = 0;
        }
        resultPtr->num = temp;
        if(num1->prev == NULL || num2->prev == NULL){
            resultPtr->prev = NULL;
            if(num1->num - num2->num - carry < 0){
                isNeg = 1;
            }
            break;
        }
        ultraInt * tempUInt = (ultraInt *)malloc(sizeof(ultraInt));
        resultPtr->prev = tempUInt;
        resultPtr = resultPtr->prev;
        num1 = num1->prev;
        num2 = num2->prev;

    }

    // printf("Result\n");
    // printNum(result);

    if(isNeg){
        // printf("Negative result\n");

        //make ultraInt of 1 followed by len1 number of 0s
        char * tempStr = (char *)malloc(maxblocks*4+1); 
        tempStr[0] = '1';
        for (int i = 1; i <= maxblocks*4; i++){
            tempStr[i] = '0';
        }
        // printf("tempStr %s\n", tempStr);
        ultraInt * tempUInt = string_toUltraInt(tempStr, maxblocks*4+1);
        result = ultraInt_sub(tempUInt, maxblocks*4+1, result, maxblocks*4); 
        free(tempStr);       
    }
    int noZeroAtEnd = 0;
    int setNeg = isNeg? 0 : 1;
    while(1){
        // printf("CHECK\n");
        if(setNeg == 1 && noZeroAtEnd == 1){
            break;
        }
        if(noZeroAtEnd==0){
            // printf("zero at end\n");
            ultraInt * tempUInt = result;
            
            if(tempUInt->prev != NULL)
            {while(tempUInt->prev->prev != NULL){
                tempUInt = tempUInt->prev;
            }
            if(tempUInt->prev->num == 0){
                free(tempUInt->prev);
                tempUInt->prev = NULL;
                // printf("removed zero at end\n");
                // printNum(result);
            } 
            else{
                // printf("No Zero at end1\n");
                noZeroAtEnd = 1;
            }}
            else{
                noZeroAtEnd = 1;
            }
        }
        if(noZeroAtEnd == 1){
            // printf("no zero at end2\n");
            if(isNeg){
                // printf("isNeg\n");
                ultraInt * tempUInt = result;
                while(tempUInt->prev != NULL){
                    tempUInt = tempUInt->prev;
                }
                tempUInt->num *= -1;
                setNeg = 1;
                // printf("setNeg\n");

        }
    }
    }
    

    // printf("result at  %p\n", result);

    return result;
}

ultraInt * ultraInt_add(ultraInt * num1, int len1, ultraInt * num2, int len2){
    
    ultraInt * result = (ultraInt *)malloc(sizeof(ultraInt));
    ultraInt * resultPtr = result;

    int blocks1 = len1 / 4 + (len1 % 4 != 0)*1;
    int blocks2 = len2 / 4 + (len2 % 4 != 0)*1;
    // printf("len1 %d\n", len1);
    // printf("len2 %d\n", len2);
    // printf("blocks1 %d\n", blocks1);
    // printf("blocks2 %d\n", blocks2);

    int carry = 0;

    if(num1 == NULL || num2 == NULL){
        return NULL;
    }

    //make same number of blocks
    int maxblocks = blocks1 > blocks2 ? blocks1 : blocks2;
    
    ultraInt * tempPtr1 = num1;
    ultraInt * tempPtr2 = num2;

    for(maxblocks; maxblocks>0; maxblocks--){
        // printf("maxblocks %d\n", maxblocks);

        int tempN1=0, tempN2=0;
        if(tempPtr1 != NULL){
            tempN1 = tempPtr1->num;
            // printf("tempN1 %d\n", tempN1);
            tempPtr1 = tempPtr1->prev;
        }
        if(tempPtr2 != NULL){
            tempN2 = tempPtr2->num;
            // printf("tempN2 %d\n", tempN2);
            tempPtr2 = tempPtr2->prev;
        }
        // printf("carry %d\n", carry);
        int temp = tempN1 + tempN2 + carry;
        carry = temp / 10000;
        temp = temp % 10000;
        resultPtr->num = temp;
        if(tempPtr1 == NULL && tempPtr2 == NULL){
            // printf("both block last together\n");
            if(carry != 0){
                // printf("Carry not zero\n");
                ultraInt * tempUInt = (ultraInt *)malloc(sizeof(ultraInt));
                tempUInt->num = carry;
                resultPtr->prev = tempUInt;
                resultPtr = resultPtr->prev;
            }
            break;
        }
        ultraInt * tempUInt = (ultraInt *)malloc(sizeof(ultraInt));
        resultPtr->prev = tempUInt;
        resultPtr = resultPtr->prev;
    }
    resultPtr->prev = NULL;

    // printNum(result);

    return result;
}

ultraInt * UltraSub(ultraInt * _num1, int len1, ultraInt * _num2, int len2){
    //Wrapper function for ultraInt_sub
    int num1Neg = 0;
    int num2Neg = 0;

    // printf("Num 1________\n");
    // printNum(num1);
    // printf("Num 2________\n");
    // printNum(num2);

    //copy the numbers
    ultraInt * num1 = (ultraInt *)malloc(sizeof(ultraInt));
    ultraInt * num2 = (ultraInt *)malloc(sizeof(ultraInt));
    {
        // printf("Copying numbers\n");
        ultraInt * tempCopy_1 = num1;
        ultraInt * tempCopy_2 = num2;
        while (_num1->prev != NULL){
            tempCopy_1->num = _num1->num;
            ultraInt * tempUInt = (ultraInt *)malloc(sizeof(ultraInt));
            tempCopy_1->prev = tempUInt;
            tempCopy_1 = tempCopy_1->prev;
            _num1 = _num1->prev;
        }
        tempCopy_1->num = _num1->num;
        tempCopy_1->prev = NULL;
        while (_num2->prev != NULL){
            tempCopy_2->num = _num2->num;
            ultraInt * tempUInt = (ultraInt *)malloc(sizeof(ultraInt));
            tempCopy_2->prev = tempUInt;
            tempCopy_2 = tempCopy_2->prev;
            _num2 = _num2->prev;
        }
        tempCopy_2->num = _num2->num;
        tempCopy_2->prev = NULL;
        // printf("Copied numbers\n");
    }
    
    ultraInt * tempUInt1ForNeg = num1;
    ultraInt * tempUInt2ForNeg = num2;
    while(tempUInt1ForNeg->prev != NULL){
        tempUInt1ForNeg = tempUInt1ForNeg->prev;
    }
    while(tempUInt2ForNeg->prev != NULL){
        tempUInt2ForNeg = tempUInt2ForNeg->prev;
    }
    if(tempUInt1ForNeg->num < 0){
        num1Neg = 1;
        tempUInt1ForNeg->num *= -1;
    }
    if(tempUInt2ForNeg->num < 0){
        num2Neg = 1;
        tempUInt2ForNeg->num *= -1;
    }

    //printing the numbers
    // printf("Printing numbers\n");

    // printf("Num 1________\n");
    // printNum(num1);
    // printf("Num 2________\n");
    // printNum(num2);

    //We here keep track of the sign of the result, and make the numbers positive
    //+ve/+ve
    ultraInt * result = NULL;

    if(num1Neg == 0 && num2Neg == 0){
        result = ultraInt_sub(num1, len1, num2, len2);
    }

    //-ve/-ve
    else if(num1Neg == 1 && num2Neg == 1){
        result = ultraInt_sub(num1, len1, num2, len2);
        ultraInt * tempUInt = result;
        while(tempUInt->prev != NULL){
            tempUInt = tempUInt->prev;
        }
        tempUInt->num *= -1;
        //make the changed numbers negative again
        tempUInt1ForNeg->num *= -1;
        tempUInt2ForNeg->num *= -1;
    }

    //+ve/-ve
    else if(num1Neg == 0 && num2Neg == 1){
        
        result = ultraInt_add(num1, len1, num2, len2);
        //make the changed numbers negative again
        tempUInt2ForNeg->num *= -1;
    }

    //-ve/+ve
    else if(num1Neg == 1 && num2Neg == 0){
        result = ultraInt_add(num1, len1, num2, len2);
        ultraInt * tempUInt = result;
        while(tempUInt->prev != NULL){
            tempUInt = tempUInt->prev;
        }
        tempUInt->num *= -1;
        //make the changed numbers negative again
        tempUInt1ForNeg->num *= -1;
    }
    //free the copied numbers
    freeUltraInt(num1);
    freeUltraInt(num2);

    return result;

}

int count_pairs(void * arr, char* targetStr, int numsLen){




    int targetLen = 0;
    for (targetLen = 0; targetStr[targetLen]!= '\0'; targetLen++);
    if(targetStr[targetLen-1] == '\n'){
        targetLen--;
    }
    // printf("targetLen %d\n", targetLen);
    // printf("targetStr %s\n", targetStr);
    ultraInt * target = string_toUltraInt(targetStr, targetLen);
    // printf("Target num:");
    // printNum(target);
    // printf("____________________\n");
    char ** ptrToNums = (char **)arr;
    int count = 0;
    int flag;

    int targetneg = 0;
    if(targetStr[0] == '-'){
        targetneg = 1;
    }
    // printf("targetStr %s\n", targetStr);
    // printf("targetneg %d\n", targetneg);

    //make id tuples for each string
    idTuple ** idTuples = (idTuple **)malloc(numsLen*sizeof(idTuple *));
    for(int i = 0; i < numsLen; i++){
        idTuples[i] = (idTuple *)malloc(sizeof(idTuple));
        idTuples[i]->numStr = ptrToNums[i];
        idTuples[i]->id = i;
    }

    //mergesort the strings
    idTuple ** sortedNums = mergeSort(idTuples, numsLen);
    



     
    //calculate the length of each string and store it in the idTuple's numStrLen field
    for(int i = 0; i < numsLen; i++){
        // printf("numStr: %s\n", sortedNums[i]->numStr);
        int len = 0;
        //length of each sortedNums[i]->numStr
        for (len = 0; sortedNums[i]->numStr[len]!= '\0'; len++);
        if(sortedNums[i]->numStr[len-1] == '\n'){
            len--;
        }
        if(sortedNums[i]->numStr[len-1] == '\0'){
            len--;
        }
        // if(sortedNums[i]->numStr[0] == '-'){
        //     len--;
        // }
        sortedNums[i]->numStrLen = len;
        // printf("  len: %d\n", sortedNums[i]->numStrLen);
    }



    //we need to find num1 and num2 such that num1 - num2 = target where num2 has higher id than num1
    //num1 - num2 = target => num1 -target = num2
    //we will iterate through ptrToNums and for each num1, and do binary search for num1-target


    for (int i = 0; i < numsLen; i++){
        int len1 = 0, len2 = 0;
        for (len1 = 0; ptrToNums[i][len1]!= '\0'; len1++){
            // printf("len1: %d   %c\n", len1, ptrToNums[i][len1]);
        }
        if(ptrToNums[i][len1-1] == '\n'){
            len1--;
        }
        ultraInt * num1 = string_toUltraInt(ptrToNums[i], len1);

        ultraInt * numToFind = UltraSub(num1, len1, target, targetLen);
        char * numToFindStr = ultraInt_toString(numToFind);


        int len = 0;
        for (len = 0; numToFindStr[len]!= '\0'; len++);
        if(numToFindStr[len-1] == '\n'){
            len--;
        }
        if(numToFindStr[len-1] == '\0'){
            len--;
        }
        if(numToFindStr[0] == '-'){
            len--;
        }
        // printf("len of num to find: %d\n", len);
        int numToFindLen = 0;
        for (numToFindLen = 0; numToFindStr[numToFindLen]!= '\0'; numToFindLen++);
        // printf("____________________\n");
        int count_i = indexCount(numToFindStr,numToFindLen, sortedNums, numsLen, i);
        count += count_i;

        //free the num1 and numToFind
        freeUltraInt(num1);
        freeUltraInt(numToFind);

        // printf("Target num:");
        // printNum(target);
        // TEST____________________
        // if (1){
        //     printf("num1 %s , len : %d\n", ptrToNums[i], len1);
        //     printf("target/num2 %s , len : %d\n", ultraInt_toString(target), targetLen);
        //     // printNum(string_toUltraInt(targetStr, targetLen));
        //     // printf("numtofind ");
        //     // printNum(numToFind);
        //     printf("numToFindStr: %s\n", numToFindStr);
        //     printf("count_i :  %d\n\n", count_i);
        // printf("____________________\n");

        // }
    }

    //free the sortedNums
    for(int i = 0; i < numsLen; i++){
        free(sortedNums[i]);
    }

    // //free idTuples, the contents of idTuples are already freed in mergeSort
    free(idTuples);


    return count;
}

int indexCount(char * numstr,int numstrlen, idTuple ** nums, int numsLen, int idOfNumstr){

    // printf("numstr %s\n", numstr);



    //passing sorted nums into this function
    int count = 0;
    int * ids = binarySearch(numstr,numstrlen, nums, numsLen);
    //ids[0] = index of the numstr in nums passed here, ids[1] = original id in the numbers

    if(ids[0] == -1){
        // printf("Numstr %s not found\n", numstr);
        return 0;
    }
    if(idOfNumstr < ids[1]){
        count++;
        // printf("Numstr id %d\n", idOfNumstr);
    }
    // printf("Numstr id %d\n", idOfNumstr);
    // printf("initial id %d\n", nums[ids[0]]->id);
    //see if there are more than one occurence of numstr, search in both directions
    int i = ids[0]-1;
    while(i >= 0){
        // printf("Mark9017\n");
        int currentnumstrlen = nums[i]->numStrLen;
        
        // printf("Current numstr len %d\n", currentnumstrlen);
        if(ultraInt_StrCmp(numstr, numstrlen, nums[i]->numStr, currentnumstrlen) == 0){
            // printf("Matchs are %s and %s\n", numstr, nums[i]->numStr);
            if(idOfNumstr < nums[i]->id){
                count++;
            }
            i--;
        } else{
            break;
        }
    }
    i = ids[0]+1;
    while(i < numsLen){
        int currentnumstrlen = nums[i]->numStrLen;
        // printf("Mark9017\n");
        if(ultraInt_StrCmp(numstr, numstrlen, nums[i]->numStr, currentnumstrlen) == 0){
            // printf("Matchs are %s and %s\n", numstr, nums[i]->numStr);
            if(idOfNumstr < nums[i]->id){
                // printf("%d\n", nums[i]->id);
                count++;
            }
            i++;
        } else{
            break;
        }
    }
    // printf("count %d\n", count);
    free(ids);
    return count;

}

int * binarySearch(char * numstr ,int numstrlen, idTuple ** nums, int numsLen){
    // printf("Bin search Start\n");


    //do iterative binary search for numstr in nums, return the index
    int low = 0;
    int high = numsLen - 1;
    int len1 = numstrlen;
    int * retVals = (int *)malloc(2*sizeof(int ));


    // printf("len1 %d\n", len1);
    while(low <= high){
        // printf("low %d high %d\n", low, high);

        
        // printf("len2 in bin search %d\n", len2);
        int mid = low + (high - low)/2;
        int len2 = nums[mid]->numStrLen;

        // printf("Mark9017bin\n");
        // printf("len1_bin %d\n", len1);
        // printf("len2_bin %d\n", len2);

        int result = ultraInt_StrCmp(numstr, len1, nums[mid]->numStr, len2);
        // printf("Compared %s and %s\n", numstr, nums[mid]->numStr);
        // printf("Compared %s and %s\n", numstr, nums[mid]->numStr);
        //result = 1 if numstr > nums[mid]
        //result = 0 if numstr == nums[mid]
        //result = -1 if numstr < nums[mid]
        if(result == 0){
            // printf("Match found\n");
            retVals[0] = mid;
            retVals[1] = nums[mid]->id;
            return retVals;

            
        }
        if(result == 1){
            low = mid + 1;
        } else{
            high = mid - 1;
        }
    }
    retVals[0] = -1;
    retVals[1] = -1;

    // printf("Bin search End\n");
    return retVals;
}

int ultraInt_StrCmp(char * str1, int len1, char * str2, int len2){
    // compare two ultraInt numbers
    // return 1 if num1 > num2
    // return 0 if num1 == num2
    // return -1 if num1 < num2
    // printf("Comparing %s and %s _________\n", str1, str2);
    // printf("Len1 %d\n", len1);
    // printf("Len2 %d\n", len2);
    // printf("__________________________\n");
    int n1neg = 0, n2neg = 0; //1 if negative
    if(str1[0] == '-'){
        n1neg = 1;
        len1--;
        str1++;
    }
    if(str2[0] == '-'){
        n2neg = 1;
        len2--;
        str2++;
    }

    if(n1neg == 0 && n2neg == 1){
        return 1;
    }
    if(n1neg == 1 && n2neg == 0){
        return -1;
    }
    if(n1neg == 1 && n2neg == 1){
        return -1 * ultraInt_StrCmp(str1, len1, str2, len2);
    }


    // if(str1[len1-1] == '\n'|| str1[len1-1] == '\0'){
    //     printf("removing newline\n");
    //     len1--;
    // }
    // if(str2[len2-1] == '\n'|| str2[len2-1] == '\0'){
    //     printf("removing newline\n");
    //     len2--;
    // }
    //now only case left is both +ve
    if(len1 > len2){
        return 1;
    } else if (len1 < len2){
        return -1;
    } else{
        //both have same length
        for (int i = 0; i < len1 && i<len2; i++){
            // printf("Comparing %c and %c\n", str1[i], str2[i]);
            if(str1[i] > str2[i]){
                // printf("Did not match at %d for %s and %s\n", i, str1[i], str2[i]);
                return 1;
            } else if (str1[i] < str2[i]){
                // printf("Did not match at %d for %s and %s\n", i, str1[i], str2[i]);
                return -1;
            }
        }
    }
    return 0;

}

idTuple ** merge(idTuple ** arr1, int len1, idTuple ** arr2, int len2){

    idTuple ** merged = (idTuple **)malloc((len1+len2)*sizeof(idTuple *));
    //freed in next merging //last one is freed in freeing sortedNums
    //use ultraInt_StrCmp to compare the strings
    int i = 0, j = 0, k = 0;
    while(i < len1 && j < len2){
        int strlen1 = 0, strlen2 = 0;
        while(1){
            if(arr1[i]->numStr[strlen1] == '\0' || arr1[i]->numStr[strlen1] == '\n'){
                break;
            }
            strlen1++;
        }
        while(1){
            if(arr2[j]->numStr[strlen2] == '\0' || arr2[j]->numStr[strlen2] == '\n'){
                break;
            }
            strlen2++;
        }
        if(ultraInt_StrCmp(arr1[i]->numStr, strlen1, arr2[j]->numStr, strlen2) == -1){
            merged[k] = arr1[i];
            i++;
        } else{
            merged[k] = arr2[j];
            j++;
        }
        k++;
    }
    while(i < len1){
        merged[k] = arr1[i];
        i++;
        k++;
    }
    while(j < len2){
        merged[k] = arr2[j];
        j++;
        k++;
    }
    //free the memory of arr1 and arr2
    free(arr1);
    free(arr2);


    return merged;
}

idTuple ** mergeSort(idTuple ** arr, int len){
    if(len == 1){
        return arr;
    }
    int mid = len/2;
    idTuple ** arr1 = (idTuple **)malloc(mid*sizeof(idTuple *)); //freed in merge
    idTuple ** arr2 = (idTuple **)malloc((len-mid)*sizeof(idTuple *)); //freed in merge
    for (int i = 0; i < mid; i++){
        arr1[i] = arr[i];
    }
    for (int i = mid; i < len; i++){
        arr2[i-mid] = arr[i];
    }
    arr1 = mergeSort(arr1, mid);
    arr2 = mergeSort(arr2, len-mid);




    return merge(arr1, mid, arr2, len-mid);
}