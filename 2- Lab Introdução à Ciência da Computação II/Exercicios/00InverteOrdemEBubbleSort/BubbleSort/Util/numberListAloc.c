#include "numberListAloc.h"

#include <stdlib.h>
#include "fileManager.h"


NUMBER_LIST_DATA *loadNumberList(int listSize){

    NUMBER_LIST_DATA *numberList = malloc(sizeof(NUMBER_LIST_DATA));

    numberList->size = listSize;
    numberList->elements = readNumberListFromBinaryFile(numberList->size);

    return(numberList);
}

void unloadNumberList(NUMBER_LIST_DATA *numberList){

    free(numberList->elements);
    free(numberList);
}