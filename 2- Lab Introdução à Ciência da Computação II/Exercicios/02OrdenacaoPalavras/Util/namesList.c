#include "namesList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct names_list_{
    char **names;
    int size;
};


FILE *fileOpen(char *fileName, char *mode){

    FILE *fp = fopen(fileName, mode);

    if(fp == NULL) 
        printf("Erro! Verifique se o arquivo de entradas se encontra na mesma pasta que o arquivo Makefile\n");

    return(fp);
}


char *readString(FILE *stream){

    char *string = NULL, character = 0;
    int charCounter = 0;
    
    while(character < 33)
        if((character = tolower(fgetc(stream))) == EOF)
            return(NULL);
    
    do{
        string = (char *) realloc(string, charCounter + 2);
        string[charCounter++] = character;
        character = tolower(fgetc(stream));
    }while(character != '\n' && character != '\r' && character != EOF);
    
    string[charCounter] = '\0';
    
    return(string);
}


NAMES_LIST *loadNamesList(char *fileName){

    FILE *fp = fileOpen(fileName, "r");

    if(fp == NULL)
        exit(0); 
    
    NAMES_LIST *namesList = malloc(sizeof(NAMES_LIST));
    namesList->names = NULL; namesList->size = 0;
    
    while(!feof(fp)){
        char *string = readString(fp);
        if(string != NULL){
            namesList->names = (char **) realloc(namesList->names, (namesList->size + 1) * sizeof(char *));
            namesList->names[namesList->size] = string;
            namesList->size += 1;
        }
    }
    
    fclose(fp);
    
    return(namesList);
}


void bubbleSortDescending(NAMES_LIST *namesList){

    char **names = namesList->names;
    char *actual, *last, *auxTrade;
   
    for(int i = namesList->size - 1; i >= 0; i--){
        for(int j = 0; j < i; j++){
            actual = names[j], last = names[i];
            if(strcmp(actual, last) < 0){
                auxTrade = last;
                names[i] = actual;
                names[j] = auxTrade;
            }
        }
    }
   
    namesList->names = names;
}


void insertionSortDescending(NAMES_LIST *namesList){

    char **names = namesList->names;
   
    for(int i = 1; i < namesList->size; i++){
        int j = i - 1;
        char *actual = names[i];
        while(j >= 0 && strcmp(actual, names[j]) > 0){
            names[j+1] = names[j];
            j--;
        }
        names[j+1] = actual;
    }
   
    namesList->names = names;
}


void mergeSortDescending(char **names, int startPos, int endPos){

    if(startPos >= endPos)
        return;

    int centerPos = (startPos + endPos) / 2;

    mergeSortDescending(names, startPos, centerPos);
    mergeSortDescending(names, centerPos+1, endPos);

    char **namesFraction = malloc((endPos - startPos + 1) * sizeof(char *));

    int i = startPos, j = centerPos + 1, k = 0;

    while(i <= centerPos && j <= endPos){
        if(strcmp(names[i], names[j]) >= 0)
            namesFraction[k++] = names[i++];
        else
            namesFraction[k++] = names[j++];
    }

    while(i <= centerPos)
        namesFraction[k++] = names[i++];
    while(j <= endPos)
        namesFraction[k++] = names[j++];
    
    for(int i = startPos, k = 0; i <= endPos; i++, k++)
        names[i] = namesFraction[k];
    
    free(namesFraction);
}


void sortNamesListDescending(NAMES_LIST *namesList, int type){

    if(namesList == NULL)
        return;

    switch(type){
        case BUBBLE:
            return bubbleSortDescending(namesList);
        case INSERTION:
            return insertionSortDescending(namesList);
        case MERGE:
            return mergeSortDescending(namesList->names, 0, namesList->size - 1);
        default:
            return;
    }
}


void printNamesList(NAMES_LIST *namesList){

    if(namesList == NULL)
        return;
    
    for(int i = 0; i < namesList->size; i++)
        printf("%s\n", namesList->names[i]);    
}


void freeNamesList(NAMES_LIST **namesList){

    if(*namesList == NULL)
        return;
    
    for(int i = 0; i < (*namesList)->size; i++)
        free((*namesList)->names[i]);

    free((*namesList)->names);
    free(*namesList); 
}