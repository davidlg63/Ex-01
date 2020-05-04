//
// Created by X on 03/05/2020.
//
#include <string.h>
#define ERROE_MESSEGE -1
#define BASE 10




int powerOfNumber(int base, int exponent){ // only for natural exponents(including 0)
    if(exponent<0)
    {
        return ERROE_MESSEGE;
    }
    if (exponent==0)
    {
        return 1;
    }
    int sum=1;
    while (exponent!=0)
    {
        exponent--;
        sum*=base;
    }
    return sum;
}

int stringToInt(char* num_str){
    char* end_of_str="";
    if(strcmp(num_str,end_of_str)==0)
    {
        return ERROE_MESSEGE;
    }
    int sum=0;
    int length=strlen(num_str);
    for (int i=0;i<strlen(num_str);i++){
        int digit=num_str[length-i-1]-'0';
        if(digit<0 || digit>9)
        {
            return  ERROE_MESSEGE;
        }
        sum+=digit*powerOfNumber(BASE,i);
    }
    return sum;
}

