#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

#define A 0
#define B 1 
#define C 2


typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *proximo;
};

struct pilha_{
    NO *topo;
    int tamanho;
    char id;
};


NO *pilha_criar_no(ITEM *item){

    NO *novoNo = malloc(sizeof(NO));

    if(novoNo != NULL){
        novoNo->item = item;
        novoNo->proximo = NULL;
    }

    return(novoNo);
}


PILHA *pilha_criar(char id){
    
    PILHA *novaPilha = malloc(sizeof(PILHA));
    
    if(novaPilha != NULL){
        novaPilha->topo = NULL;
        novaPilha->tamanho = 0;
        novaPilha->id = id;
    }

    return(novaPilha);
}


void pilha_apagar_nos(NO **no){

    if((*no)->proximo != NULL)
        pilha_apagar_nos(&(*no)->proximo);

    item_apagar(&(*no)->item);
    free(*no);
    *no = NULL;
}


bool pilha_apagar(PILHA **pilha){

    if(*pilha != NULL){
        if((*pilha)->topo != NULL)
            pilha_apagar_nos(&(*pilha)->topo);
        free(*pilha);
        *pilha = NULL;
        return(True);
    }

    return(False);
}


bool pilha_empilhar(PILHA *pilha, ITEM *item){

    if(pilha != NULL && item != NULL){
        NO *novoNo = pilha_criar_no(item);
        novoNo->proximo = pilha->topo;
        pilha->topo = novoNo;
        pilha->tamanho += 1;
        return(True);
    }

    return(False);
}


bool pilha_desempilhar(PILHA *pilha){

    if(pilha != NULL && pilha->topo != NULL){
        NO *proximo = pilha->topo->proximo;
        item_apagar(&pilha->topo->item);
        free(pilha->topo);
        pilha->topo = proximo;
        pilha->tamanho -= 1;
        return(True);
    }

    return(False);
}


ITEM *pilha_topo(PILHA *pilha){

    if(pilha != NULL && pilha->topo != NULL)
        return(pilha->topo->item);
    
    return(NULL);
}


bool pilha_cheia(PILHA *pilha){

    NO *noTeste = pilha_criar_no(NULL);

    if(noTeste == NULL)
        return(True);
    
    free(noTeste);

    return(False);
}


void pilha_hanoi_empilhar_origem(PILHA *origem, int nDiscos){

    for(int i = nDiscos; i > 0; i--)
        pilha_empilhar(origem, item_criar(i));
}


void pilha_hanoi_imprimir(PILHA **arrayPilhas, int nDiscos, FILE *fp){
    
    for(int i = 0; i < 3; i++){
        fprintf(fp, "\nPilha %c:\n", arrayPilhas[i]->id);
        NO *noAtual = arrayPilhas[i]->topo;
        while(noAtual != NULL){
            int chaveAtual = item_obter_chave(noAtual->item);
            for(int i = 0; i < chaveAtual * 2; i++)
                fprintf(fp, "_");
            fprintf(fp, "\n");
            noAtual = noAtual->proximo;
        }
        fprintf(fp, "\n");
    }
}


void pilha_hanoi_rec(PILHA **arrayPilhas, int indiceOrigem, int indiceIntermediaria, int indiceDestino, int nDiscos, FILE *fp){

    if(nDiscos == 1){
        NO *noTopo = arrayPilhas[indiceOrigem]->topo;
        NO *proximo = noTopo->proximo;
        ITEM *itemMovido = noTopo->item;
        arrayPilhas[indiceOrigem]->topo = proximo;
        free(noTopo); 
        pilha_empilhar(arrayPilhas[indiceDestino], itemMovido);
        fprintf(fp, "\n\n1 disco movido de %c para %c\n", arrayPilhas[indiceOrigem]->id, arrayPilhas[indiceDestino]->id);
        pilha_hanoi_imprimir(arrayPilhas, nDiscos, fp);
        return;
    }

    pilha_hanoi_rec(arrayPilhas, indiceOrigem, indiceDestino, indiceIntermediaria, nDiscos - 1, fp);
    pilha_hanoi_rec(arrayPilhas, indiceOrigem, indiceIntermediaria, indiceDestino, 1, fp);
    pilha_hanoi_rec(arrayPilhas, indiceIntermediaria, indiceOrigem, indiceDestino, nDiscos - 1, fp);
}


void pilha_hanoi(PILHA **arrayPilhas, int nDiscos, FILE *fp){

    pilha_hanoi_empilhar_origem(arrayPilhas[0], nDiscos);
    pilha_hanoi_imprimir(arrayPilhas, nDiscos, fp);
    pilha_hanoi_rec(arrayPilhas, A, B, C, nDiscos, fp);
}