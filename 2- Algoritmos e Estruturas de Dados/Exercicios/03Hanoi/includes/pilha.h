#ifndef PILHA_H
    #define PILHA_H

    #ifndef booleanType
        #define booleanType
        
        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"
    #include <stdio.h>

    typedef struct pilha_ PILHA;

    PILHA *pilha_criar(char id);
    bool pilha_apagar(PILHA **pilha);
    void pilha_hanoi(PILHA **arrayPilhas, int nDiscos, FILE *fp);
    
#endif