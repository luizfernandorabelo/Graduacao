#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 20
#define MESSAGE_SIZE 200

char **readMessage();
/*Função  que  lê na entrada  padrão a mensagem,  ordenando-a em forma de "lista".  Retorna o
endereço de memória em que a mensagem foi armazenada.*/

void replaceWord(char **message, char *originalWord, char *newWord);
/*Função que verifica se a primeira palavra digitada pelo usuário existe na mensagem. Se sim,
a substitui pela segunda palavra digitada pelo usuário. Tem como parâmetros os endereços da
mensagem, da primeira palavra e da segunda palavra. */

void printMessage(char **message);
/*Função que imprime na tela todos os elementos da mensagem (palavras e pontuação)*/


int main(int argc, char *argv[]){

    //Alocação Dinâmica de Memória:
    char *originalWord = (char *) calloc(WORD_SIZE, sizeof(char));
    char *newWord = (char *) calloc(WORD_SIZE, sizeof(char));

    //Leitura e Armazenamento das Palavras e da Mensagem:
    scanf("%s ", originalWord);
    scanf("%s ", newWord);
    char **message = readMessage();
    
    //Substituição da Palavra Original pela Nova Palavra:
    replaceWord(message, originalWord, newWord);
    
    //Impressão da Mensagem Final na Tela:
    printMessage(message);

    //Liberação de Memória Alocada:
    for(int i = 0; i < MESSAGE_SIZE; i++) {
        free(message[i]);
    }
    free(message);
    free(originalWord);
    free(newWord);

    return 0;
}


char **readMessage(){
    
    //ALocação Dinâmica de Memória:
    char **list = (char **) calloc (MESSAGE_SIZE, sizeof(char*));
    for(int i = 0; i < MESSAGE_SIZE; i++){
        list[i] = (char *) calloc (WORD_SIZE, sizeof(char));
    }
    
    //Variáveis Auxiliares:    
    char character; //armazenará o caractere lido na entrada padrão
    short lines = 0, columns = 0; //posições das linhas e colunas da lista
    
    //Leitura e Armazenamento da Mensagem:
    do{
        character = fgetc(stdin);
        if(character >= 65 && character <= 122){ //se character for letra
            list[lines][columns++] = character;
        }
        else if(character >= 32){ //se ltetter for pontuação
            if(list[lines][columns-1] >= 65 && list[lines][columns] <= 122){ //se character anterior for letra
                lines += 1;
                columns = 0;
            }
            list[lines++][columns] = character;
        }
    } while (character != '\n' && character != EOF);

    return list;
}

void replaceWord(char ** message, char *originalWord, char *newWord){

    short int charcounter = 0;

    for(int i = 0; message[i][0] != '\0'; i++){
        for(int j = 0; message[i][j] != 0 && message[i][j] >= 65; j++){
            if(message[i][j] == originalWord[j]){ //se os caracteres correspondentes forem iguais
                charcounter += 1;;
            }
        }
        if(charcounter == strlen(originalWord)){ //se a palavra da mensagem for igual à palavra original
            for(int j = 0; j < WORD_SIZE; j++){
                message[i][j] = 0;
                if(j < strlen(newWord)){
                    message[i][j] = newWord[j];
                }
            }
        }
        charcounter = 0;
    }

    return;
}

void printMessage(char **list){
    for(int i = 0; list[i][0] != 0; i ++){
        printf("%s", list[i]);
    }
    printf("\n");

    return;
}