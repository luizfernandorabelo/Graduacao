#ifndef LISTA_H
    #define LISTA_H

    #ifndef BOOLEAN_TYPE
        #define BOOLEAN_TYPE

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "aba.h"

    #define ERRO -32000
    #define ORDENADA False

    typedef struct lista_ LISTA;

    LISTA *lista_criar(void);
    bool lista_apagar(LISTA **lista);
    bool lista_inserir(LISTA *lista, ABA *aba);
    bool lista_alterar_posicao(LISTA *lista, char *tituloAba, int posicaoDestino);
    int lista_tamanho(LISTA *lista);
    bool lista_vazia(LISTA *lista);
    bool lista_cheia(LISTA *lista);
    void lista_imprimir(LISTA *lista);

#endif