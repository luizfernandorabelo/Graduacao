#ifndef ARVORE_N_ARIA
    #define ARVORE_N_ARIA

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    typedef struct an_ AN;

    AN *arvore_criar(ITEM *itemRaiz);
    bool arvore_apagar(AN **arvore);
    bool arvore_inserir(AN *arvore, ITEM *item, int chavePai);
    ITEM *arvore_buscar(AN *arvore, int chave);
    void arvore_imprimir(AN *arvore);
    int arvore_tamanho(AN *arvore);
    bool arvore_cheia(AN *arvore);
    bool arvore_vazia(AN *arvore);

#endif