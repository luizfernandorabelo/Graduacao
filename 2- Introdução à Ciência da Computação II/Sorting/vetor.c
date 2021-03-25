#include "vetor.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


VETOR *gerar_vetor(int min, int max, int tamanho){
    
    if(tamanho <= 0){
        fprintf(stderr, "Impossível gerar vetor com tamanho selecionado!\n");
        return(NULL);
    }
    
    if(min > max){
        fprintf(stderr, "O valor mínimo não pode ser maior que o mínimo!\n");
        return(NULL);
    }

    srand(time(NULL));

    VETOR *novoVetor = malloc(sizeof(VETOR));
    novoVetor->tamanho = tamanho;
    novoVetor->chaves = malloc(tamanho * sizeof(int));

    for(int i = 0; i < tamanho; i++)
        novoVetor->chaves[i] = rand() % (max-min) + min + 1;

    return(novoVetor);    
}


void imprimir_vetor(VETOR *vetor, FILE *stream){

    if(vetor == NULL)
        return; 

    int tamanho = vetor->tamanho;

    for(int i = 0; i < tamanho; i++)
        fprintf(stream, "%d; ", vetor->chaves[i]);

    fprintf(stream, "\n");
}


void liberar_vetor(VETOR **vetor){

    if(*vetor == NULL)
        return;
    
    free((*vetor)->chaves);
    free(*vetor);
    *vetor = NULL;
}