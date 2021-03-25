#ifndef FILE_MANAGER_H
    #define FILE_MANAGER_H

    #define NUMBER_LIST_FILE_DIRECTORY "./InputData/"
    #define NUMBER_LIST_FILE_PREFIX "numberList"
    #define EXECUTION_TIME_FILE_DIRECTORY "./OutputData/"
    #define EXECUTION_TIME_FILE_PREFIX "execution"
    #define BINARY_FILE_EXTENSION ".dat"
    #define TEXT_FILE_EXTENSION ".txt"

    int *readNumberListFromBinaryFile(int numberListSize); 
    void writeExecutionTimeToTextFile(double executionTime, int repetitionsNumber, int numberListSize);

#endif