#include <stdio.h>
#include <stdlib.h>

#include "numberListAloc.h"
#include "fileManager.h"
#include "stopWatch.h"


void sort(NUMBER_LIST_DATA *numberList){

    int *elements = numberList->elements;
    int auxTrade = 0;

    for(int i = numberList->size; i >= 0; i--){
        for(int j = 0; j < i; j++){
            int actualNumber = elements[j], successor = elements[j+1]; 
            if(actualNumber > successor){
                elements[j] = successor; 
                elements[j+1] = actualNumber; 
            }
        }
    }
}


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
        sort(numberList);
        time_t end = clock();
        averageTime += getExecutionTime(start, end);
    }
    averageTime /= (double) executionsNumber;

    writeExecutionTimeToTextFile(averageTime, executionsNumber, numberList->size);

    unloadNumberList(numberList);

    return(0);
}