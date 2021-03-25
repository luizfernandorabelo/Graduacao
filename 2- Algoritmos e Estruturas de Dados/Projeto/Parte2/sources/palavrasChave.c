#include "palavrasChave.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_ALFABETO 26


typedef struct no_ NO;

struct no_{
    NO *filhos[TAM_ALFABETO];
    CODIGOS *codigosRelacionados;
};

struct palavras_chave_{
    NO *raiz;
    int tamanho;
};


NO *palavras_chave_criar_no(void){

    NO *noNovo = malloc(sizeof(NO));

    if(noNovo != NULL){
        for(int i = 0; i < TAM_ALFABETO; i++)
            noNovo->filhos[i] = NULL;
        noNovo->codigosRelacionados = NULL;
    }

    return(noNovo);
}


PALAVRAS_CHAVE *palavras_chave_criar(void){

    PALAVRAS_CHAVE *palavrasChave = malloc(sizeof(PALAVRAS_CHAVE));

    if(palavrasChave != NULL){
        palavrasChave->raiz = palavras_chave_criar_no();
        palavrasChave->tamanho = 0;
    }

    return(palavrasChave);
}


void palavras_chave_apagar_codigos_relacionados(CODIGOS *codigosRelacionados){

    if(codigosRelacionados == NULL)
        return;

    free(codigosRelacionados->codigos);
    free(codigosRelacionados);    
}


void palavras_chave_apagar_rec(NO *raiz){

    if(raiz == NULL)
        return;
    
    for(int i = 0; i < TAM_ALFABETO; i++)
        palavras_chave_apagar_rec(raiz->filhos[i]);

    palavras_chave_apagar_codigos_relacionados(raiz->codigosRelacionados); 
    free(raiz);
}


boolean palavras_chave_apagar(PALAVRAS_CHAVE **palavrasChave){

    if(*palavrasChave != NULL){
        palavras_chave_apagar_rec((*palavrasChave)->raiz);
        free(*palavrasChave);
        *palavrasChave = NULL;
        return(TRUE);
    }

    return(FALSE);
}


boolean palavras_chave_cheia(PALAVRAS_CHAVE *palavras_chave){

    NO *noTeste = palavras_chave_criar_no();

    if(noTeste == NULL)
        return(TRUE);
    
    free(noTeste);

    return(FALSE);
}


int palavras_chave_tamanho(PALAVRAS_CHAVE *palavras_chave){
    return((palavras_chave != NULL) ? palavras_chave->tamanho : -1);
}


boolean palavras_chave_vazia(PALAVRAS_CHAVE *palavras_chave){
    return(palavras_chave_tamanho(palavras_chave) == 0);
}


boolean palavras_chave_validar_chave(char *chave){

    int tamChave = strlen(chave);
    
    for(int i = 0; i < tamChave; i++){
        if(chave[i] < 'a' || chave[i] > 'z'){
            fprintf(stderr, "A chave possui um ou mais caracteres inválidos!\n");
            fprintf(stderr, "ATENCAO: usar apenas valores ASCII no intervalo [97-122]\n");
            return(FALSE);
        }
    }

    return((tamChave > 0) ? TRUE : FALSE);
}


boolean palavras_chave_inserir_aux(PALAVRAS_CHAVE *palavrasChave, char *chave, int codigoSite){

    int tamChave = strlen(chave);
    NO *noAtual = palavrasChave->raiz;

    for(int i = 0; i < tamChave; i++){
        int posFilho = chave[i] - 'a';
        if(noAtual->filhos[posFilho] == NULL)
            noAtual->filhos[posFilho] = palavras_chave_criar_no();
        noAtual = noAtual->filhos[posFilho];
    }

    if(noAtual->codigosRelacionados == NULL){ 
        noAtual->codigosRelacionados = malloc(sizeof(CODIGOS));
        noAtual->codigosRelacionados->codigos = NULL;
        noAtual->codigosRelacionados->quantidade = 0;
    }

    noAtual->codigosRelacionados->codigos = realloc(noAtual->codigosRelacionados->codigos, 
                                            (noAtual->codigosRelacionados->quantidade + 1) * sizeof(int));
    noAtual->codigosRelacionados->codigos[noAtual->codigosRelacionados->quantidade] = codigoSite;

    noAtual->codigosRelacionados->quantidade += 1;
    palavrasChave->tamanho += 1;

    return(TRUE);
}


boolean palavras_chave_inserir(PALAVRAS_CHAVE *palavrasChave, char *chave, int codigoSite){

    if(palavrasChave != NULL && chave != NULL && !palavras_chave_cheia(palavrasChave) && palavras_chave_validar_chave(chave))
        return(palavras_chave_inserir_aux(palavrasChave, chave, codigoSite));
    
    return(FALSE);
}


boolean palavras_chave_no_sem_filhos(NO *raiz){

    if(raiz != NULL){
        for(int i = 0; i < TAM_ALFABETO; i++)
            if(raiz->filhos[i] != NULL)
                return(FALSE);
    }

    return(TRUE);
}


int palavras_chave_buscar_indice_relacionado(CODIGOS *relacinados, int codigoBuscado){

    int total = relacinados->quantidade;

    for(int i = 0; i < total; i++){
        if(relacinados->codigos[i] == codigoBuscado) 
            return(i);
    } 

    return(-1);
}


NO *palavras_chave_remover_rec(PALAVRAS_CHAVE *pChave, NO *raiz, char *chave, int tamChave, int codigoSite, int profundidade){

    if(raiz == NULL)
        return(NULL);
    
    if(profundidade == tamChave){
        if(raiz->codigosRelacionados != NULL){
            int indiceRemovido = palavras_chave_buscar_indice_relacionado(raiz->codigosRelacionados, codigoSite);
            if(indiceRemovido != -1){
                printf("Codigo encontrado\n");
                int totalRelacionados = raiz->codigosRelacionados->quantidade;
                for(int i = indiceRemovido; i < totalRelacionados - 1; i++)
                    raiz->codigosRelacionados->codigos[i] = raiz->codigosRelacionados->codigos[i+1];
                raiz->codigosRelacionados->codigos = realloc(raiz->codigosRelacionados->codigos,
                                                            (totalRelacionados - 1) * sizeof(int));
                raiz->codigosRelacionados->quantidade -= 1;
            }
            if(raiz->codigosRelacionados->quantidade == 0){
                free(raiz->codigosRelacionados);                
                raiz->codigosRelacionados = NULL;
            }
            pChave->tamanho -= 1;
        }
        if(palavras_chave_no_sem_filhos(raiz) && raiz->codigosRelacionados == NULL){
            free(raiz);
            raiz = NULL;
        }
        return(raiz);
    }

    int posFilho = chave[profundidade] - 'a';
    raiz->filhos[posFilho] = palavras_chave_remover_rec(pChave, raiz->filhos[posFilho], chave, tamChave, codigoSite, profundidade + 1);

    if(palavras_chave_no_sem_filhos(raiz) && raiz->codigosRelacionados == NULL){
        free(raiz);
        raiz = NULL;
    }

    return(raiz);
}


boolean palavras_chave_remover(PALAVRAS_CHAVE *palavrasChave, char *chave, int codigoSite){
    
    if(palavrasChave != NULL && chave != NULL && palavras_chave_validar_chave(chave)){
        int tamanhoPre = palavrasChave->tamanho;
        palavrasChave->raiz = palavras_chave_remover_rec(palavrasChave, palavrasChave->raiz, chave, strlen(chave), codigoSite, 0);
        int tamanhoPos = palavrasChave->tamanho;
        return((tamanhoPos < tamanhoPre) ? TRUE : FALSE);
    }

    return(FALSE);
}


CODIGOS *palavras_chave_busca_aux(NO *raiz, char *chave){

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

    return(noAtual->codigosRelacionados);
}


CODIGOS *palavras_chave_buscar_codigos_relacionados(PALAVRAS_CHAVE *palavras_chave, char *chave){
    
    if(palavras_chave != NULL && chave != NULL && palavras_chave_validar_chave(chave))
        return(palavras_chave_busca_aux(palavras_chave->raiz, chave));

    return(NULL);
}