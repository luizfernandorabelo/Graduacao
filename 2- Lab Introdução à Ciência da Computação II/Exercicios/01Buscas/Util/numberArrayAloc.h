#ifndef NUMBER_ARRAY_H
    #define NUMBER_ARRAY_H
    
    typedef struct{
        int *elements;
        int size;
    }NUMBER_ARRAY;

    NUMBER_ARRAY *loadNumberArray(int registerNumber);
    void unloadNumberArray(NUMBER_ARRAY *numberArray);

#endif