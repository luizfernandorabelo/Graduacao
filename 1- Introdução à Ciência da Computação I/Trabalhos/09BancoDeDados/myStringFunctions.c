#include "myStringFunctions.h"

char *readString(FILE *stream, char delim){
    char *string = NULL, chracter = fgetc(stream);
    int counter = 0;
    while(chracter == '\n' || chracter == '\r' || chracter == ' ') chracter = fgetc(stream);
    do{
        string = (char *) realloc(string, (counter+2) * sizeof(char));
        string[counter++] = chracter;
        chracter = fgetc(stream);
    }while(chracter != delim && chracter != '\n' && chracter != '\r' && chracter != EOF);
    string[counter] = '\0';
    return string;
}

char *getStringInto(char *originalString, char begin, char end){
    int lenOriginal = strlen(originalString), pos = 0;
    char *newString = NULL;
    while(originalString[pos++] != begin);
    for(int i = pos; i < lenOriginal; i++){
        newString = (char *) realloc(newString, (i-pos+1) * sizeof(char));
        newString[i-pos] = (originalString[i] != end) ? originalString[i] : '\0';
        if(originalString[i] == end) break;
    }
    return newString;
}

void checkExpectedWord(FILE *stream, char *expectedWord){
    char *word = readString(stream, ' ');
    if(strcmp(word, expectedWord) != 0){
        printf("A palavra %s não foi reconhecida\n", word);
        exit(0);
    }
    free(word);
}
