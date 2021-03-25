#ifndef FILE_MANAGER_H
    #define FILE_MANAGER_H

    #define NAMES_LIST_FILE_PREFIX "numberList"
    #define EXECUTION_TIME_FILE_DIRECTORY "./Tempos/"
    #define EXECUTION_TIME_FILE_PREFIX "execution"
    #define TEXT_FILE_EXTENSION ".txt"

    void writeExecutionTimeToTextFile(double executionTime, int repetitionsNames, char *inputFileName, int sortingCode);

#endif