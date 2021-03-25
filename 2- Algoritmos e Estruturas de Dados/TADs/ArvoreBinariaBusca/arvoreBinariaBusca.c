#include "arvoreBinariaBusca.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *filhoEsquerda;
    NO *filhoDireita;
};

struct abb_{
    NO *raiz;
    int tamanho;
};


NO *arvore_criar_no(ITEM *item){

    NO *novoNo = malloc(sizeof(NO));

    if(novoNo != NULL){
        novoNo->item = item;
        novoNo->filhoEsquerda = NULL;
        novoNo->filhoDireita = NULL;
    }

    return(novoNo);
}


ABB *arvore_criar(void){

    ABB *novaArvore = malloc(sizeof(ABB));

    if(novaArvore != NULL){
        novaArvore->raiz = NULL;
        novaArvore->tamanho = 0;
    }

    return(novaArvore);
}


void arvore_apagar_rec(NO *raiz){

    if(raiz == NULL)
        return;
    
    arvore_apagar_rec(raiz->filhoEsquerda);
    arvore_apagar_rec(raiz->filhoDireita);

    item_apagar(&raiz->item);
    free(raiz);
}


bool arvore_apagar(ABB **arvore){

    if(*arvore != NULL){
        arvore_apagar_rec((*arvore)->raiz);
        free(*arvore);
        *arvore = NULL;
        return(True);
    }

    return(False);
}


NO *arvore_buscar_no(NO *raiz, int chave){

    if(raiz == NULL)
        return(NULL);

    if((item_obter_chave(raiz->item) == chave))
        return(raiz);

    if(chave < item_obter_chave(raiz->item))
        return(arvore_buscar_no(raiz->filhoEsquerda, chave));

    return(arvore_buscar_no(raiz->filhoDireita, chave));
}


ITEM *arvore_buscar(ABB *arvore, int chave){

    if(arvore != NULL){
        NO *noBuscado = arvore_buscar_no(arvore->raiz, chave);
        if(noBuscado != NULL)
            return(noBuscado->item);
    }

    return(NULL);
}


NO *arvore_inserir_rec(ABB *arvore, NO *raiz, ITEM *item){

    if(raiz == NULL){
        arvore->tamanho += 1;
        return(arvore_criar_no(item));
    }

    if(item_obter_chave(item) < item_obter_chave(raiz->item))
        raiz->filhoEsquerda = arvore_inserir_rec(arvore, raiz->filhoEsquerda, item);

    else if(item_obter_chave(item) > item_obter_chave(raiz->item))
        raiz->filhoDireita = arvore_inserir_rec(arvore, raiz->filhoDireita, item);

    return(raiz);
}


bool arvore_inserir(ABB *arvore, ITEM *item){

    if(arvore == NULL || item == NULL)
        return(False);

    int tamahoPre = arvore->tamanho;
    arvore->raiz = arvore_inserir_rec(arvore, arvore->raiz, item);
    int tamanhoPos = arvore->tamanho;

    return((tamanhoPos - tamahoPre) == 1);
}


void troca_max_esquerda(NO *raiz, NO *noAnterior, NO *noAtual){

    if(noAtual->filhoDireita == NULL){
        item_apagar(&raiz->item);
        raiz->item = noAtual->item;
        if(noAnterior == raiz)
            raiz->filhoEsquerda = noAtual->filhoEsquerda;
        else
            noAnterior->filhoDireita = noAtual->filhoEsquerda;
        free(noAtual);
        noAtual = NULL;
        return;
    }
    
    troca_max_esquerda(raiz, noAtual, noAtual->filhoDireita);
}


bool arvore_remover(ABB *arvore, int chave){

    if(arvore == NULL)
        return(False);
    
    NO *noAtual = arvore->raiz;

    // Procurando o nó que deve ser removido:
    while(noAtual != NULL){
        if(item_obter_chave(noAtual->item) == chave) 
            break;
        noAtual = (chave < item_obter_chave(noAtual->item)) ? noAtual->filhoEsquerda : noAtual->filhoDireita;
    }

    if(noAtual == NULL) 
        return(False);

    if(noAtual->filhoEsquerda == NULL || noAtual->filhoDireita == NULL){ // noAtual tem 1 ou 0 filhos
        item_apagar(&noAtual->item);
        if(noAtual->filhoEsquerda == NULL){
            NO *removido = noAtual->filhoDireita;
            *noAtual = *(noAtual->filhoDireita);
            if(removido != NULL)
                free(removido);
        }
        else{
            NO *removido = noAtual->filhoEsquerda;
            *noAtual = *(noAtual->filhoEsquerda);
            if(removido != NULL)
                free(removido);
        }
    }
    else // noAtual tem os 2 filhos
        troca_max_esquerda(noAtual, noAtual, noAtual->filhoEsquerda);
    
    arvore->tamanho -= 1;

    return(True);
}


void arvore_imprimir_rec(NO *raiz){

    if(raiz == NULL)
        return;

    item_imprimir(raiz->item);

    bool noFolha = (raiz->filhoEsquerda == NULL && raiz->filhoDireita == NULL) ? True : False;

    if(noFolha == False) printf("[");
    arvore_imprimir_rec(raiz->filhoEsquerda);
    if(noFolha == False) printf(",");
    arvore_imprimir_rec(raiz->filhoDireita);
    if(noFolha == False) printf("]");
}


void arvore_imprimir(ABB *arvore){

    if(arvore != NULL)
        arvore_imprimir_rec(arvore->raiz);

    printf("\n");
}


void arvore_percorrer_preordem_rec(NO *raiz){

    if(raiz == NULL)
        return;

    printf("%d; ", item_obter_chave(raiz->item));
    arvore_percorrer_preordem_rec(raiz->filhoEsquerda);
    arvore_percorrer_preordem_rec(raiz->filhoDireita);
}


void arvore_percorrer_preordem(ABB *arvore){
    printf("Pre ordem: ");
    if(arvore != NULL)
        arvore_percorrer_preordem_rec(arvore->raiz);    
    printf("\n");
}


void arvore_percorrer_emordem_rec(NO *raiz){

    if(raiz == NULL)
        return;

    arvore_percorrer_emordem_rec(raiz->filhoEsquerda);
    printf("%d; ", item_obter_chave(raiz->item));
    arvore_percorrer_emordem_rec(raiz->filhoDireita);
}


void arvore_percorrer_emordem(ABB *arvore){
    printf("Em ordem: ");
    if(arvore != NULL)
        arvore_percorrer_emordem_rec(arvore->raiz);    
    printf("\n");
}


void arvore_percorrer_posordem_rec(NO *raiz){

    if(raiz == NULL)
        return;

    arvore_percorrer_posordem_rec(raiz->filhoEsquerda);
    arvore_percorrer_posordem_rec(raiz->filhoDireita);
    printf("%d; ", item_obter_chave(raiz->item));
}


void arvore_percorrer_posordem(ABB *arvore){
    printf("Pos ordem: ");
    if(arvore != NULL)
        arvore_percorrer_posordem_rec(arvore->raiz);    
    printf("\n");
}


bool arvore_cheia(ABB *arvore){

    NO *noTeste = arvore_criar_no(NULL);

    if(noTeste == NULL)
        return(True);
    
    free(noTeste);

    return(False);
}


bool arvore_vazia(ABB *arvore){
    return(arvore_tamanho(arvore) == 0);
}


int arvore_tamanho(ABB *arvore){
    return((arvore != NULL) ? arvore->tamanho : -1);
}