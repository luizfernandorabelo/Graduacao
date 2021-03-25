#ifndef ARVORE_AVL_H
    #define ARVORE_AVL_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    typedef struct avl_ AVL;

    AVL *arvore_criar(void);
    bool arvore_apagar(AVL **arvore);
    bool arvore_inserir(AVL *arvore, ITEM *item);
    bool arvore_remover(AVL *arvore, int chave);
    ITEM *arvore_buscar(AVL *arvore, int chave);
    int arvore_tamanho(AVL *arvore);
    bool arvore_cheia(AVL *arvore);
    bool arvore_vazia(AVL *arvore);
    void arvore_imprimir(AVL *arvore);

#endif