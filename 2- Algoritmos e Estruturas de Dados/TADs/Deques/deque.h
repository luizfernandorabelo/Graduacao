#ifndef DEQUE_H
    #define DEQUE_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    typedef struct deque_ DEQUE;

    DEQUE *deque_criar(void);
    bool deque_apagar(DEQUE **deque);
    bool deque_inserir_inicio(DEQUE *deque, ITEM *item);
    bool deque_inserir_fim(DEQUE *deque, ITEM *item);
    bool deque_remover_inicio(DEQUE *deque);
    bool deque_remover_fim(DEQUE *deque);
    ITEM *deque_inicio(DEQUE *deque);
    ITEM *deque_fim(DEQUE *deque);
    int deque_tamanho(DEQUE *deque);
    bool deque_cheia(DEQUE *deque);
    bool deque_vazia(DEQUE *deque);
    void deque_imprimir(DEQUE *deque);

#endif