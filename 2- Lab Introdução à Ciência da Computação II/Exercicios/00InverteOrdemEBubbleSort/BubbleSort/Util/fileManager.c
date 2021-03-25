#include "fileManager.h"
#include "myNumber.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *getNumberListFileName(int numberListSize){

    char *digitsBuffer = getIntegerAsString(numberListSize);

    char *numberListFileName = calloc(strlen(NUMBER_LIST_FILE_PREFIX) 
                                    + strlen(digitsBuffer) 
                                    + 1, sizeof(char));

    strcat(numberListFileName, NUMBER_LIST_FILE_PREFIX);
    strcat(numberListFileName, digitsBuffer);

    free(digitsBuffer);

    return(numberListFileName);
}


char *getNumberListFilePath(int numberListSize){

    char *numberListFileName = getNumberListFileName(numberListSize);

    char *numberListFilePath = calloc(strlen(NUMBER_LIST_FILE_DIRECTORY) 
                                    + strlen(numberListFileName) 
                                    + strlen(BINARY_FILE_EXTENSION) 
                                    + 1, sizeof(char));
                                
    strcat(numberListFilePath, NUMBER_LIST_FILE_DIRECTORY);
    strcat(numberListFilePath, numberListFileName);
    strcat(numberListFilePath, BINARY_FILE_EXTENSION);

    free(numberListFileName);

    return(numberListFilePath);
}


char *getExecutionTimeFileName(int inputFileSize){

    char *digitsBuffer = getIntegerAsString(inputFileSize);

    char *executionTimeFileName = calloc(strlen(EXECUTION_TIME_FILE_PREFIX)
                                       + strlen(digitsBuffer)
                                       + 1, sizeof(char));

    strcat(executionTimeFileName, EXECUTION_TIME_FILE_PREFIX);
    strcat(executionTimeFileName, digitsBuffer);

    free(digitsBuffer); 

    return(executionTimeFileName);
}


char *getExecutionTimeFilePath(int repetitionsNumber){

    char *executionTimeFileName = getExecutionTimeFileName(repetitionsNumber);

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


int *readNumberListFromBinaryFile(int numberListSize){

    int *numberList = malloc(numberListSize * sizeof(int));
    char *filePath = getNumberListFilePath(numberListSize);
    
    FILE *filePointer = fopen(filePath, "rb"); 

    if(filePointer == NULL){
        printf("O arquivo %s não existe. Programa abortado\n", filePath);
        exit(0);
    }

    for(int i = 0; i < numberListSize; i++) 
        fread(&numberList[i], sizeof(int), 1, filePointer);
    
    fclose(filePointer);
    free(filePath);

    return(numberList);
}


void writeExecutionTimeToTextFile(double executionTime, int repetitionsNumber, int numberListSize){

    char *filePath = getExecutionTimeFilePath(repetitionsNumber);

    FILE *filePointer = fopen(filePath, "a+");

    if(filePointer == NULL){
        printf("Erro ao abrir o arquivo %s para escrita. Programa abortado\n", filePath);
        exit(0);
    }

    fprintf(filePointer, "%d ", numberListSize);
    fprintf(filePointer, "%lf\n", executionTime);

    fclose(filePointer);
    free(filePath);
}