#ifndef NUMBER_LIST_ALOC_H
    #define NUMBER_LIST_ALOC_H

    typedef struct{
        int *elements;
        int size;
    }NUMBER_LIST_DATA;
    
    NUMBER_LIST_DATA *loadNumberList(int numberListSize);
    void unloadNumberList(NUMBER_LIST_DATA *numberList);
    
#endif