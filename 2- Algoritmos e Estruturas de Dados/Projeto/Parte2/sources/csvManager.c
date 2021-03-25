#include "csvManager.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MIN_VALID_CHAR 33
#define INVALID_INTEGER -1


char *readString(FILE *fp, boolean *endLine){
    
    if(*endLine == TRUE)
        return NULL;
    
    int charCounter = 0;
    char character = 0, *string = NULL;

    while(character < MIN_VALID_CHAR && character != EOF)
        character = fgetc(fp); 

    do{
        string = (char *) realloc(string, (charCounter+2));
        string[charCounter++] = (char) tolower((int) character);
        character = fgetc(fp);
    }while(character != ','  && character != '\n' && character != '\r' && character != EOF);
    
    *endLine = (character == '\n' || character == '\r' || character == EOF) ? TRUE : FALSE;
    
    string[charCounter] = '\0';
    
    return(string);
}


int readNumber(FILE *fp, boolean *endLine){    
    
    char *asciiNumber = readString(fp, endLine);
    
    if(asciiNumber != NULL){
        int integerNumber = atoi(asciiNumber);
        free(asciiNumber);
        return integerNumber;
    }

    return(INVALID_INTEGER);
}


line_ *readLineFromCsvFile(FILE *fp){
    
    line_ *line = malloc(sizeof(line_));

    boolean endLine = FALSE;
    
    line->code = readNumber(fp, &endLine);

    if(line->code == INVALID_INTEGER){
        free(line);
        fclose(fp);
        return(NULL);
    }

    line->name = readString(fp, &endLine);
    line->relevance = readNumber(fp, &endLine);
    line->link = readString(fp, &endLine);
    
    line->keyWords = malloc(sizeof(key_words));
    line->keyWords->words = NULL;
    
    int wordsCounter = 0;
    char *string = NULL;

    while(endLine == FALSE){
        string = readString(fp, &endLine);
        if(string != NULL){
            line->keyWords->words = realloc(line->keyWords->words, (wordsCounter + 1) * sizeof(char *));
            line->keyWords->words[wordsCounter++] = string; 
        }
    }

    line->keyWords->size = wordsCounter;
    
    return(line);
}


void writeLineToCsvFile(line_ *line, FILE *fp){

    if(ftell(fp) != SEEK_SET)
        fprintf(fp, "\n");

    fprintf(fp, "%.4d,", line->code);
    fprintf(fp, "%s,",line->name);
    fprintf(fp, "%d,", line->relevance);
    fprintf(fp, "%s,", line->link);
 
    int i; 
    for(i = 0; i < (line->keyWords->size - 1); i++){
        fprintf(fp, "%s,", line->keyWords->words[i]);
    }
    fprintf(fp, "%s", line->keyWords->words[i]);
}