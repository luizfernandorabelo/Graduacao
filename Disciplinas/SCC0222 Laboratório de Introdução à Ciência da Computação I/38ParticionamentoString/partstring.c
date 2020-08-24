#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *readPhrase();
char **partitionPhrase(char *phrase, int *wordsnumber);
char **sortMatrix(char **wordsmatrix, int wordsnumber);
void printWordsMatrix(char **wordsmatrix, int wordsnumber, int option);

int main(int argc, char *argv[]){

    //Declaração e Inicialização de Variáveis:
    int wordsnumber = 0, option = 0;

    //Leitura e Armazenamento da Frase:
    char *phrase = readPhrase();

    //Leitura e Armazenamento da Opção de Impressão:
    scanf("%d", &option);

    //Geração da Matriz (lista de palavras):  
    char **wordsmatrix = partitionPhrase(phrase, &wordsnumber);

    //Impressão da Matriz e Liberação de seus bytes:
    printWordsMatrix(wordsmatrix, wordsnumber, option);

    //Liberação de Memória Alocada para a Frase:
    free(phrase);

    return 0;
}

char *readPhrase(){
    //Declaração e Inicialização de Variáveis:
    int counter = 0;
    char *phrase = NULL, character;
    //Leitura e Armazenamento da Frase:
    do{
        character = fgetc(stdin);
        phrase = (char *) realloc(phrase, (counter+1) * sizeof(char));
        phrase[counter++] = character;
    }while(character != '\n');
    //Adição do Terminador de Strings '\0':
    phrase[--counter] = '\0';
    //Retorno do Endereço dos bytes Alocados para a Frase:
    return phrase;
}

char **partitionPhrase(char *phrase, int *wordsnumber){
    //Declaração e Inicialização de Variáveis:
    int auxcounter = 0, matrixcounter = 0;
    char **wordsmatrix = NULL, *aux = NULL;
    //Processo de Pariticionamento da Frase:
    for(int i = 0; i <= strlen(phrase); i++){ 
        aux = (char *) realloc(aux, (auxcounter+1) * sizeof(char));
        aux[auxcounter++] = phrase[i];
        if(aux[auxcounter-1] == ' ' || aux[auxcounter-1] == '\0'){ 
            //Adição do terminador de strings '\0' à palavra:
            aux[auxcounter-1] = '\0';
            //Alocação da Nova Palavra na Matriz de Palavras:
            wordsmatrix = (char **) realloc(wordsmatrix, (matrixcounter+1) * sizeof(char *));
            wordsmatrix[matrixcounter] = calloc(auxcounter, sizeof(char));
            strcpy(wordsmatrix[matrixcounter++], aux);
            //Redefinição do Índice da Variável Auxiliar:
            auxcounter = 0;
        }
    }
    //Determinação do Número total de Palavras Armazenadas:
    *wordsnumber = matrixcounter;
    //Liberação dos bytes Reservados para a Variável Auxiliar:
    free(aux);
    //Retorno do Endereço dos bytes Reservados para a Matriz de Palavras:
    return wordsmatrix;
}

void printWordsMatrix(char **wordsmatrix, int wordsnumber, int option){
    //Verificação da Opção Digitada:
    wordsmatrix = option == 2 ? sortMatrix(wordsmatrix, wordsnumber) : wordsmatrix;
    //Impressão e Liberação da Matriz de Palavras, linha a linha:
    for(int i = 0; i < wordsnumber; i++){
        printf("%s\n", wordsmatrix[i]);
        free(wordsmatrix[i]);
    }
    free(wordsmatrix);
    return;
}

char **sortMatrix(char **wordsmatrix, int wordsnumber){
    //Declaração e Inicializaçao de Variável Auxiliar:
    char *aux = NULL; //servirá como temporária em trocas
    //Passagem de Todas as Letras para Minúsculo:
    for(int i = 0; i < wordsnumber; i++){
        for(int j = 0; j < strlen(wordsmatrix[i]); j++){
            wordsmatrix[i][j] = tolower(wordsmatrix[i][j]);
        }
    }
    //Ordenação das Palavras de Forma Alfabética:
    for(int i = 0; i < wordsnumber - 1; i++){
        for(int j = i; j < wordsnumber; j++){
            if(strcmp(wordsmatrix[j], wordsmatrix[i]) < 0){
                aux = wordsmatrix[j];
                wordsmatrix[j] = wordsmatrix[i];
                wordsmatrix[i] = aux;
            }
        }
    }
    //Retorno do Endereço dos bytes Alocados para a Matriz de Palavras já Ordenada: 
    return wordsmatrix;
}
