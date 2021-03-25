#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct no_ NO;

struct no_{
    ABA *aba;
    NO *anterior;
    NO *proximo;    
};

struct lista_{
    NO *inicio;
    NO *fim;
    int tamanho;
};


NO *lista_criar_no(ABA *aba){
    
    NO *novoNo = malloc(sizeof(NO));
    
    if(novoNo != NULL){
        novoNo->aba = aba;
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


bool lista_inserir(LISTA *lista, ABA *aba){

    if(lista == NULL || aba == NULL || lista_cheia(lista))
        return(False);

    NO *noNovo = lista_criar_no(aba);

    if(lista->tamanho == 0) 
        lista->inicio = noNovo;
    else{
        noNovo->anterior = lista->fim;
        lista->fim->proximo = noNovo;
    }

    lista->fim = noNovo;
    lista->tamanho += 1;

    return(True);
}


NO *lista_buscar_no(LISTA *lista, char *tituloAba){

    if(lista == NULL)
        return(NULL);

    NO *noAtual = lista->inicio;
    
    while(noAtual != lista->fim->proximo){
        if(strcmp(tituloAba, aba_get_titulo(noAtual->aba)) == 0) 
            return(noAtual);
        noAtual = noAtual->proximo;
    }

    return(NULL);
}


void lista_inserir_posicao(LISTA *lista, ABA *abaAlterada, int posicaoDestino){

    int posicaoAtual = 1;
    NO *noAtual = lista->inicio;
    NO *novoNo = lista_criar_no(abaAlterada);

    while(noAtual->proximo != NULL && posicaoAtual < posicaoDestino){
        posicaoAtual += 1;
        noAtual = noAtual->proximo;
    }

    if(posicaoAtual == 1){
        novoNo->proximo = lista->inicio;
        lista->inicio->anterior = novoNo;
        lista->inicio = novoNo;
    }
    else if(noAtual->proximo == NULL && posicaoAtual != posicaoDestino){
        noAtual->proximo = novoNo;
        novoNo->anterior = noAtual;
        lista->fim = novoNo;
    }
    else{
        novoNo->proximo = noAtual;
        novoNo->anterior = noAtual->anterior;
        noAtual->anterior->proximo = novoNo;
        noAtual->anterior = novoNo;
    }        
}


bool lista_alterar_posicao(LISTA *lista, char *tituloAba, int posicaoDestino){

    if(lista == NULL || tituloAba == NULL || posicaoDestino < 1 || lista->tamanho <= 1)
        return(False);
    
    NO *noAlterado = lista_buscar_no(lista, tituloAba);

    if(noAlterado == NULL)
        return(False);
    
    ABA *abaAlterada = noAlterado->aba;

    if(noAlterado == lista->inicio)
        lista->inicio = noAlterado->proximo;
    else
        noAlterado->anterior->proximo = noAlterado->proximo;
    
    if(noAlterado == lista->fim)
        lista->fim = noAlterado->anterior;
    else
        noAlterado->proximo->anterior = noAlterado->anterior;
    
    lista_inserir_posicao(lista, abaAlterada, posicaoDestino);

    return(True);
}


void lista_apagar_nos(NO **no){

    if(*no != NULL){
        lista_apagar_nos(&(*no)->proximo);
        if((*no)->proximo == NULL){
            aba_apagar(&(*no)->aba);
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
        aba_imprimir(noAtual->aba);
        noAtual = noAtual->proximo;
        printf("\n");
    }

    printf("\n");
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