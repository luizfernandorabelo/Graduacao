#include "pilha.h"

#include <stdio.h>

#define BINARIO_TAM_MAX 30

int main(int argc, char *argv[]){

    int decimal;
    PILHA *pilha = pilha_criar();

    printf("Digite um numero decimal positivo: ");
    scanf("%d", &decimal);

    printf("O número %d na base binária é: ", decimal);

    if(decimal == 0)
        printf("0");

    while(decimal != 0){
        pilha_empilhar(pilha, item_criar(decimal % 2));
        decimal /= 2;
    }

    while(!pilha_vazia(pilha)){
        printf("%d", item_obter_chave(pilha_topo(pilha)));
        pilha_desempilhar(pilha);
    }
    printf("\n");
    
}