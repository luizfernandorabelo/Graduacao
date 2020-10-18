#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *proximo;
};

struct lista_{
    NO *inicio;
    NO *fim;
    int tamanho;
};

NO *no_criar(ITEM *item){
    NO *no = malloc(sizeof(NO));
    if(no != NULL){
        no->item = item;
        no->proximo = NULL;
    }
    return no;
}

LISTA *lista_criar(){
    LISTA *lista = malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

void lista_apagar_nos(NO **noAtual){
    if(*noAtual == NULL) return;
    lista_apagar_nos(&(*noAtual)->proximo);
    item_apagar(&(*noAtual)->item);
    free(*noAtual);
    *noAtual = NULL;
}

bool lista_apagar(LISTA **lista){
    if(lista == NULL) return False;
    lista_apagar_nos(&(*lista)->inicio);
    free(*lista);
    *lista = NULL;
    return True;
}

bool lista_inserir_fim(LISTA *lista, NO *no){
    if(lista_vazia(lista)){
        lista->inicio = no;
        no->proximo = NULL;
    }
    else{
        lista->fim->proximo = no;
        no->proximo = NULL;
    }
    lista->tamanho += 1;
    lista->fim = no;
    return True;
}

bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL || item == NULL || lista_cheia()) return False;
    NO *no = no_criar(item);
    switch(ORDENADA){
        case False:
            return lista_inserir_fim(lista, no);
        case True:
            break;
        default:
            printf("Definição de ORDENADA no arquivo cabeçalho inválida\n");
            exit(ERRO);
    }
}

bool lista_remover(LISTA *lista, int chave){
    if(lista == NULL) return False;
    NO *noAtual = lista->inicio, *noAnterior = NULL;
    while(noAtual != NULL && item_get_chave(noAtual->item) != chave){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }
    if(noAtual != NULL){
        if(noAtual == lista->inicio) lista->inicio = noAtual->proximo;
        else noAnterior->proximo = noAtual->proximo;
        item_apagar(&noAtual->item);
        free(noAtual);
        noAtual = NULL;
        lista->tamanho -= 1;
        return True;
    }
    return False;
}

ITEM *lista_busca_sequencial(LISTA *lista, int chave){
    NO *noAtual = lista->inicio;
    while(noAtual != NULL){
        if(item_get_chave(noAtual->item) == chave) return noAtual->item;
        noAtual = noAtual->proximo;
    }
    return NULL;
}

ITEM *lista_busca_ordenada(LISTA *lista, int chave){
    NO *noAtual = lista->inicio;
    int chaveRetornada = 0; 
    while(noAtual != NULL){
        chaveRetornada = item_get_chave(noAtual->item);
        if(chaveRetornada == chave) return noAtual->item;
        if(chaveRetornada > chave) return NULL;
        noAtual = noAtual->proximo;
    }
    return NULL;
}

ITEM *lista_busca(LISTA *lista, int chave){
    if(lista == NULL) return NULL;
    switch(ORDENADA){
        case False:
            return lista_busca_sequencial(lista, chave);
        case True:
            return lista_busca_ordenada(lista, chave);
        default:
            printf("Definição de ORDENADA no arquivo cabeçalho inválida\n");
            exit(ERRO);
    }
}

int lista_tamanho(LISTA *lista){
    if(lista != NULL) return lista->tamanho;
    printf("Get list size error\n");
    exit(ERRO);
}

bool lista_vazia(LISTA *lista){
    return lista_tamanho(lista) == 0 ? True : False;
}

bool lista_cheia(){
    NO *teste = malloc(sizeof(NO));
    if(teste != NULL){
        free(teste); 
        return False;
    }
    return True;
}

void lista_imprimir(LISTA *lista){
    if(lista == NULL) return;
    NO *noAtual = lista->inicio;
    while(noAtual != NULL){
        item_imprimir(noAtual->item);
        noAtual = noAtual->proximo;
    } 
    printf("\n");
}

void lista_inverter_nos(NO *noAtual, LISTA *lista){
    if(noAtual->proximo == NULL) return;
    lista_inverter_nos(noAtual->proximo, lista);
    NO *noAnterior = noAtual->proximo;
    noAnterior->proximo = noAtual;
    noAtual->proximo = NULL;
}   

void lista_inverter(LISTA *lista){
    if(lista == NULL) return;
    lista_inverter_nos(lista->inicio, lista);
    lista->inicio = lista->fim;
}

void lista_compara(NO *atual1, NO *atual2, bool *flag){
    if(item_get_chave(atual1->item) != item_get_chave(atual2->item)) *flag = False;
    if(atual1->proximo == NULL || atual2->proximo == NULL || *flag == False) return;
    lista_compara(atual1->proximo, atual2->proximo, flag);
}

bool listas_iguais(LISTA *lista1, LISTA *lista2){
    if(lista_tamanho(lista1) != lista_tamanho(lista2)) return False;
    bool flagIguais = True;
    lista_compara(lista1->inicio, lista2->inicio, &flagIguais);    
    return flagIguais;
}