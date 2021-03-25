#ifndef LISTA_H
    #define LISTA_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #define LISTA_ORDENADA 
    //#define LISTA_NAO_ORDENADA 

    #include "item.h"

    typedef struct lista_ LISTA;  

    LISTA *lista_criar(void);
    bool lista_inserir(LISTA *lista, ITEM *item);
    bool lista_remover_item(LISTA *lista, int chave);
    bool lista_apagar(LISTA **lista);
    ITEM *lista_buscar_item(LISTA *lista, int chave);
    int lista_tamanho(LISTA *lista);
    bool lista_vazia(LISTA *lista);
    bool lista_cheia(LISTA *lista);
    void lista_imprimir(LISTA *lista);
    
#endif