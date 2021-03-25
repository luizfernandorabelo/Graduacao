#ifndef PILHA_H
    #define PILHA_H

    #ifndef booleanType
        #define booleanType
        
        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    typedef struct pilha_ PILHA;

    PILHA *pilha_criar(void);
    bool pilha_apagar(PILHA **pilha);
    bool pilha_empilhar(PILHA *pilha, ITEM *item);
    bool pilha_desempilhar(PILHA *pilha);
    ITEM *pilha_topo(PILHA *pilha);
    void pilha_imprimir(PILHA *pilha);
    int pilha_tamanho(PILHA *pilha);
    bool pilha_cheia(PILHA *pilha);
    bool pilha_vazia(PILHA *pilha);

#endif