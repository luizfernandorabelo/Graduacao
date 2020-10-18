#include "item.h"

#include <stdio.h>
#include <stdlib.h>

struct item_{
    int chave;
};

ITEM *item_criar(int chave){
    ITEM *item = malloc(sizeof(ITEM));
    if(item != NULL) item->chave = chave;
    return item;
}

bool item_apagar(ITEM **item){
    if(*item == NULL) return False;
    free(*item); (*item) = NULL;
    return True;
}

void item_imprimir(ITEM *item){
    if(item == NULL) return;
    printf("[%d]; ", item->chave);
}

int item_get_chave(ITEM *item){
    if(item != NULL) return item->chave;
    printf("Get key error\n");
    exit(GET_CHAVE_ERRO);
}

bool item_set_chave(ITEM *item, int chave){
    if(item == NULL) return False;
    item->chave = chave;
    return True;
}