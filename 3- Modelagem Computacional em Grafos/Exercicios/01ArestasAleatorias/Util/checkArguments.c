#include "checkArguments.h"

#include <stdlib.h>
#include <stdio.h>

#define N_ARGS 3
#define MIN_PROBABILITY 0
#define MAX_PROBABILITY 1


void checkArgumentNumber(int argc) {

    if (argc != N_ARGS) {
        printf("Uso: ./exec n p\n   ");
        printf("- Exemplo: ./exec 4 0.375\n");
        printf("Nota: se você estiver usando o comando \"make run\", não se esqueça de atribuir os valores n e p\n   ");
        printf("- Exemplo: make run n=4 p=0.375\n");
        exit(0);
    }
}


void checkArgumentValues(int numberOfNodes, double connectionProbability) {

    if (numberOfNodes <= 0) {
        printf("Impossível criar matriz com tamanho %d", numberOfNodes);
        exit(0);
    }
    else if (connectionProbability < MIN_PROBABILITY || connectionProbability > MAX_PROBABILITY) {
        printf("A probabilidade de conexão deve estar no intervalo [0,1]\n");
        exit(0);
    }
}