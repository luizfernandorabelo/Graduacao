#include "mySearch.h"


int sequentialSearch(NUMBER_ARRAY *numberArray, int key){

    for(int i = 0; i < numberArray->size; i++)
        if(numberArray->elements[i] == key) return i+1;

    return(-1);
}


int iterativeBinarySearch(NUMBER_ARRAY *numberArray, int key){

    int half = 0, max = numberArray->size -1, min = 0;

    while(min <= max){
        half = (min + max) / 2;
        if(numberArray->elements[half] == key)
            return half;
        else if(numberArray->elements[half] > key)
            max = half - 1;
        else
            min = half + 1;
    }

    return(-1);
}


int recursiveBinarySearch(NUMBER_ARRAY *numberArray, int key, int min, int max){

    if(min > max)
        return -1;

    int half = (min + max) / 2;

    if(numberArray->elements[half] == key)
        return half+1;
    else if(numberArray->elements[half] > key)
        return recursiveBinarySearch(numberArray, key, min, half-1);
    else 
        return recursiveBinarySearch(numberArray, key, half+1, max);
}


int search(NUMBER_ARRAY *numberArray, int keySearched, int searchType){

    switch(searchType){
        case SEQUENTIAL_SEARCH: 
            return sequentialSearch(numberArray, keySearched);
        case ITERATIVE_BINARY_SEARCH:
            return iterativeBinarySearch(numberArray, keySearched);
        case RECURSIVE_BINARY_SEARCH:
            return recursiveBinarySearch(numberArray, keySearched, 0, numberArray->size - 1);
        default:
            return(-1);
    }
}