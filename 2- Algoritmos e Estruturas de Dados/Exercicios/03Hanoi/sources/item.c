#include "item.h"

#include <stdio.h>
#include <stdlib.h>


struct item_{
    int chave;
};


ITEM *item_criar(int chave){

    ITEM *item = malloc(sizeof(ITEM));

    if(item != NULL) item->chave = chave;
    
    return(item);
}


bool item_apagar(ITEM **item){

    if(*item != NULL){ 
        free(*item);
        *item = NULL;
        return(True);
    }

    return(False);
}


int item_obter_chave(ITEM *item){

    if(item != NULL) return(item->chave);

    fprintf(stderr, "Falha na obtenção de chave de item. O item não aponta para nenhum conteúdo\n");
    
    exit(GET_KEY_ERROR);
}


void item_imprimir(ITEM *item){

    if(item != NULL) printf("%d; ", item->chave);
}