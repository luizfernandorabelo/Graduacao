#include <stdio.h>
#include <stdlib.h>

#include "numberListAloc.h"
#include "fileManager.h"
#include "stopWatch.h"

void reverseOrder(NUMBER_LIST_DATA *numberList);

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Usage: ./progname numberListSize executionsNumber\n");
        exit(0);
    }

    int numberListSize = atoi(argv[1]), executionsNumber = atoi(argv[2]);

    NUMBER_LIST_DATA *numberList = loadNumberList(numberListSize);

    double averageTime = 0.0;
    for(int i = 0; i < executionsNumber; i++){
        time_t start = clock();
        reverseOrder(numberList);
        time_t end = clock();
        averageTime += getExecutionTime(start, end);
    }
    averageTime /= (double) executionsNumber;

    writeExecutionTimeToTextFile(averageTime, executionsNumber, numberList->size);

    unloadNumberList(numberList);
    
    return(0);
}

void reverseOrder(NUMBER_LIST_DATA *numberList){
    int auxTrade = 0, halfSize = numberList->size / 2;
    for(int i = 0, j = numberList->size -1; i < halfSize; i++, j--){
        auxTrade = numberList->elements[i]; 
        numberList->elements[i] = numberList->elements[j];
        numberList->elements[j] = auxTrade; 
    }
}