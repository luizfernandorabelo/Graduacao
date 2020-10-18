#ifndef LISTA_H
    #define LISTA_H

    #ifndef BOOLEAN_TYPE
        #define BOOLEAN_TYPE

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    #define ERRO -32000
    #define ORDENADA False

    typedef struct lista_ LISTA;

    LISTA *lista_criar(void);
    bool lista_apagar(LISTA **lista);
    bool lista_inserir(LISTA *lista, ITEM *item);
    bool lista_remover(LISTA *lista, int chave);
    ITEM *lista_busca(LISTA *lista, int chave);
    int lista_tamanho(LISTA *lista);
    bool lista_vazia(LISTA *lista);
    bool lista_cheia();
    void lista_imprimir(LISTA *lista);
    void lista_inverter(LISTA *lista);
    bool listas_iguais(LISTA *lista1, LISTA *lista2);

#endif