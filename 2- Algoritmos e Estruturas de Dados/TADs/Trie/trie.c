#include "trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_ALFABETO 26

typedef struct no_ NO;

struct no_{
    NO *filhos[TAM_ALFABETO];
    ITEM *item;
};

struct trie_{
    NO *raiz;
    int tamanho;
};


NO *trie_criar_no(void){

    NO *noNovo = malloc(sizeof(NO));

    if(noNovo != NULL){
        for(int i = 0; i < TAM_ALFABETO; i++)
            noNovo->filhos[i] = NULL;
        noNovo->item = NULL;
    }

    return(noNovo);
}


TRIE *trie_criar(void){

    TRIE *novaTrie = malloc(sizeof(TRIE));

    if(novaTrie != NULL){
        novaTrie->raiz = trie_criar_no();
        novaTrie->tamanho = 0;
    }

    return(novaTrie);
}


void trie_apagar_rec(NO *raiz){

    if(raiz == NULL)
        return;
    
    for(int i = 0; i < TAM_ALFABETO; i++)
        trie_apagar_rec(raiz->filhos[i]);
    
    item_apagar(&raiz->item);
    free(raiz);
}


bool trie_apagar(TRIE **trie){

    if(*trie != NULL){
        trie_apagar_rec((*trie)->raiz);
        free(*trie);
        *trie = NULL;
        return(True);
    }

    return(False);
}


bool trie_validar_chave(char *chave){

    int tamChave = strlen(chave);
    
    for(int i = 0; i < tamChave; i++){
        if(chave[i] < 'a' || chave[i] > 'z'){
            fprintf(stderr, "A chave possui um ou mais caracteres inválidos!\n");
            fprintf(stderr, "ATENCAO: usar apenas valores ASCII no intervalo [97-122]\n");
            return(False);
        }
    }

    return((tamChave > 0) ? True : False);
}


bool trie_inserir_aux(TRIE *trie, ITEM *item){

    char *chave = item_obter_chave(item);
    int tamChave = strlen(chave);
    NO *noAtual = trie->raiz;

    if(strlen(chave) == 0)
        return(False);

    for(int i = 0; i < tamChave; i++){
        int posFilho = chave[i] - 'a';
        if(noAtual->filhos[posFilho] == NULL)
            noAtual->filhos[posFilho] = trie_criar_no();
        noAtual = noAtual->filhos[posFilho];
    }

    if(noAtual->item != NULL)
        return(False);

    noAtual->item = item;
    trie->tamanho += 1;

    return(True);
}


bool trie_inserir(TRIE *trie, ITEM *item){

    if(trie != NULL && item != NULL && !trie_cheia(trie) && trie_validar_chave(item_obter_chave(item)))
        return(trie_inserir_aux(trie, item));
    
    return(False);
}


bool trie_no_sem_filhos(NO *raiz){

    if(raiz != NULL){
        for(int i = 0; i < TAM_ALFABETO; i++)
            if(raiz->filhos[i] != NULL)
                return(False);
    }

    return(True);
}


NO *trie_remover_rec(TRIE *trie, NO *raiz, char *chave, int tamChave, int profundidade){

    if(raiz == NULL)
        return(NULL);
    
    if(profundidade == tamChave){
        if(raiz->item != NULL){
            item_apagar(&raiz->item);
            raiz->item = NULL;
            trie->tamanho -= 1;
        }
        if(trie_no_sem_filhos(raiz)){
            free(raiz);
            raiz = NULL;
        }
        return(raiz);
    }

    int posFilho = chave[profundidade] - 'a';
    raiz->filhos[posFilho] = trie_remover_rec(trie, raiz->filhos[posFilho], chave, tamChave, profundidade + 1);

    if(trie_no_sem_filhos(raiz) && raiz->item == NULL){
        free(raiz);
        raiz = NULL;
    }

    return(raiz);
}


bool trie_remover(TRIE *trie, char *chave){
    
    if(trie != NULL && chave != NULL && trie_validar_chave(chave)){
        int tamanhoPre = trie->tamanho;
        trie->raiz = trie_remover_rec(trie, trie->raiz, chave, strlen(chave), 0);
        int tamanhoPos = trie->tamanho;
        return((tamanhoPos < tamanhoPre) ? True : False);
    }

    return(False);
}


ITEM *trie_busca_aux(NO *raiz, char *chave){

    if(raiz == NULL)
        return(NULL);

    int tamChave = strlen(chave);
    NO *noAtual = raiz;

    for(int i = 0; i < tamChave; i++){
        int posFilho = chave[i] - 'a';
        if(noAtual->filhos[posFilho] == NULL)
            return(NULL);
        noAtual = noAtual->filhos[posFilho]; 
    }

    return(noAtual->item);
}


ITEM *trie_buscar_item(TRIE *trie, char *chave){
    
    if(trie != NULL && chave != NULL && trie_validar_chave(chave))
        return(trie_busca_aux(trie->raiz, chave));

    return(NULL);
}


void trie_imprimir_rec(NO *raiz){

    if(raiz == NULL)
        return;
    
    for(int i = 0; i < TAM_ALFABETO; i++)
        trie_imprimir_rec(raiz->filhos[i]);
    
    if(raiz->item != NULL)
        item_imprimir(raiz->item);
}


void trie_imprimir(TRIE *trie){

    if(trie != NULL)
        trie_imprimir_rec(trie->raiz);

    printf("\n");
}


bool trie_cheia(TRIE *trie){

    NO *noTeste = trie_criar_no();

    if(noTeste == NULL)
        return(True);
    
    free(noTeste);

    return(False);
}


bool trie_vazia(TRIE *trie){
    return(trie_tamanho(trie) == 0);
}


int trie_tamanho(TRIE *trie){
    return((trie != NULL) ? trie->tamanho : -1);
}