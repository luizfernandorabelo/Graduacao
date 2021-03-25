#include "deque.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *proximo;
};

struct deque_{
    NO *cabeca;
    NO *fim;
    int tamanho;
};


NO *deque_criar_no(ITEM *item){

    NO *novoNo = malloc(sizeof(NO));

    if(novoNo != NULL){
        novoNo->item = item;
        novoNo->proximo = NULL;
    }

    return(novoNo);
}


DEQUE *deque_criar(void){

    DEQUE *novaDeque = malloc(sizeof(DEQUE));

    if(novaDeque != NULL){
        novaDeque->cabeca = deque_criar_no(NULL);
        novaDeque->cabeca->proximo = novaDeque->cabeca;
        novaDeque->fim = novaDeque->cabeca;
        novaDeque->tamanho = 0;
    }

    return(novaDeque);
}


bool deque_apagar(DEQUE **deque){

    if(*deque == NULL)
        return(False);

    NO *noAtual = (*deque)->cabeca->proximo;

    while(noAtual != (*deque)->cabeca){
        NO *proximo = noAtual->proximo;
        item_apagar(&noAtual->item);
        free(noAtual);
        noAtual = proximo;
    }

    free((*deque)->cabeca);
    free(*deque);
    *deque = NULL;

    return(True);
}


bool deque_inserir_inicio(DEQUE *deque, ITEM *item){

    if(deque == NULL || item == NULL || deque_cheia(deque))
        return(False);

    NO *novoNo = deque_criar_no(item);

    if(deque->tamanho == 0)
        deque->fim = novoNo;

    novoNo->proximo = deque->cabeca->proximo;
    deque->cabeca->proximo = novoNo;
    deque->tamanho += 1;

    return(True);
}


bool deque_inserir_fim(DEQUE *deque, ITEM *item){

    if(deque == NULL || item == NULL || deque_cheia(deque))
        return(False);

    NO *novoNo = deque_criar_no(item);

    if(deque->tamanho == 0)
        deque->cabeca->proximo = novoNo;
    else
        deque->fim->proximo = novoNo;

    novoNo->proximo = deque->cabeca;
    deque->fim = novoNo; 
    deque->tamanho += 1;

    return(True);
}


bool deque_remover_inicio(DEQUE *deque){

    if(deque == NULL || deque_vazia(deque))
        return(False);

    NO *noRemovido = deque->cabeca->proximo;
    ITEM *itemRemovido = noRemovido->item;

    deque->cabeca->proximo = noRemovido->proximo;

    item_apagar(&itemRemovido);
    free(noRemovido);

    deque->tamanho -= 1;

    return(True);
}


bool deque_remover_fim(DEQUE *deque){


    if(deque == NULL || deque_vazia(deque))
        return(False);

    NO *noAtual = deque->cabeca->proximo;

    while(noAtual->proximo != deque->fim) 
        noAtual = noAtual->proximo;

    /* Esse trecho de código (while) poderia ser omitido se cada nó possuisse duplo encadeamento,
    fazendo com que a complexidade de tempo da função passasse a ser de O(1) em vez de O(n). Entretanto, isso gastaria mais memória (por ter que armazenar também um ponteiro para cada nó 
    anterior). A escolha porpriorizar tempo ou memória varia conforme cada problema */

    noAtual->proximo = deque->cabeca; 

    NO *noRemovido = deque->fim;
    ITEM *itemRemovido = noRemovido->item;

    item_apagar(&itemRemovido);
    free(noRemovido);

    deque->fim = noAtual;
    deque->tamanho -= 1;

    return(True);
}


ITEM *deque_inicio(DEQUE *deque){

    if(deque == NULL || deque_vazia(deque))
        return(NULL);
    
    return(deque->cabeca->proximo->item);
}


bool deque_cheia(DEQUE *deque){

    NO *noTeste = deque_criar_no(NULL);

    if(noTeste == NULL)
        return(True);

    free(noTeste);
    return(False);
}


bool deque_vazia(DEQUE *deque){
    return(deque_tamanho(deque) == 0);
}


int deque_tamanho(DEQUE *deque){
    return((deque != NULL) ? deque->tamanho : -1);
}


void deque_imprimir(DEQUE *deque){

    NO *noAtual = deque->cabeca->proximo;

    printf("INÍCIO: ");
    while(noAtual != deque->cabeca){
        item_imprimir(noAtual->item);
        noAtual = noAtual->proximo;
    }
    printf("FIM\n");
}