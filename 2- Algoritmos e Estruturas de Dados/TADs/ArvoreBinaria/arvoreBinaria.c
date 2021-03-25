#include "arvoreBinaria.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *filhoEsquerda;
    NO *filhoDireita;
};

struct ab_{
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


AB *arvore_criar(void){

    AB *novaArvore = malloc(sizeof(AB));

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


bool arvore_apagar(AB **arvore){

    if(*arvore != NULL){
        arvore_apagar_rec((*arvore)->raiz);
        free(*arvore);
        *arvore = NULL;
        return(True);
    }

    return(False);
}

/* Busca em que o nó encontrado é passado por referência */
void arvore_buscar_no(NO *raiz, int chave, NO **enderecoNoBuscado){

    if(raiz == NULL || *enderecoNoBuscado != NULL)
        return;

    if((item_obter_chave(raiz->item) == chave))
        *enderecoNoBuscado = raiz;
    
    arvore_buscar_no(raiz->filhoEsquerda, chave, enderecoNoBuscado);
    arvore_buscar_no(raiz->filhoDireita, chave, enderecoNoBuscado);
}


ITEM *arvore_buscar(AB *arvore, int chave){

    if(arvore != NULL){
        NO *noBuscado = NULL;
        arvore_buscar_no(arvore->raiz, chave, &noBuscado);
        if(noBuscado != NULL)
            return(noBuscado->item);
    }

    return(NULL);
}


bool arvore_inserir(AB *arvore, ITEM *item, int chavePai, char lado){

    if(arvore == NULL || item == NULL)
        return(False);

    if(arvore->raiz == NULL){
        arvore->raiz = arvore_criar_no(item);
        arvore->tamanho += 1;
        return(True);
    }

    NO *noPai = NULL;

    arvore_buscar_no(arvore->raiz, chavePai, &noPai); // noPai recebe o endereço do no que tem a chave 'chavePai'

    if(noPai != NULL){
        if(lado == ESQUERDA && noPai->filhoEsquerda == NULL){
            noPai->filhoEsquerda = arvore_criar_no(item);
            arvore->tamanho += 1;
            return(True);
        }
        else if(lado == DIREITA && noPai->filhoDireita == NULL){
            noPai->filhoDireita = arvore_criar_no(item);
            arvore->tamanho += 1;
            return(True);
        }
    }

    return(False);
}


/* Apaga um nó, perdendo a referência de seus descendentes */
bool arvore_remover(AB *arvore, int chavePai, char lado){

    if(arvore != NULL){
        NO *noPai = NULL;
        arvore_buscar_no(arvore->raiz, chavePai, &noPai);
        if(noPai != NULL){
            if(lado == ESQUERDA && noPai->filhoEsquerda != NULL){
                item_apagar(&noPai->filhoEsquerda->item);
                free(noPai->filhoEsquerda);
                noPai->filhoEsquerda = NULL;
                return(True);
            }
            else if(lado == DIREITA && noPai->filhoDireita != NULL){
                item_apagar(&noPai->filhoDireita->item);
                free(noPai->filhoDireita);
                noPai->filhoDireita = NULL;
                return(True);
            }
        }
    }

    return(False);
}


void arvore_imprimir_rec(NO *raiz){

    if(raiz == NULL)
        return;

    item_imprimir(raiz->item);

    bool noFolha = (raiz->filhoEsquerda == NULL && raiz->filhoDireita == NULL) ? True : False;

    if(noFolha == False)
        printf("[");
    arvore_imprimir_rec(raiz->filhoEsquerda);
    if(noFolha == False)
        printf(",");
    arvore_imprimir_rec(raiz->filhoDireita);
    if(noFolha == False)
        printf("]");
}


void arvore_imprimir(AB *arvore){

    if(arvore != NULL)
        arvore_imprimir_rec(arvore->raiz);
    printf("\n");
}


bool arvore_cheia(AB *arvore){

    NO *noTeste = arvore_criar_no(NULL);

    if(noTeste == NULL)
        return(True);
    
    free(noTeste);

    return(False);
}


bool arvore_vazia(AB *arvore){
    return(arvore_tamanho(arvore) == 0);
}


int arvore_tamanho(AB *arvore){
    return((arvore != NULL) ? arvore->tamanho : -1);
}