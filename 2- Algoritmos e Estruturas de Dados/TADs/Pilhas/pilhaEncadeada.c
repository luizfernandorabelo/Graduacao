#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *proximo;
};

struct pilha_{
    NO *topo;
    int tamanho;
};


NO *pilha_criar_no(ITEM *item){

    NO *novoNo = malloc(sizeof(NO));

    if(novoNo != NULL){
        novoNo->item = item;
        novoNo->proximo = NULL;
    }

    return(novoNo);
}


PILHA *pilha_criar(void){
    
    PILHA *novaPilha = malloc(sizeof(PILHA));
    
    if(novaPilha != NULL){
        novaPilha->topo = NULL;
        novaPilha->tamanho = 0;
    }

    return(novaPilha);
}


void pilha_apagar_nos(NO **no){

    if((*no)->proximo != NULL)
        pilha_apagar_nos(&(*no)->proximo);

    item_apagar(&(*no)->item);
    free(*no);
    *no = NULL;
}


bool pilha_apagar(PILHA **pilha){

    if(*pilha != NULL){
        if(pilha_tamanho(*pilha) > 0)
            pilha_apagar_nos(&(*pilha)->topo);
        free(*pilha);
        *pilha = NULL;
        return(True);
    }

    return(False);
}


bool pilha_empilhar(PILHA *pilha, ITEM *item){

    if(pilha != NULL && item != NULL && !pilha_cheia(pilha)){
        NO *novoNo = pilha_criar_no(item);
        novoNo->proximo = pilha->topo;
        pilha->topo = novoNo;
        pilha->tamanho += 1;
        return(True);
    }

    return(False);
}


bool pilha_desempilhar(PILHA *pilha){

    if(pilha != NULL && pilha->topo != NULL){
        NO *proximo = pilha->topo->proximo;
        item_apagar(&pilha->topo->item);
        free(pilha->topo);
        pilha->topo = proximo;
        pilha->tamanho -= 1;
        return(True);
    }

    return(False);
}


ITEM *pilha_topo(PILHA *pilha){

    if(pilha != NULL && pilha->topo != NULL)
        return(pilha->topo->item);
    
    return(NULL);
}


void pilha_imprimir(PILHA *pilha){

    if(pilha != NULL){
        NO *noAtual = pilha->topo;
        while(noAtual != NULL){
            printf("%d\n", item_obter_chave(noAtual->item));
            noAtual = noAtual->proximo;
        }
    }
}


bool pilha_cheia(PILHA *pilha){

    NO *noTeste = pilha_criar_no(NULL);

    if(noTeste == NULL)
        return(True);
    
    free(noTeste);
    return(False);
}


bool pilha_vazia(PILHA *pilha){
    return(pilha_tamanho(pilha) == 0);    
}

int pilha_tamanho(PILHA *pilha){
    return((pilha != NULL) ? pilha->tamanho : 0);
}