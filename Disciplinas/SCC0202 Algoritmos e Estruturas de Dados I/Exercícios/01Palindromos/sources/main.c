#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]){

    STACK *myStack = stackCreate();
    char *phrase = NULL;
    int charCounter = 0;

    while(!feof(stdin)){
        char character = fgetc(stdin);
        if(isalnum((int) character)){
            ITEM *item = itemCreate(toupper(character));
            stackUp(myStack, item);
            phrase = (char *) realloc(phrase, charCounter+2);
            phrase[charCounter++] = toupper(character);
        }
    }
    phrase[charCounter] = '\0'; //terminador de string
    
    bool palindromeFlag = True;
    for(int i = 0, lenPhrase = strlen(phrase); i < lenPhrase; i++){
        ITEM *item = unStack(myStack);
        if(itemGetKey(item) != phrase[i]){
            palindromeFlag = False;
            break;
        }
        itemDelete(&item);
    }

    if(palindromeFlag == True) printf("É um palíndromo!\n");
    else printf("Não é um palíndromo!\n");

    stackDelete(&myStack);
    free(phrase);

    return 0;
}