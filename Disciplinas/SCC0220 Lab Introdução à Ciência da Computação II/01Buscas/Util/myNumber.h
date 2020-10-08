#ifndef MY_NUMBER_H
    #define MY_NUMBER_H

    #include <stdio.h>

    int readInteger(FILE *stream);
    float readFloat(FILE *stream);
    double readDouble(FILE *stream);
    char *getIntegerAsString(int number);
    char *getFloatAsString(float number);
    char *getDoubleAsString(double number);

#endif