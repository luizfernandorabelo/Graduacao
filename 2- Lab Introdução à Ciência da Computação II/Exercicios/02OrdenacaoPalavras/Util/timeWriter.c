#include "timeWriter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "myNumber.h"
#include "namesList.h"


char *getSortingName(int sortingCode){

    char *sortingName = NULL;

    switch(sortingCode){
        case BUBBLE:
            sortingName = (char *) calloc(7, sizeof(char));
            strcpy(sortingName, "Bubble");
            break;
        case INSERTION:
            sortingName = (char *) calloc(10, sizeof(char));
            strcpy(sortingName, "Insertion");
            break;
        case MERGE:
            sortingName = (char *) calloc(6, sizeof(char));
            strcpy(sortingName, "Merge");
            break;
        default:
            break;
    }
    
    return(sortingName);
}


char *getExecutionTimeFileName(int inputFileSize, int sortingCode){

    char *sortingName = getSortingName(sortingCode);

    char *asciiInputFileSize = getIntegerAsString(inputFileSize);

    char *executionTimeFileName = calloc(strlen(EXECUTION_TIME_FILE_PREFIX)
                                       + strlen(sortingName)
                                       + strlen(asciiInputFileSize)
                                       + 1, sizeof(char));

    strcat(executionTimeFileName, asciiInputFileSize);
    strcat(executionTimeFileName, EXECUTION_TIME_FILE_PREFIX);
    strcat(executionTimeFileName, sortingName);

    free(asciiInputFileSize); 

    return(executionTimeFileName);
}


char *getExecutionTimeFilePath(int repetitionsNumber, int sortingCode){

    char *executionTimeFileName = getExecutionTimeFileName(repetitionsNumber, sortingCode);

    char *executionTimeFIlePath = calloc(strlen(EXECUTION_TIME_FILE_DIRECTORY)
                                       + strlen(executionTimeFileName)
                                       + strlen(TEXT_FILE_EXTENSION)
                                       + 1, sizeof(char));
    
    strcat(executionTimeFIlePath, EXECUTION_TIME_FILE_DIRECTORY);
    strcat(executionTimeFIlePath, executionTimeFileName);
    strcat(executionTimeFIlePath, TEXT_FILE_EXTENSION);

    free(executionTimeFileName);

    return(executionTimeFIlePath);
}


int getInputFileSize(char *inputFileName){

    char *inputFileNameCopy = calloc(strlen(inputFileName) + 1, sizeof(char));

    memcpy(inputFileNameCopy, inputFileName, strlen(inputFileName) + 1);
    
    int i = 0;

    while(i < strlen(inputFileNameCopy) && isdigit(inputFileNameCopy[i]))
        i++;

    inputFileNameCopy[i] = '\0';

    int inputFileSize = atoi(inputFileNameCopy) * 1000;
    
    free(inputFileNameCopy);
    
    return(inputFileSize);
}


void writeExecutionTimeToTextFile(double executionTime, int repetitionsNumber, char *inputFileName, int sortingCode){

    char *filePath = getExecutionTimeFilePath(repetitionsNumber, sortingCode);

    FILE *filePointer = fopen(filePath, "a+");

    if(filePointer == NULL){
        printf("Erro ao abrir o arquivo %s para escrita. Programa abortado\n", filePath);
        exit(0);
    }

    int inputFileSize = getInputFileSize(inputFileName);  

    fprintf(filePointer, "%d ", inputFileSize);
    fprintf(filePointer, "%lf\n", executionTime);

    fclose(filePointer);
    free(filePath);
}