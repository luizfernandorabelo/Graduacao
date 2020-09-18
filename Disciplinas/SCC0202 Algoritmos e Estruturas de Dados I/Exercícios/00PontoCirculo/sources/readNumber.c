#include <stdio.h>

int readInteger(){
    int number = 0;
    scanf("%d", &number);
    return(number);
}

float readFloat(){
    float number = 0;
    scanf("%f", &number);
    return(number);
}

double readDouble(){
    double number = 0;
    scanf("%lf", &number);
    return(number);
}