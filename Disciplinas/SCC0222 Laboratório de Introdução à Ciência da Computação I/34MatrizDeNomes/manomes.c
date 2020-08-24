#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESNUMBER 5

char **getNamesList(void);
char *readName(void);
void printNamesList(char **nameslist);
void freeNamesList(char **nameslist);

int main(int argc, char *argv[]){
    //Armazenamanto dos 5 nomes:
    char **nameslist = getNamesList();
    //Impressão dos Nomes em Ordem Alfabética:
    printNamesList(nameslist);
    //Liberação de Memória Alocada:
    freeNamesList(nameslist);
    //Retorno "Exit Success":  
    return 0;
}

char **getNamesList(void){
    //Alocação Dinâmica de Memória para a Lista de Nomes:
    char **nameslist = malloc(NAMESNUMBER * sizeof(char *));
    //Armazenamento dos Nomes Lidos pela Função readName;
    for(int i = 0; i < NAMESNUMBER; i++){
        nameslist[i] = readName();
    }
    //Retorno do Endereço dos bytes alocados para a lista:
    return nameslist;
}

char *readName(void){
    //Declaração e Inicialização de Variáveis:
    char *name = NULL;
    int counter = 0, character = 0;
    //Leitura e Armazenamento do Nome:
    do{
        character = fgetc(stdin);
        name = (char *) realloc(name, (counter+1) * sizeof(char));
        name[counter++] = (char) character;
    }while(character != '\n' && character != EOF);
    //Adição do Terminador de Strings '\0':
    name[--counter] = '\0';
    //Retorno do Endereço dos bytes alocados para o nome:
    return name;
}

void printNamesList(char **nameslist){
    //Colocação dos Nomes em Ordem Alfabética:
    char *aux = NULL;
    for(int i = 0; i < NAMESNUMBER - 1; i++){
        for(int j = i; j < NAMESNUMBER; j++){
            if(strcmp(nameslist[j], nameslist[i]) < 0){ //se o segundo nome vier antes do primeiro
                //Troca da Posição dos Nomes:
                aux = nameslist[i];
                nameslist[i] = nameslist[j];
                nameslist[j] = aux;
            }
        }
    }
    //Impressão dos Nomes da Lista, linha por linha:
    for(int i = 0; i < NAMESNUMBER; i++){
        printf("%s\n", nameslist[i]);
    }
    return;
}

void freeNamesList(char **nameslist){
    for(int i = 0; i < NAMESNUMBER; i++){
        free(nameslist[i]);
    }
    free(nameslist);
    return;
}