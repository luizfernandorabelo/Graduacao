#include "numberArrayAloc.h"

#include <stdio.h>
#include <stdlib.h>
#include "myNumber.h"

int *readNumberArrayElements(int numberArraySize){
    int *elements = malloc(numberArraySize * sizeof(int));
    for(int i = 0; i < numberArraySize; i++)    
        elements[i] = readInteger(stdin);
    return elements;
}

NUMBER_ARRAY *loadNumberArray(int registerNumber){
    NUMBER_ARRAY *numberArray = malloc(sizeof(NUMBER_ARRAY));
    numberArray->size = registerNumber;
    numberArray->elements = readNumberArrayElements(numberArray->size);
    return numberArray;
}

void unloadNumberArray(NUMBER_ARRAY *numberArray){
    free(numberArray->elements);
    free(numberArray);
}