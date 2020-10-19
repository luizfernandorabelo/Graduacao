#include "lista.h"
#include "aba.h"

#include <stdio.h>
#include <stdlib.h>

#define INCLUIR_NOVA_ABA 1
#define ALTERAR_POSICAO_ABA 2
#define IMPRIMIR_ABAS 3
#define SAIR 4

int readInteger(void);
char *readString(void);

int main(int argc, char *argv[]){

    LISTA *lista = lista_criar();

    int opcao = readInteger();
    while(opcao != SAIR){ 
        if(opcao == INCLUIR_NOVA_ABA){
            ABA *novaAba = aba_criar();
            aba_set_titulo(novaAba, readString());
            aba_set_url(novaAba, readString());
            lista_inserir(lista, novaAba);
        }
        else if(opcao == ALTERAR_POSICAO_ABA){
            char *titulo = readString();
            int posicao = readInteger();
            lista_alterar_posicao(lista, titulo, posicao);
            free(titulo);
        }
        else if(opcao == IMPRIMIR_ABAS){
            lista_imprimir(lista);
        }
        else if(opcao != SAIR){
            //printf("Opcao inválida!\n");
        }
        opcao = readInteger();
    }

    lista_apagar(&lista);

    return 0;
}

int readInteger(void){
    int number = 0;
    scanf("%d", &number);
    return number;
}

char *readString(void){
    char *string = NULL, character = 0;
    int charCounter = 0;
    while(character < 33 && character != EOF) character = fgetc(stdin);
    do{
        string = (char *) realloc(string, (charCounter+2));
        string[charCounter++] = character;
        character = fgetc(stdin);
    }while(character != '\n' && character != '\r' && character != EOF);
    string[charCounter] = '\0';
    return string;
}