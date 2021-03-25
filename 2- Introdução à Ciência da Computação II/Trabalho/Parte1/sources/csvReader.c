#include "csvReader.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN_VALID_CHAR 33


char *readField(FILE *fp){

    char *field = NULL;
    int charCounter = 0;
    char character = fgetc(fp);
    
    while(character < MIN_VALID_CHAR && character != EOF) character = fgetc(fp); 

    if(character == FIELD_DELIMITER) // se o campo foi passado em branco
        field = malloc(sizeof(char));
    else{
        do{
            field = realloc(field, (charCounter+2));
            field[charCounter++] = character;
            character = fgetc(fp);
        }while(character != FIELD_DELIMITER && character != '\n' && character != '\r' && character != EOF);
    }
    
    field[charCounter] = '\0'; 
    
    return(field);
}


char *readString(FILE *fp){
 
    char *string = readField(fp);
 
    return(string);
}


int readInteger(FILE *fp){

    char *asciiNumber = readField(fp);

    int integerNumber = 0;

    if(asciiNumber != NULL){
        integerNumber = atoi(asciiNumber);
        free(asciiNumber);
    }
    
    return(integerNumber);
}


double readDouble(FILE *fp){

    char *asciiNumber = readField(fp);

    double doubleNumber = 0;

    if(asciiNumber != NULL){
        doubleNumber = (double) atof(asciiNumber);
        free(asciiNumber);
    }

    return(doubleNumber);
}


HEADER *readHeader(FILE *fp){

    HEADER *header = malloc(sizeof(HEADER));

    int fieldCounter = 0;
    char character = fgetc(fp);

    while(character != '\n'){
        character = fgetc(fp);
        fieldCounter = (character == FIELD_DELIMITER) ? fieldCounter + 1 : fieldCounter;
    }

    fseek(fp, 0, SEEK_SET);

    header->numberOfFields = fieldCounter;

    header->fieldNames = malloc(header->numberOfFields * sizeof(char *));
    
    for(int i = 0; i < header->numberOfFields; i++)
        header->fieldNames[i] = readString(fp);
    
    return(header);
}


REGISTER *readRegister(FILE *fp){

    REGISTER *reg = malloc(sizeof(REGISTER));

    reg->trackName = readString(fp);
    reg->trackId = readString(fp);
    reg->albumName = readString(fp);
    reg->albumId = readString(fp);
    reg->artistName = readString(fp);
    reg->artistId = readString(fp);
    reg->releaseDate = readString(fp);
    reg->lenght = readInteger(fp);
    reg->popularity = readInteger(fp);
    reg->acousticness = readDouble(fp);
    reg->danceability = readDouble(fp);
    reg->energy = readDouble(fp);
    reg->instrumentalness = readDouble(fp);
    reg->liveness = readDouble(fp);
    reg->loudness = readDouble(fp);
    reg->speechness = readDouble(fp);
    reg->time = readDouble(fp);
    reg->timeSignature = readInteger(fp);

    return(reg);
}


FILE *fileOpen(char *fileName, char *mode){

    FILE *fp = fopen(fileName, "r");
   
    if(fp == NULL){
        printf("Não foi possível abrir o arquivo .csv\n");
        exit(FILE_OPEN_FAILURE);
    }

    return(fp);
}


bool isLineEmpty(FILE *fp){
    
    int position = ftell(fp);
    char character = fgetc(fp);
    bool delimiterFound = False;

    while(character != '\n' && character != EOF){
        if(character == FIELD_DELIMITER){
            delimiterFound = True;
            fseek(fp, position, SEEK_SET);
            break;
        }
        character = fgetc(fp);
    }

    return(delimiterFound == True) ? False : True;
}


CSV *csvReadData(char *fileName){
    
    FILE *fp = fileOpen(fileName, "r");

    CSV *csvData = malloc(sizeof(CSV));

    csvData->header = readHeader(fp); 

    REGISTER **registers = NULL;
    int regCounter = 0;

    while(!feof(fp)){
        if(isLineEmpty(fp) == False){
            registers = realloc(registers, (regCounter+1) * sizeof(REGISTER *));
            registers[regCounter++] = readRegister(fp);            
        }       
    }

    csvData->registers = registers;
    csvData->numberOfRegisters = regCounter;

    fclose(fp);

    return(csvData);
}