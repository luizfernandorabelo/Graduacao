#include "lista.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *proximo;    
};

struct lista_{
    NO *sentinela;
    NO *fim;
    int tamanho;
};


NO *lista_criar_no(ITEM *item){
    
    NO *novoNo = malloc(sizeof(NO));
    
    if(novoNo != NULL){
        novoNo->item = item;
        novoNo->proximo = NULL;
    }

    return(novoNo);
}


LISTA *lista_criar(void){

    LISTA *novaLista = malloc(sizeof(LISTA));

    if(novaLista != NULL){
        novaLista->sentinela = lista_criar_no(NULL);
        novaLista->sentinela->proximo = novaLista->sentinela;
        novaLista->fim = NULL;
        novaLista->tamanho = 0;
    }

    return(novaLista);
}


bool lista_inserir_ordenado(LISTA *lista, NO *noAtual, ITEM *item){ // Complexidade tempo: O(n)

    NO *noNovo = lista_criar_no(item);

    while(noAtual->proximo != lista->sentinela && item_obter_chave(noAtual->proximo->item) < item_obter_chave(noNovo->item))
        noAtual = noAtual->proximo;
    
    if(noAtual->proximo == lista->sentinela)
        lista->fim = noNovo;
        
    noNovo->proximo = noAtual->proximo;
    noAtual->proximo = noNovo;
    lista->tamanho += 1;
    
    return(True);
}


bool lista_inserir_nao_ordenado(LISTA *lista, ITEM *item){ // Complexidade tempo: O(1)

    NO *noNovo = lista_criar_no(item);

    if(lista->tamanho == 0) // se for o primeiro elemento a ser inserido
        lista->sentinela->proximo = noNovo;
    else
        lista->fim->proximo = noNovo;

    lista->fim = noNovo;
    noNovo->proximo = lista->sentinela;
    lista->tamanho += 1;

    return(True);
}


bool lista_inserir(LISTA *lista, ITEM *item){

    if(lista != NULL && item != NULL && !lista_cheia(lista)){
        #ifdef LISTA_ORDENADA
            return(lista_inserir_ordenado(lista, lista->sentinela, item));
        #endif
        #ifdef LISTA_NAO_ORDENADA
            return(lista_inserir_nao_ordenado(lista, item));
        #endif
        fprintf(stderr, "Falha na inserção de item na lista! Não foi definido no arquivo .h se a lista é ou não ordenada\n");
    }

    return(False);
}


NO *lista_buscar_no_ordenado(LISTA *lista, int chave){ // Complexidade tempo: O(n)

    lista->sentinela->item = item_criar(chave);
    NO *noAtual = lista->sentinela->proximo;
    
    while(item_obter_chave(noAtual->item) < chave)
        noAtual = noAtual->proximo;

    item_apagar(&lista->sentinela->item);

    if(noAtual != lista->sentinela && item_obter_chave(noAtual->item) == chave)
        return(noAtual);
    
    return(NULL);
}


NO *lista_buscar_no_nao_ordenado(LISTA *lista, int chave){ // Complexidade tempo: O(n)

    lista->sentinela->item = item_criar(chave);
    NO *noAtual = lista->sentinela->proximo;

    while(item_obter_chave(noAtual->item) != chave)
        noAtual = noAtual->proximo;
    
    item_apagar(&lista->sentinela->item);

    if(noAtual != lista->sentinela)
        return(noAtual);

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


bool lista_remover_item_ordenado(LISTA *lista, int chave){

    lista->sentinela->item = item_criar(chave);
    NO *noAtual = lista->sentinela;

    while(item_obter_chave(noAtual->proximo->item) < chave)
        noAtual = noAtual->proximo;

    item_apagar(&lista->sentinela->item);

    if(noAtual->proximo != lista->sentinela && item_obter_chave(noAtual->proximo->item) == chave){
        NO *noRemovido = noAtual->proximo;
        noAtual->proximo = noAtual->proximo->proximo;
        item_apagar(&noRemovido->item);
        free(noRemovido); noRemovido = NULL;
        lista->tamanho -= 1;
        return(True);
    }

    return(False);
}


bool lista_remover_item_nao_ordenado(LISTA *lista, int chave){

    lista->sentinela->item = item_criar(chave);
    NO *noAtual = lista->sentinela;

    while(item_obter_chave(noAtual->proximo->item) != chave)
        noAtual = noAtual->proximo;

    item_apagar(&lista->sentinela->item);

    if(noAtual->proximo != lista->sentinela){
        NO *noRemovido = noAtual->proximo;
        if(noRemovido == lista->fim)
            lista->fim = noAtual;
        noAtual->proximo = noAtual->proximo->proximo;
        item_apagar(&noRemovido->item);
        free(noRemovido); noRemovido = NULL;
        lista->tamanho -= 1;
        return(True);
    }

    return(False);
}


bool lista_remover_item(LISTA *lista, int chave){

    if(lista != NULL){
        #ifdef LISTA_ORDENADA
            return(lista_remover_item_ordenado(lista, chave));
        #endif
        #ifdef LISTA_NAO_ORDENADA
            return(lista_remover_item_nao_ordenado(lista, chave));
        #endif
        fprintf(stderr, "Falha na remoção de item na lista! Não foi definido no arquivo .h se a lista é ou não ordenada\n");
    }

    return(False);
}


bool lista_apagar(LISTA **lista){
    
    if(*lista != NULL){
        NO *noAtual = (*lista)->sentinela->proximo;
        while(noAtual != (*lista)->sentinela){
            NO *proximo = noAtual->proximo;
            item_apagar(&noAtual->item);
            free(noAtual);
            noAtual = proximo;
        }
        free((*lista)->sentinela);
        free(*lista); *lista = NULL;
        return(True);
    }

    return(False);
}


void lista_imprimir(LISTA *lista){

    if(lista == NULL) return;

    NO *noAtual = lista->sentinela->proximo;

    while(noAtual != lista->sentinela){
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