#include "deque.h"

#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 5


struct deque_{
    ITEM *itens[TAM_MAX];
    int inicio;
    int fim;
    int tamanho;
};


DEQUE *deque_criar(void){

    DEQUE *novaDeque = malloc(sizeof(DEQUE));

    if(novaDeque != NULL){
        novaDeque->inicio = 0;
        novaDeque->fim = 0;
        novaDeque->tamanho = 0;
    }

    return(novaDeque);
}


bool deque_apagar(DEQUE **deque){

    if(*deque != NULL){
        for(int i = (*deque)->inicio; i != (*deque)->fim; i = (i + 1) % TAM_MAX)
            item_apagar(&(*deque)->itens[i]);
        free(*deque);
        *deque = NULL;
        return(True);
    }

    return(False);
}


bool deque_inserir_inicio(DEQUE *deque, ITEM *item){

    if(deque != NULL && item != NULL && !deque_cheia(deque)){
        deque->inicio = (deque->inicio - 1 + TAM_MAX) % TAM_MAX;        
        deque->itens[deque->inicio] = item;
        deque->tamanho += 1;
        return(True);
    }

    return(False);
}


bool deque_inserir_fim(DEQUE *deque, ITEM *item){

    if(deque != NULL && item != NULL && !deque_cheia(deque)){
        deque->itens[deque->fim] = item;
        deque->fim = (deque->fim + 1) % TAM_MAX;
        deque->tamanho += 1;
        return(True);
    }

    return(False);
}


bool deque_remover_inicio(DEQUE *deque){

    if(deque != NULL && !deque_vazia(deque)){
        item_apagar(&deque->itens[deque->inicio]);
        deque->inicio = (deque->inicio + 1) % TAM_MAX;
        deque->tamanho -= 1;
        return(True);
    }

    return(False);
}


bool deque_remover_fim(DEQUE *deque){

    if(deque != NULL && !deque_vazia(deque)){
        deque->fim = (deque->fim - 1 + TAM_MAX) % TAM_MAX;
        item_apagar(&deque->itens[deque->fim]);
        deque->tamanho -= 1;
        return(True);
    }

    return(False);
}


ITEM *deque_inicio(DEQUE *deque){

    if(deque != NULL && !deque_vazia(deque))
        return(deque->itens[deque->inicio]);

    return(NULL);
}


ITEM *deque_fim(DEQUE *deque){

    if(deque != NULL && !deque_vazia(deque))
        return(deque->itens[(deque->fim - 1 + TAM_MAX) % TAM_MAX]);

    return(NULL);
}


int deque_tamanho(DEQUE *deque){
    return((deque != NULL) ? deque->tamanho : -1);
}


bool deque_cheia(DEQUE *deque){
    return(deque_tamanho(deque) == TAM_MAX);
}


bool deque_vazia(DEQUE *deque){
    return(deque_tamanho(deque) == 0);
}


void deque_imprimir(DEQUE *deque){

    if(deque != NULL){
        printf("INICIO: ");
        for(int i = deque->inicio, contador = 0; contador < deque->tamanho; i = (i+1) % TAM_MAX, contador++)
            item_imprimir(deque->itens[i]);
        printf("FIM\n");
    }
}