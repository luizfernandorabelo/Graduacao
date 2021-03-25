#include "namesList.h"
#include "stopWatch.h"
#include "timeWriter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[]){

    #ifdef RUN_CODES
    
        char fileName[20]; scanf("%s", fileName);
        
        int sortingType; scanf("%d", &sortingType);

        NAMES_LIST *namesList = loadNamesList(fileName);

        sortNamesListDescending(namesList, sortingType);

        printNamesList(namesList);

        freeNamesList(&namesList);

    #endif


    #ifdef COUNT_TIME 

        if(argc != 4){
            printf("Usage: ./progname inputsFile.txt executionsNumber sortingCode\n");
            exit(0);
        }

        char *inputFileName = argv[1];
        int executionsNumber = atoi(argv[2]);
        int sortingCode = atoi(argv[3]);

        double averageTime = 0.0;

        for(int i = 0; i < executionsNumber; i++){
            
            NAMES_LIST *namesList = loadNamesList(inputFileName);
            
            time_t startTime = clock();
            
            sortNamesListDescending(namesList, sortingCode);
            
            time_t endTime = clock();
            
            averageTime += getExecutionTime(startTime, endTime);
            
            freeNamesList(&namesList);
        }

        averageTime /= (double) executionsNumber;

        writeExecutionTimeToTextFile(averageTime, executionsNumber, inputFileName, sortingCode); 
        
        printf("%s -> %d: %lf seg\n", inputFileName, sortingCode, averageTime);

    #endif


    return 0;
}