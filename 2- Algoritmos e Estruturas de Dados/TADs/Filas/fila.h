#ifndef FILA_H
    #define FILA_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    typedef struct fila_ FILA;

    FILA *fila_criar(void);
    bool fila_apagar(FILA **fila);
    bool fila_entrar(FILA *fila, ITEM *item);
    bool fila_sair(FILA *fila);
    ITEM *fila_inicio(FILA *fila);
    int fila_tamanho(FILA *fila);
    bool fila_cheia(FILA *fila);
    bool fila_vazia(FILA *fila);
    void fila_imprimir(FILA *fila);

#endif