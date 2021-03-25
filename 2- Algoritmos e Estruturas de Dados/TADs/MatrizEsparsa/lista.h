#ifndef LISTA_H
    #define LISTA_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    typedef struct lista_ LISTA;  

    int size_of_lista(void);
    LISTA *lista_criar(void);
    bool lista_inserir(LISTA *lista, ITEM *item, int coluna);
    bool lista_remover_item(LISTA *lista, int coluna);
    bool lista_apagar(LISTA **lista);
    ITEM *lista_buscar_item(LISTA *lista, int coluna);
    void lista_imprimir(LISTA *lista);
    
#endif