#include "lista.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct no_ NO;

struct no_{
    ITEM *item;
    int coluna;
    NO *proximo;    
};

struct lista_{
    NO *inicio;
    int tamanho;
};



int size_of_lista(){
    return(sizeof(LISTA));
}


NO *lista_criar_no(ITEM *item, int coluna){
    
    NO *novoNo = malloc(sizeof(NO));
    
    if(novoNo != NULL){
        novoNo->item = item;
        novoNo->coluna = coluna;
        novoNo->proximo = NULL;
    }

    return(novoNo);
}


LISTA *lista_criar(void){

    LISTA *novaLista = malloc(sizeof(LISTA));

    if(novaLista != NULL){
        novaLista->inicio = NULL;
        novaLista->tamanho = 0;
    }

    return(novaLista);
}


bool lista_inserir(LISTA *lista, ITEM *item, int coluna){

    if(lista == NULL || item == NULL)
        return(False);
    
    NO *noAtual = lista->inicio;
    NO *noAnterior = NULL;
    
    while(noAtual != NULL && noAtual->coluna < coluna){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    if(noAnterior == NULL){ 
        NO *noNovo = lista_criar_no(item, coluna);
        noNovo->proximo = lista->inicio;
        lista->inicio = noNovo;
    }
    else{
        if(noAtual == NULL){ 
            noAtual = lista_criar_no(item, coluna);
            noAnterior->proximo = noAtual;
        }
        else if(noAtual->coluna == coluna){
            item_apagar(&noAtual->item);
            noAtual->item = item;
        }
        else{
            NO *noNovo = lista_criar_no(item, coluna);
            noAnterior->proximo = noNovo;
            noNovo->proximo = noAtual;
        }
    }

    lista->tamanho += 1;

    return(True);
}


NO *lista_buscar_no(LISTA *lista, int coluna){

    if(lista == NULL)
        return(NULL);
    
    NO *noAtual = lista->inicio;

    while(noAtual != NULL){
        if(coluna == noAtual->coluna)
            return(noAtual);
        noAtual = noAtual->proximo;
    }
    
    return(NULL);
}


ITEM *lista_buscar_item(LISTA *lista, int coluna){

    NO *no = lista_buscar_no(lista, coluna);

    return((no != NULL) ? no->item : NULL);
}


bool lista_remover_item(LISTA *lista, int coluna){

    if(lista == NULL)
        return(False);

    NO *noAtual = lista->inicio;
    NO *noAnterior = NULL;

    while(noAtual != NULL && noAtual->coluna < coluna){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    if(noAtual != NULL && noAtual->coluna == coluna){
        if(noAnterior == NULL)
            lista->inicio = lista->inicio->proximo;
        else
            noAnterior->proximo = noAtual->proximo;
        lista->tamanho -= 1;
        item_apagar(&noAtual->item);
        free(noAtual);
        return(True);
    }

    return(False);
}


void lista_apagar_nos(NO **no){

    if(*no != NULL){
        lista_apagar_nos(&(*no)->proximo);
        if((*no)->proximo == NULL){
            item_apagar(&(*no)->item); 
            free(*no); *no = NULL;
        } 
    }
}


bool lista_apagar(LISTA **lista){
    
   if(*lista != NULL){
        lista_apagar_nos(&(*lista)->inicio);
        free(*lista); *lista = NULL;
        return(True);
    }

    return(False);
}


void lista_imprimir(LISTA *lista){

    if(lista == NULL)
        return;

    NO *noAtual = lista->inicio;

    while(noAtual != NULL){
        item_imprimir(noAtual->item);
        noAtual = noAtual->proximo;
    }
}