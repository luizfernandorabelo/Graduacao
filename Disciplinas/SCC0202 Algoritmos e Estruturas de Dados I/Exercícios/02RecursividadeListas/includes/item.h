#ifndef ITEM_H
    #define ITEM_H
    
    #ifndef BOOLEAN_TYPE
        #define BOOLEAN_TYPE

        #define bool char
        #define True 1
        #define False 0
    #endif

    #define GET_CHAVE_ERRO -1

    typedef struct item_ ITEM;

    ITEM *item_criar(int chave);
    bool item_apagar(ITEM **item);
    void item_imprimir(ITEM *item);
    int item_get_chave(ITEM *item);
    bool item_set_chave(ITEM *item, int chave);
    
#endif