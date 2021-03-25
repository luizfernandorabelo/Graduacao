#ifndef ARVORE_BINARIA_BUSCA_H
    #define ARVORE_BINARIA_BUSCA_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    typedef struct abb_ ABB;

    ABB *arvore_criar(void);
    bool arvore_apagar(ABB **arvore);
    bool arvore_inserir(ABB *arvore, ITEM *item);
    bool arvore_remover(ABB *arvore, int chave);
    ITEM *arvore_buscar(ABB *arvore, int chave);
    int arvore_tamanho(ABB *arvore);
    bool arvore_cheia(ABB *arvore);
    bool arvore_vazia(ABB *arvore);
    void arvore_imprimir(ABB *arvore);
    void arvore_percorrer_preordem(ABB *arvore);
    void arvore_percorrer_emordem(ABB *arvore);
    void arvore_percorrer_posordem(ABB *arvore);

#endif