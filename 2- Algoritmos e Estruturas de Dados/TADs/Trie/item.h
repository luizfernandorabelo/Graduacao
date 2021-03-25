#ifndef ITEM_H
    #define ITEM_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #define GET_KEY_ERROR - 1
    
    typedef struct item_ ITEM;

    ITEM *item_criar(char *chave);
    bool item_apagar(ITEM **item);
    char *item_obter_chave(ITEM *item);
    int item_obter_tamanho_chave(ITEM *item);
    void item_imprimir(ITEM *item);

#endif