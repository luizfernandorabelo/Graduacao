#ifndef MATRIZ_ESPARSA_H
    #define MATRIZ_ESPARSA_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    typedef struct matriz_esparsa_ ME;

    ME *matriz_criar(int nLinhas, int nColunas, int valorPadrao);
    bool matriz_apagar(ME **matriz);
    bool matriz_inserir(ME *matriz, int linha, int coluna, ITEM *item);
    bool matriz_remover_item(ME *matriz, int linha, int coluna);
    ITEM *matriz_obter_item(ME *matriz, int linha, int coluna);
    void matriz_imprimir(ME *matriz);

#endif