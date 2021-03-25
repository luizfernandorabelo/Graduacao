#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 100


struct pilha_{
    ITEM *itens[TAM_MAX];
    int topo;
};


PILHA *pilha_criar(void){

    PILHA *novaPilha = malloc(sizeof(PILHA));

    if(novaPilha != NULL)
        novaPilha->topo = -1;
    
    return(novaPilha);
}


bool pilha_apagar(PILHA **pilha){

    if(*pilha != NULL){
        for(int i = 0, topo = (*pilha)->topo; i <= topo; i++)
            item_apagar(&(*pilha)->itens[i]);
        free(*pilha);
        *pilha = NULL;
        return(True);
    }

    return(False);
}


bool pilha_empilhar(PILHA *pilha, ITEM *item){

    if(pilha != NULL && item != NULL && !pilha_cheia(pilha)){
        int indiceLivre = pilha->topo + 1;
        pilha->itens[indiceLivre] = item;
        pilha->topo += 1;
        return(True);
    }

    return(False);
}


bool pilha_desempilhar(PILHA *pilha){

    if(pilha != NULL && pilha->topo >= 0){
        item_apagar(&pilha->itens[pilha->topo]);
        pilha->topo -= 1;
        return(True);
    }

    return(False);
}


void pilha_imprimir(PILHA *pilha){

    if(pilha != NULL){
        for(int i = pilha->topo; i >= 0; i--)
            printf("%d\n", item_obter_chave(pilha->itens[i]));
    }
}


ITEM *pilha_topo(PILHA *pilha){

    if(pilha != NULL && pilha->topo >= 0)
        return(pilha->itens[pilha->topo]);
    
    return(NULL);
}


int pilha_tamanho(PILHA *pilha){
    return((pilha != NULL) ? pilha->topo + 1 : 0);
}

bool pilha_cheia(PILHA *pilha){
    return(pilha_tamanho(pilha) == TAM_MAX);
}

bool pilha_vazia(PILHA *pilha){
    return(pilha_tamanho(pilha) == 0);
}