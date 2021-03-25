#ifndef CSV_READER_H
    #define CSV_READER_H

    #ifndef BOOLEAN_TYPE
        #define BOOLEAN_TYPE

        #define boolean int 
        #define TRUE 1
        #define FALSE 0

    #endif
    
    #include <stdio.h>

    #define CSV_FILE_NAME "inputs.csv"

    typedef struct{
        char **words;
        int size;
    }key_words;
    
    typedef struct{
        int code;
        char *name;
        int relevance;
        char *link; 
        key_words *keyWords;
    }line_;

    line_ *readLineFromCsvFile(FILE *fp);
    void writeLineToCsvFile(line_ *line, FILE *fp);

#endif