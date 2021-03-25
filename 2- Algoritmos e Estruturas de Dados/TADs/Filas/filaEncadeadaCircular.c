#include "fila.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *proximo;
};

struct fila_{
    NO *cabeca;
    NO *fim;
    int tamanho;
};


NO *fila_criar_no(ITEM *item){

    NO *novoNo = malloc(sizeof(NO));

    if(novoNo != NULL){
        novoNo->item = item;
        novoNo->proximo = NULL;
    }

    return(novoNo);
}


FILA *fila_criar(void){

    FILA *novaFila = malloc(sizeof(FILA));

    if(novaFila != NULL){
        novaFila->cabeca = fila_criar_no(NULL);
        novaFila->cabeca->proximo = novaFila->cabeca;
        novaFila->fim = novaFila->cabeca;
        novaFila->tamanho = 0;
    }

    return(novaFila);
}


bool fila_apagar(FILA **fila){

    if(*fila == NULL)
        return(False);

    NO *noAtual = (*fila)->cabeca->proximo;

    while(noAtual != (*fila)->cabeca){
        NO *proximo = noAtual->proximo;
        item_apagar(&noAtual->item);
        free(noAtual);
        noAtual = proximo;
    }

    free((*fila)->cabeca);
    free(*fila);
    *fila = NULL;

    return(True);
}


bool fila_entrar(FILA *fila, ITEM *item){

    if(fila == NULL || item == NULL || fila_cheia(fila))
        return(False);

    NO *novoNo = fila_criar_no(item);

    if(fila->tamanho == 0)
        fila->cabeca->proximo = novoNo;
    else
        fila->fim->proximo = novoNo;

    novoNo->proximo = fila->cabeca;
    fila->fim = novoNo; 
    fila->tamanho += 1;

    return(True);
}


bool fila_sair(FILA *fila){

    if(fila == NULL || fila_vazia(fila))
        return(False);

    NO *noRemovido = fila->cabeca->proximo;
    ITEM *itemRemovido = noRemovido->item;

    fila->cabeca->proximo = noRemovido->proximo;

    item_apagar(&itemRemovido);
    free(noRemovido);

    fila->tamanho -= 1;

    return(True);
}


ITEM *fila_inicio(FILA *fila){

    if(fila == NULL || fila_vazia(fila))
        return(NULL);
    
    return(fila->cabeca->proximo->item);
}


bool fila_cheia(FILA *fila){

    NO *noTeste = fila_criar_no(NULL);

    if(noTeste == NULL)
        return(True);

    free(noTeste);
    return(False);
}


bool fila_vazia(FILA *fila){
    return(fila_tamanho(fila) == 0);
}


int fila_tamanho(FILA *fila){
    return((fila != NULL) ? fila->tamanho : -1);
}


void fila_imprimir(FILA *fila){

    NO *noAtual = fila->cabeca->proximo;

    printf("INÍCIO: ");
    while(noAtual != fila->cabeca){
        item_imprimir(noAtual->item);
        noAtual = noAtual->proximo;
    }
    printf("FIM\n");
}