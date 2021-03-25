#include "lista.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *anterior;
    NO *proximo;    
};

struct lista_{
    NO *inicio;
    NO *fim;
    int tamanho;
};


NO *lista_criar_no(ITEM *item){
    
    NO *novoNo = malloc(sizeof(NO));
    
    if(novoNo != NULL){
        novoNo->item = item;
        novoNo->anterior = NULL;
        novoNo->proximo = NULL;
    }

    return(novoNo);
}


LISTA *lista_criar(void){

    LISTA *novaLista = malloc(sizeof(LISTA));

    if(novaLista != NULL){
        novaLista->inicio = NULL;
        novaLista->fim = NULL;
        novaLista->tamanho = 0;
    }

    return(novaLista);
}


bool lista_inserir_ordenado(LISTA *lista, NO *noAtual, ITEM *item){ // Complexidade tempo: O(n)

    if(noAtual != NULL && item_obter_chave(item) > item_obter_chave(noAtual->item))
        return(lista_inserir_ordenado(lista, noAtual->proximo, item));
    
    NO *noNovo = lista_criar_no(item);

    if(lista_tamanho(lista) == 0){ // se for o primeiro elemento a ser inserido 
        lista->inicio = noNovo;
        lista->fim = noNovo;
    }
    else{
        if(noAtual == NULL){ // se a inserção for no fim
            noNovo->anterior = lista->fim;
            lista->fim = noNovo;
        }
        else{
            if(noAtual->anterior == NULL) // se a inserção for no início
                lista->inicio = noNovo;
            else
                noAtual->anterior->proximo = noNovo;    
            noNovo->anterior = noAtual->anterior;
            noAtual->anterior = noNovo;
        }
    }
    
    noNovo->proximo = noAtual;
    lista->tamanho += 1;

    return(True);
}


bool lista_inserir_nao_ordenado(LISTA *lista, ITEM *item){ // Complexidade tempo: O(1)

    NO *noNovo = lista_criar_no(item);

    if(lista->tamanho == 0) // se for o primeiro elemento a ser inserido
        lista->inicio = noNovo;
    else{
        noNovo->anterior = lista->fim;
        lista->fim->proximo = noNovo;
    }

    lista->fim = noNovo;
    lista->tamanho += 1;

    return(True);
}


bool lista_inserir(LISTA *lista, ITEM *item){

    if(lista != NULL && item != NULL && !lista_cheia(lista)){
        #ifdef LISTA_ORDENADA
            return(lista_inserir_ordenado(lista, lista->inicio, item));
        #endif
        #ifdef LISTA_NAO_ORDENADA
            return(lista_inserir_nao_ordenado(lista, item));
        #endif
        fprintf(stderr, "Falha na inserção de item na lista! Não foi definido no arquivo .h se a lista é ou não ordenada\n");
    }

    return(False);
}


NO *lista_buscar_no_ordenado(LISTA *lista, int chave){ // Complexidade tempo: O(n)

    NO *noAtual = lista->inicio;

    while(noAtual != lista->fim->proximo){
        if(chave == item_obter_chave(noAtual->item)) return(noAtual);
        if(chave < item_obter_chave(noAtual->item)) break;
        noAtual = noAtual->proximo;
    }

    return(NULL);
}


NO *lista_buscar_no_nao_ordenado(LISTA *lista, int chave){ // Complexidade tempo: O(n)

    NO *noAtual = lista->inicio;

    while(noAtual != lista->fim->proximo){
        if(chave == item_obter_chave(noAtual->item)) return(noAtual);
        noAtual = noAtual->proximo;
    }

    return(NULL);
}


NO *lista_buscar_no(LISTA *lista, int chave){

    if(lista != NULL){
        #ifdef LISTA_ORDENADA
            return(lista_buscar_no_ordenado(lista, chave));
        #endif
        #ifdef LISTA_NAO_ORDENADA
            return(lista_buscar_no_nao_ordenado(lista, chave));
        #endif
        fprintf(stderr, "Falha na busca de item na lista! Não foi definido no arquivo .h se a lista é ou não ordenada\n");
    }

    return(NULL);
}


ITEM *lista_buscar_item(LISTA *lista, int chave){

    NO *no = lista_buscar_no(lista, chave);

    return((no != NULL) ? no->item : NULL);
}


bool lista_remover_item(LISTA *lista, int chave){

    if(lista == NULL)
        return(False);

    NO *noRemovido = lista_buscar_no(lista, chave);

    if(noRemovido == NULL) // se não for encontrado nenhum item com a chave passada
        return(False);

    if(noRemovido == lista->inicio)
        lista->inicio = lista->inicio->proximo;
    else
        noRemovido->anterior->proximo = noRemovido->proximo;

    if(noRemovido == lista->fim)
        lista->fim = lista->fim->anterior;
    else
        noRemovido->proximo->anterior = noRemovido->anterior;
    
    item_apagar(&noRemovido->item);
    free(noRemovido); noRemovido = NULL;

    lista->tamanho -= 1;

    return(True);
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

    if(lista == NULL) return;

    NO *noAtual = lista->inicio;

    while(noAtual != NULL){
        item_imprimir(noAtual->item);
        noAtual = noAtual->proximo;
    }
}


bool lista_cheia(LISTA *lista){

    NO *noTeste = malloc(sizeof(NO));

    if(noTeste != NULL){
        free(noTeste);
        return(False);
    }

    return(True);
}


bool lista_vazia(LISTA *lista){
    return((lista != NULL) ? lista->tamanho == 0 : False);
}


int lista_tamanho(LISTA *lista){
    return((lista != NULL) ? lista->tamanho : 0);
}