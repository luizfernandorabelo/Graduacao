#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]){

    PILHA *minhaPilha = pilha_criar();
    char *frase = NULL;
    int charCounter = 0;

    while(!feof(stdin)){
        char character = fgetc(stdin);
        if(isalnum((int) character)){
            ITEM *item = item_criar(toupper(character));
            pilha_empilhar(minhaPilha, item);
            frase = (char *) realloc(frase, charCounter + 2);
            frase[charCounter++] = toupper(character);
        }
    }
    frase[charCounter] = '\0'; //terminador de string
    
    bool ehPalindromo = True;
    for(int i = 0, tamanhoFrase = strlen(frase); i < tamanhoFrase; i++){
        ITEM *item = pilha_topo(minhaPilha);
        if(item_obter_chave(item) != frase[i]){
            ehPalindromo = False;
            break;
        }
        pilha_desempilhar(minhaPilha);
    }

    if(ehPalindromo == True) printf("É um palíndromo!\n");
    else printf("Não é um palíndromo!\n");

    pilha_apagar(&minhaPilha);
    free(frase);

    return(0);
}