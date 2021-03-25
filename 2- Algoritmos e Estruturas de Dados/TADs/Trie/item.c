#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct item_{
    char *chave;
};


ITEM *item_criar(char *chave){

    ITEM *item = malloc(sizeof(ITEM));

    if(item != NULL && chave != NULL){
        int tamChave = strlen(chave);
        item->chave = calloc(tamChave + 1, sizeof(char));
        strcpy(item->chave, chave);
    }
    
    return(item);
}


bool item_apagar(ITEM **item){

    if(*item != NULL){ 
        free((*item)->chave);
        free(*item);
        *item = NULL;
        return(True);
    }

    return(False);
}


char *item_obter_chave(ITEM *item){

    if(item != NULL) return(item->chave);

    fprintf(stderr, "Falha na obtenção de chave de item. O item não aponta para nenhum conteúdo\n");
    
    exit(GET_KEY_ERROR);
}

   
int item_obter_tamanho_chave(ITEM *item){

    if(item != NULL)
        return(strlen(item->chave));
    
    return(-1);
}


void item_imprimir(ITEM *item){

    if(item != NULL) printf("- %s\n", item->chave);
}