#include "arvoreNaria.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *primeiroFilho;
    NO *proximoIrmao;
};

struct an_{
    NO *raiz;
    int tamanho;
};


NO *arvore_criar_no(ITEM *item){

    NO *noNovo = malloc(sizeof(NO));

    if(noNovo != NULL){
        noNovo->item = item;
        noNovo->primeiroFilho = NULL;
        noNovo->proximoIrmao = NULL;
    }

    return(noNovo);
}


AN *arvore_criar(ITEM *itemRaiz){

    AN *novaArvore = malloc(sizeof(AN));

    if(novaArvore != NULL && itemRaiz != NULL){
        novaArvore->raiz = arvore_criar_no(itemRaiz);
        novaArvore->tamanho = 1;
    }

    return(novaArvore);
}


void arvore_apagar_rec(AN *arvore, NO *raiz){

    if(raiz == NULL) 
        return;

    arvore_apagar_rec(arvore, raiz->primeiroFilho);
    arvore_apagar_rec(arvore, raiz->proximoIrmao);

    item_apagar(&raiz->item);
    free(raiz);
}


bool arvore_apagar(AN **arvore){

    if(*arvore != NULL){
        arvore_apagar_rec(*arvore, (*arvore)->raiz);
        free(*arvore);
        *arvore = NULL;
        return(True);
    }

    return(False);
}


NO *arvore_buscar_no(NO *raiz, int chave){

    if(raiz == NULL)
        return(NULL);
    
    if(item_obter_chave(raiz->item) == chave)
        return(raiz);

    NO *noAtual = raiz->primeiroFilho;

    while(noAtual != NULL){
        NO *aux = arvore_buscar_no(noAtual, chave);
        if(aux != NULL)
            return(aux);
        noAtual = noAtual->proximoIrmao;
    } 

    return(NULL);
}


bool arvore_inserir(AN *arvore, ITEM *item, int chavePai){

    if(arvore == NULL || item == NULL || arvore_cheia(arvore))
        return(False);

    NO *noPai = arvore_buscar_no(arvore->raiz, chavePai);

    if(noPai == NULL){
        fprintf(stderr, "Erro na inserção! Não existe nenhum item de chave %d!\n", chavePai);
        return(False);
    }

    if(noPai->primeiroFilho == NULL)
        noPai->primeiroFilho = arvore_criar_no(item);
    else{
        NO *ultimoFilho = noPai->primeiroFilho;
        while(ultimoFilho->proximoIrmao != NULL)
            ultimoFilho = ultimoFilho->proximoIrmao;
        ultimoFilho->proximoIrmao = arvore_criar_no(item);
    }

    arvore->tamanho += 1;

    return(True);
}


ITEM *arvore_buscar(AN *arvore, int chave){

    NO *noBuscado = arvore_buscar_no(arvore->raiz, chave);

    if(noBuscado != NULL)
        return(noBuscado->item);
    
    return(NULL);
}


void arvore_imprimir_rec(NO *raiz){

    if(raiz == NULL)
        return;
    
    item_imprimir(raiz->item);

    raiz = raiz->primeiroFilho;

    printf("[");
    while(raiz != NULL){
        arvore_imprimir_rec(raiz);
        raiz = raiz->proximoIrmao;
    }
    printf("]");
}


void arvore_imprimir(AN *arvore){

    if(arvore != NULL && arvore->tamanho > 0)
        arvore_imprimir_rec(arvore->raiz);

    printf("\n");
}


bool arvore_cheia(AN *arvore){

    NO *noTeste = arvore_criar_no(NULL);

    if(noTeste == NULL)
        return(True);
    
    free(noTeste);
    
    return(False);
}


bool arvore_vazia(AN *arvore){
    return(arvore_tamanho(arvore) == 0);
}


int arvore_tamanho(AN *arvore){
    return((arvore != NULL) ? arvore->tamanho : -1);
}