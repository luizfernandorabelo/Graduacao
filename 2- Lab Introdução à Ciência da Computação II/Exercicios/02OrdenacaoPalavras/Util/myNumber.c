#include "myNumber.h"

#include <stdio.h>
#include <stdlib.h>


int readInteger(FILE *stream){

    int number = 0;
    
    fscanf(stream, "%d", &number);
    
    return(number);
}


float readFloat(FILE *stream){

    float number = 0;
    
    fscanf(stream, "%f", &number);
    
    return(number);
}


double readDouble(FILE *stream){

    double number = 0;
    
    fscanf(stream, "%lf", &number);
    
    return(number);
}


char *getIntegerAsString(int number){

    char *string = calloc(12, sizeof(char));
    
    sprintf(string, "%d", number);
    
    return(string);
}


char *getFloatAsString(float number){

    char *string = calloc(12, sizeof(char));
    
    sprintf(string, "%f", number);
    
    return(string);
}


char *getDoubleAsString(double number){

    char *string = calloc(12, sizeof(char));
    
    sprintf(string, "%lf", number);
    
    return(string);
}