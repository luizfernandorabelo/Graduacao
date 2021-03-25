#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct dictionary_{
    char **words;
    int size;
};


char *readValidWord(FILE *fp){

    char *word = calloc(1, sizeof(char)); 
    char character = '\0';
    int charCounter = 0;
    
    while(!isalnum(character) && character != EOF)
        character = fgetc(fp);
    
    if(character == EOF){
        free(word);
        return(NULL);
    }

    do{
        word = realloc(word, charCounter+2);
        word[charCounter++] = character;
        character = fgetc(fp);
    }while(isalnum(character) && character != EOF);

    word[charCounter] = '\0';
 
    return(word);
}


int wordBinarySearch(char **words, char *searched, int startPos, int endPos){

    if(startPos > endPos)
        return(-1);
    
    int halfPos = (startPos + endPos) / 2;

    if(strcasecmp(searched, words[halfPos]) == 0)
        return(halfPos);

    if(strcasecmp(searched, words[halfPos]) < 0)
        return(wordBinarySearch(words, searched, startPos, halfPos-1));

    return(wordBinarySearch(words, searched, halfPos+1, endPos));
}


bool isWordInDictionary(char *word, dictionary_t *dictionary){

    int index = -1;

    if(dictionary->words != NULL)
        index = wordBinarySearch(dictionary->words, word, 0, dictionary->size-1);

    return((index > -1) ? True : False);
}


int getInsertionIndex(char **words, char *inserted, int dictionarySize){

    int index = 0;
    
    while(index < dictionarySize && strcasecmp(inserted, words[index]) >= 0)
        index++;

    return(index);
}


void insertWordInDictionary(dictionary_t *dictionary, char *word){

    int insertionIndex = 0;
    bool wordFound = isWordInDictionary(word, dictionary);

    if(wordFound == False){
        insertionIndex = getInsertionIndex(dictionary->words, word, dictionary->size);        
        dictionary->words = realloc(dictionary->words, (dictionary->size + 1) * sizeof(char *));
        dictionary->size += 1;
        for(int i = dictionary->size-1; i > insertionIndex; i--)
            dictionary->words[i] = dictionary->words[i-1];
        dictionary->words[insertionIndex] = word;
    }
    else
        free(word);
}


dictionary_t *loadDictionaryFromTxtFile(char *fileName){

    FILE *fp = fopen(fileName, "r");

    if(fp == NULL)
        return(NULL);

    dictionary_t *dictionary = malloc(sizeof(dictionary_t));
    dictionary->words = NULL;
    dictionary->size = 0;

    while(!feof(fp)){
        char *word = readValidWord(fp);
        if(word != NULL)
            insertWordInDictionary(dictionary, word);
    }

    fclose(fp);
    
    return(dictionary);
}


void unloadDictionary(dictionary_t *dictionary){

    for(int i = 0; i < dictionary->size; i++)
        free(dictionary->words[i]);
    
    free(dictionary->words);
    free(dictionary);
}