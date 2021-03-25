#include <stdio.h>
#include "stopWatch.h"

double getExecutionTime(time_t startTime, time_t endTime){
    return(endTime - startTime) / (double) CLOCKS_PER_SEC;
}

void printExecutionTime(double timeTaken){
    printf("Tempo de execução da tarefa: %lf seg", timeTaken);
}