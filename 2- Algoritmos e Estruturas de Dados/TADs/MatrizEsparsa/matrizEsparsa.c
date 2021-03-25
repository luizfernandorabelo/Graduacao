#include "matrizEsparsa.h"
#include "lista.h"

#include <stdio.h>
#include <stdlib.h>


struct matriz_esparsa_{
    LISTA **listas;
    int nLinhas;
    int nColunas;
    int valorPadrao;
};


ME *matriz_criar(int nLinhas, int nColunas, int valorPadrao){

    if(nLinhas < 0 || nColunas < 0){
        fprintf(stderr, "Impossível criar matriz com dimensões negativas\n");
        return(NULL);
    }

    ME *novaMatriz = malloc(sizeof(ME));

    if(novaMatriz != NULL){
        novaMatriz->listas = malloc(nLinhas * size_of_lista());
        for(int i = 0; i < nLinhas; i++)
            novaMatriz->listas[i] = lista_criar();
        novaMatriz->nLinhas = nLinhas;
        novaMatriz->nColunas = nColunas;
        novaMatriz->valorPadrao = valorPadrao;
    }

    return(novaMatriz);
}


bool matriz_apagar(ME **matriz){

    if(*matriz != NULL){
        for(int i = 0, nLinhas = (*matriz)->nLinhas; i < nLinhas; i++)
            lista_apagar(&(*matriz)->listas[i]);
        free((*matriz)->listas);
        free(*matriz);
        *matriz = NULL;
        return(True);
    }

    return(False);
}


bool matriz_inserir(ME *matriz, int linha, int coluna, ITEM *item){

    if(matriz == NULL || linha < 0 || coluna < 0 || linha >= matriz->nLinhas || coluna >= matriz->nColunas)
        return(False);
    
    if(item_obter_chave(item) == matriz->valorPadrao){
        item_apagar(&item);
        return(matriz_remover_item(matriz, linha, coluna));
    }

    return(lista_inserir(matriz->listas[linha], item, coluna));
}


bool matriz_remover_item(ME *matriz, int linha, int coluna){

    if(matriz == NULL || linha < 0 || coluna < 0 || linha >= matriz->nLinhas || coluna >= matriz->nColunas)
        return(False);

    return(lista_remover_item(matriz->listas[linha], coluna));
}


ITEM *matriz_obter_item(ME *matriz, int linha, int coluna){

    if(matriz == NULL || linha < 0 || coluna < 0 || linha >= matriz->nLinhas || coluna >= matriz->nColunas)
        return(False);

    return(lista_buscar_item(matriz->listas[linha], coluna));
}


void matriz_imprimir(ME *matriz){

    if(matriz == NULL)
        return;
    
    int nLinhas = matriz->nLinhas;
    int nColunas = matriz->nColunas;

    for(int i = 0; i < nLinhas; i++){
        for(int j = 0; j < nColunas; j++){
            ITEM *itemAtual = lista_buscar_item(matriz->listas[i], j);
            printf("%.2d ", (itemAtual != NULL) ? item_obter_chave(itemAtual) : matriz->valorPadrao);
        }
        printf("\n");
    }
}