#ifndef ARVORE_BINARIA_H
    #define ARVORE_BINARIA_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    #define ESQUERDA 'e'
    #define DIREITA 'd'
    #define RAIZ 0

    typedef struct ab_ AB;

    AB *arvore_criar(void);
    bool arvore_apagar(AB **arvore);
    bool arvore_inserir(AB *arvore, ITEM *item, int chavePai, char lado);
    bool arvore_remover(AB *arvore, int chavePai, char lado);
    ITEM *arvore_buscar(AB *arvore, int chave);
    int arvore_tamanho(AB *arvore);
    bool arvore_cheia(AB *arvore);
    bool arvore_vazia(AB *arvore);
    void arvore_imprimir(AB *arvore);

#endif