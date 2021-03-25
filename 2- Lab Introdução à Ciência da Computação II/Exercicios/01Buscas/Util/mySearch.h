#ifndef MY_SEARCH_H
    #define MY_SEARCH_H

    #include "numberArrayAloc.h"
    
    #define SEQUENTIAL_SEARCH 1
    #define ITERATIVE_BINARY_SEARCH 2
    #define RECURSIVE_BINARY_SEARCH 3
    
    int search(NUMBER_ARRAY *numberArray, int keySearched, int searchType);

#endif