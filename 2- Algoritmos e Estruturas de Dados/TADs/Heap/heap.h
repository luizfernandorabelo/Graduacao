#ifndef HEAP_H
    #define HEAP_H
    
    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    //#define MAX_HEAP
    #define MIN_HEAP

    typedef struct heap_ HEAP;

    HEAP *heap_criar(void);
    bool heap_apagar(HEAP **heap);
    bool heap_inserir(HEAP *heap, ITEM *item);
    bool heap_remover_inicio(HEAP *heap);
    ITEM *heap_inicio(HEAP *heap);
    ITEM *heap_fim(HEAP *heap);
    int heap_tamanho(HEAP *heap);
    bool heap_cheia(HEAP *heap);
    bool heap_vazia(HEAP *heap);
    void heap_imprimir(HEAP *heap);

#endif