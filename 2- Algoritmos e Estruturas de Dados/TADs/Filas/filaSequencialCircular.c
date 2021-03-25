#include "fila.h"

#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 5


struct fila_{
    ITEM *itens[TAM_MAX];
    int inicio;
    int fim;
    int tamanho;
};


FILA *fila_criar(void){

    FILA *novaFila = malloc(sizeof(FILA));

    if(novaFila != NULL){
        novaFila->inicio = 0;
        novaFila->fim = 0;
        novaFila->tamanho = 0;
    }

    return(novaFila);
}


bool fila_apagar(FILA **fila){

    if(*fila != NULL){
        for(int i = (*fila)->inicio; i != (*fila)->fim; i = (i + 1) % TAM_MAX)
            item_apagar(&(*fila)->itens[i]);
        free(*fila);
        *fila = NULL;
        return(True);
    }

    return(False);
}


bool fila_entrar(FILA *fila, ITEM *item){

    if(fila != NULL && item != NULL && !fila_cheia(fila)){
        fila->itens[fila->fim] = item;
        fila->fim = (fila->fim + 1) % TAM_MAX;
        fila->tamanho += 1;
        return(True);
    }

    return(False);
}


bool fila_sair(FILA *fila){

    if(fila != NULL && !fila_vazia(fila)){
        item_apagar(&fila->itens[fila->inicio]);
        fila->inicio = (fila->inicio + 1) % TAM_MAX;
        fila->tamanho -= 1;
        return(True);
    }

    return(False);
}


ITEM *fila_inicio(FILA *fila){

    if(fila != NULL && !fila_vazia(fila))
        return(fila->itens[fila->inicio]);

    return(NULL);
}


int fila_tamanho(FILA *fila){
    return((fila != NULL) ? fila->tamanho : -1);
}


bool fila_cheia(FILA *fila){
    return(fila_tamanho(fila) == TAM_MAX);
}


bool fila_vazia(FILA *fila){
    return(fila_tamanho(fila) == 0);
}


void fila_imprimir(FILA *fila){

    if(fila != NULL){
        printf("INICIO: ");
        for(int i = fila->inicio, contador = 0; contador < fila->tamanho; i = (i+1) % TAM_MAX, contador++)
            item_imprimir(fila->itens[i]);
        printf("FIM\n");
    }
}