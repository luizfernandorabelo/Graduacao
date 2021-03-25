#include "avl.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *filhoEsquerda;
    NO *filhoDireita;
    int altura;
};

struct avl_{
    NO *raiz;
    int tamanho;
};


int max(int a, int b){
    return((a >= b) ? a : b);
}


NO *arvore_criar_no(ITEM *item){

    NO *novoNo = malloc(sizeof(NO));

    if(novoNo != NULL){
        novoNo->item = item;
        novoNo->filhoEsquerda = NULL;
        novoNo->filhoDireita = NULL;
        novoNo->altura = 0;
    }

    return(novoNo);
}


int arvore_obter_altura_no(NO *no){
    return((no != NULL) ? no->altura : -1);
}


AVL *arvore_criar(void){

    AVL *novaArvore = malloc(sizeof(AVL));

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


bool arvore_apagar(AVL **arvore){

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


ITEM *arvore_buscar(AVL *arvore, int chave){

    if(arvore != NULL){
        NO *noBuscado = arvore_buscar_no(arvore->raiz, chave);
        if(noBuscado != NULL)
            return(noBuscado->item);
    }

    return(NULL);
}


NO *arvore_rodar_esquerda(NO *raizDesbalanceada){

    NO *novaRaiz = raizDesbalanceada->filhoDireita;
    raizDesbalanceada->filhoDireita = novaRaiz->filhoEsquerda;
    novaRaiz->filhoEsquerda = raizDesbalanceada;

    raizDesbalanceada->altura = max(arvore_obter_altura_no(raizDesbalanceada->filhoEsquerda),
                                    arvore_obter_altura_no(raizDesbalanceada->filhoDireita)) + 1;
    novaRaiz->altura = max(raizDesbalanceada->altura, arvore_obter_altura_no(novaRaiz->filhoDireita)) + 1;

    return(novaRaiz);
}


NO *arvore_rodar_direita(NO *raizDesbalanceada){
    
    NO *novaRaiz = raizDesbalanceada->filhoEsquerda;
    raizDesbalanceada->filhoEsquerda = novaRaiz->filhoDireita;
    novaRaiz->filhoDireita = raizDesbalanceada;

    raizDesbalanceada->altura = max(arvore_obter_altura_no(raizDesbalanceada->filhoEsquerda),
                                    arvore_obter_altura_no(raizDesbalanceada->filhoDireita)) + 1;
    novaRaiz->altura = max(arvore_obter_altura_no(novaRaiz->filhoEsquerda), raizDesbalanceada->altura) + 1;

    return(novaRaiz);
}


NO *arvore_rodar_esquerda_direita(NO *raizDesbalanceada){

    raizDesbalanceada->filhoEsquerda = arvore_rodar_esquerda(raizDesbalanceada->filhoEsquerda);

    return(arvore_rodar_direita(raizDesbalanceada));
}


NO *arvore_rodar_direita_esquerda(NO *raizDesbalanceada){

    raizDesbalanceada->filhoDireita = arvore_rodar_direita(raizDesbalanceada->filhoDireita);

    return(arvore_rodar_esquerda(raizDesbalanceada));
}


NO *arvore_corrigir_balanceamento(NO *raiz){

    if(arvore_obter_altura_no(raiz->filhoEsquerda) - arvore_obter_altura_no(raiz->filhoDireita) == -2){
        if(arvore_obter_altura_no(raiz->filhoDireita->filhoEsquerda) >=
            arvore_obter_altura_no(raiz->filhoDireita->filhoDireita))
            raiz = arvore_rodar_direita_esquerda(raiz);
        else
            raiz = arvore_rodar_esquerda(raiz);
    }
    else if(arvore_obter_altura_no(raiz->filhoEsquerda) - arvore_obter_altura_no(raiz->filhoDireita) == 2){
        if(arvore_obter_altura_no(raiz->filhoEsquerda->filhoEsquerda) <
           arvore_obter_altura_no(raiz->filhoEsquerda->filhoDireita))
            raiz = arvore_rodar_esquerda_direita(raiz);
        else
            raiz = arvore_rodar_direita(raiz);
    }

    return(raiz);
}


NO *arvore_inserir_rec(AVL *arvore, NO *raiz, ITEM *item){

    if(raiz == NULL){
        arvore->tamanho += 1;
        return(arvore_criar_no(item));
    }

    if(item_obter_chave(item) < item_obter_chave(raiz->item))
        raiz->filhoEsquerda = arvore_inserir_rec(arvore, raiz->filhoEsquerda, item);
    else if(item_obter_chave(item) > item_obter_chave(raiz->item))
        raiz->filhoDireita = arvore_inserir_rec(arvore, raiz->filhoDireita, item);

    raiz->altura = max(arvore_obter_altura_no(raiz->filhoEsquerda), arvore_obter_altura_no(raiz->filhoDireita)) + 1;

    raiz = arvore_corrigir_balanceamento(raiz);

    return(raiz);
}


bool arvore_inserir(AVL *arvore, ITEM *item){

    if(arvore == NULL || item == NULL || arvore_cheia(arvore))
        return(False);

    int tamahoPre = arvore->tamanho;
    arvore->raiz = arvore_inserir_rec(arvore, arvore->raiz, item);
    int tamanhoPos = arvore->tamanho;

    return((tamanhoPos - tamahoPre) == 1);
}


void arvore_troca_max_esquerda(NO *raiz, NO *noAnterior, NO *noAtual){

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
    
    arvore_troca_max_esquerda(raiz, noAtual, noAtual->filhoDireita);
}


NO *arvore_remover_rec(AVL *arvore, NO *raiz, int chave){

    if(raiz == NULL)
        return(NULL);
    
    int chaveAtual = item_obter_chave(raiz->item);

    if(chave > chaveAtual) 
        raiz->filhoDireita = arvore_remover_rec(arvore, raiz->filhoDireita, chave);
    else if(chave < chaveAtual) 
        raiz->filhoEsquerda = arvore_remover_rec(arvore, raiz->filhoEsquerda, chave);
    else{ 
        if(raiz->filhoEsquerda == NULL || raiz->filhoDireita == NULL){
            NO *noRemovido = raiz;
            if(raiz->filhoEsquerda == NULL)
                raiz = raiz->filhoDireita;
            else
                raiz = raiz->filhoEsquerda;
            item_apagar(&noRemovido->item);
            free(noRemovido);
            noRemovido = NULL;
        }
        else{
            arvore_troca_max_esquerda(raiz, raiz, raiz->filhoEsquerda);
            if(raiz->filhoEsquerda != NULL)
                raiz->filhoEsquerda = arvore_corrigir_balanceamento(raiz->filhoEsquerda);
        }
        arvore->tamanho -= 1;
    }

    if(raiz != NULL){
        raiz->altura = max(arvore_obter_altura_no(raiz->filhoEsquerda), arvore_obter_altura_no(raiz->filhoDireita)) + 1;
        raiz = arvore_corrigir_balanceamento(raiz);
    }

    return(raiz);
}


bool arvore_remover(AVL *arvore, int chave){

    if(arvore != NULL){
        int tamanhoPre = arvore->tamanho;
        arvore->raiz = arvore_remover_rec(arvore, arvore->raiz, chave);
        int tamanhoPos = arvore->tamanho;
        return((tamanhoPre - tamanhoPos) == 1);
    }

    return(False);
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


void arvore_imprimir(AVL *arvore){

    if(arvore != NULL)
        arvore_imprimir_rec(arvore->raiz);

    printf("\n");
}


bool arvore_cheia(AVL *arvore){

    NO *noTeste = arvore_criar_no(NULL);

    if(noTeste == NULL)
        return(True);
    
    free(noTeste);

    return(False);
}


bool arvore_vazia(AVL *arvore){
    return(arvore_tamanho(arvore) == 0);
}


int arvore_tamanho(AVL *arvore){
    return((arvore != NULL) ? arvore->tamanho : -1);
}