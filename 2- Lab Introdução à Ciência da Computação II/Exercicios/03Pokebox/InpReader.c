#include "InpReader.h"
#include <stdio.h>

int readNumber(){
    int number = 0;
    scanf("%d", &number);
    return(number);
}

int readOption(void){
    return(readNumber());
}

int readPos(void){
    return(readNumber());
}