#include "jsonTweet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define END_OF_FIELD ','


bool isDelimiter(char character){
    char c = character;
    return((c == '[' || c == ']' || c == '{' || c == '}' || c == '"') ? True : False);
}


bool isEndOfField(char character, FILE *fp){

    if(character == END_OF_FIELD){ 
        character = fgetc(fp);
        if(isDelimiter(character) || character == '\n') 
            return(True); 
    }
    
    return(False);
}


char *readWord(FILE *fp){

    char *word = calloc(1, sizeof(char)); 
    char character = ',';
    int charCounter = 0;

    while(!isalpha(character) && character != EOF){
        character = fgetc(fp);
        if(isEndOfField(character, fp))
            return(word);
    }

    do{
        word = realloc(word, charCounter+2);
        word[charCounter++] = character;
        character = fgetc(fp);
    }while(isalpha(character) && character != EOF);

    word[charCounter] = '\0';

    return(word);
}


void skipUnusefulData(FILE *fp){

    char buffer = fgetc(fp);

    while(!isDelimiter(buffer) && buffer != '\n' && buffer != EOF)
        buffer = fgetc(fp); 
}


bool jumpToTweetField(FILE *fp){

    skipUnusefulData(fp);

    char *fieldName = readWord(fp);

    while(!feof(fp) && strcmp(fieldName, TWEET_FIELD_NAME) != 0){
        skipUnusefulData(fp);
        free(fieldName);
        fieldName = readWord(fp);
    }

    free(fieldName);

    return((feof(fp) ? False : True));
}


FILE *fileOpen(char *fileName, char *mode){

    FILE *fp = fopen(fileName, mode);

    if(fp == NULL)
        printf("There was an error opening the file %s\n", fileName);

    return(fp);
}


bool endOfTweet(char *word){
    return((strcmp(word, "\0") == 0) ? True : False);
}


tweet_words_t *getTweetWords(FILE *fp){

    tweet_words_t *twtWords = malloc(sizeof(tweet_words_t));
    twtWords->words = NULL;
    twtWords->size = 0;

    char *word = readWord(fp);

    while(!endOfTweet(word)){ 
        twtWords->words = realloc(twtWords->words, (twtWords->size + 1) * sizeof(char *));
        twtWords->words[twtWords->size] = word;
        twtWords->size += 1;
        word = readWord(fp);
    }
    
    free(word);
    
    return(twtWords);
}


tweet_words_t **getTweetWordsFromJsonFile(char *fileName){

    FILE *fp = fileOpen(fileName, "r");

    if(fp == NULL)
        return(NULL);
    
    tweet_words_t **twtWords = NULL;
    int twtsCounter = 0; 
    bool tweetFieldFound = False;

    while(True){
        twtWords = realloc(twtWords, (twtsCounter+1) * sizeof(tweet_words_t *));
        if((tweetFieldFound = jumpToTweetField(fp)) == True)
            twtWords[twtsCounter++] = getTweetWords(fp);
        else{
            twtWords[twtsCounter++] = NULL; 
            break;
        }
    }

    fclose(fp);

    if(twtWords[0] != NULL) 
        return(twtWords);

    free(twtWords);
}


void deleteTweetWords(tweet_words_t **tweetWords){

    if(*tweetWords == NULL)
        return(NULL);

    for(int i = 0; tweetWords[i] != NULL; i++){
        tweet_words_t *currentTweet = tweetWords[i];
        for(int j = 0; j < currentTweet->size; j++)
            free(currentTweet->words[j]);
        free(currentTweet->words);
        free(currentTweet);
    }

    free(tweetWords);
}