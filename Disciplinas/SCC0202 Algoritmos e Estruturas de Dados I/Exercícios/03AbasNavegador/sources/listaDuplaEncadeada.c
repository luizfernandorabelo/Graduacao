#include "lista.h"
#include "aba.h"

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

NO *no_criar(ABA *aba){
    NO *no = malloc(sizeof(NO));
    if(no != NULL){
        no->aba = aba;
        no->anterior = NULL;
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
    aba_apagar(&(*noAtual)->aba);
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
        no->anterior = NULL;
    }
    else{
        no->anterior = lista->fim;
        lista->fim->proximo = no;
        no->proximo = NULL;
    }
    lista->tamanho += 1;
    lista->fim = no;
    return True;
}

bool lista_inserir(LISTA *lista, ABA *aba){
    if(lista == NULL || aba == NULL || lista_cheia()) return False;
    NO *no = no_criar(aba);
    return lista_inserir_fim(lista, no);
}

NO *lista_busca_por_nome_da_aba(LISTA *lista, char *nomeDaAba){
    NO *aux = lista->inicio;
    while(aux != NULL){
        if(strcmp(nomeDaAba, aba_get_titulo(aux->aba)) == 0) return aux;
        aux = aux->proximo;
    }
    return NULL;
}

NO *lista_busca_por_posicao(LISTA *lista, int posicao){
    NO *aux = lista->inicio;
    int contador = 1;
    while(aux != NULL){
        if(contador++ == posicao) return aux;
        aux = aux->proximo;
    }
    return lista->fim;
}

bool lista_alterar_posicao(LISTA *lista, char *nomeDaAba, int posicaoDestino){
    if(lista == NULL || nomeDaAba == NULL) return False;
    
    NO *aux1 = lista_busca_por_nome_da_aba(lista, nomeDaAba);
    if(aux1 == NULL) return False;

    NO *aux2 = lista_busca_por_posicao(lista, posicaoDestino);
    if(aux2 == aux1) return True;
    
    if(aux1 == lista->inicio){
        lista->inicio = aux1->proximo;
        aux1->proximo->anterior = NULL;
    }
    else if(aux1 == lista->fim){
        lista->fim = aux1->anterior;
        aux1->anterior->proximo = NULL;
    }
    else{
        aux1->anterior->proximo = aux1->proximo;
        aux1->proximo->anterior = aux1->anterior;
    }

    if(aux2 == lista->inicio){
        if(aux1->proximo == aux2){
            aux1->proximo = aux2->proximo;
            aux2->proximo = aux1;
            aux2->proximo->anterior = aux1;
            aux1->anterior = aux2;
            aux2->anterior = NULL;
        }
        else{ 
            aux1->proximo = aux2;
            aux2->anterior = aux1;
            aux1->anterior = NULL;
            lista->inicio = aux1;
        }
    }
    else if(aux2 == lista->fim){
        aux2->proximo = aux1;
        aux1->anterior = aux2;
        aux1->proximo = NULL;
    }
    else{
        aux1->proximo = aux2;
        aux1->anterior = aux2->anterior;
        aux2->anterior->proximo = aux1;
        aux2->anterior = aux1;
    }

    return True;
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
        aba_imprimir(noAtual->aba);
        noAtual = noAtual->proximo;
    } 
    printf("\n");
}