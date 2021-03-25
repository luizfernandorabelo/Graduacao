#include "pilha.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO_SAIDA "hanoi.txt"

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Use o número de discos como segundo argumento! Exemplo: ./hanoi 3\n");
        exit(EXIT_FAILURE);
    }

    int nDiscos = atoi(argv[1]);

    if(nDiscos <= 0){
        printf("O número de discos deve ser maior que zero!\n");
        exit(EXIT_FAILURE);
    }

    PILHA **arrayPilhas = malloc(3 * sizeof(PILHA *));
    arrayPilhas[0] = pilha_criar('A');
    arrayPilhas[1] = pilha_criar('B');
    arrayPilhas[2] = pilha_criar('C');

    FILE *arquivo = fopen(ARQUIVO_SAIDA, "w");

    fprintf(arquivo, ">>> SAÍDA GERADA PARA %d DISCOS\n\n", nDiscos);

    pilha_hanoi(arrayPilhas, nDiscos, arquivo);

    fclose(arquivo);

    printf("Saída gerada em %s!\n", ARQUIVO_SAIDA);

    for(int i = 0; i < 3; i++)
        pilha_apagar(&arrayPilhas[i]);
    
    free(arrayPilhas);

    return(0);
}