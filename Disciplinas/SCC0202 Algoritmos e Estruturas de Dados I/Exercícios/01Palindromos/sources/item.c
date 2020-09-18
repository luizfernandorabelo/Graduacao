#include "item.h"

#include <stdio.h>
#include <stdlib.h>

struct item_{
    char key;
};

ITEM *itemCreate(char key){
    ITEM *item = NULL;
    item = (ITEM *) malloc(sizeof(ITEM));
    if(item != NULL){
        item->key = key;
    }
    return(item);
}

bool itemDelete(ITEM **item){
    if(*item != NULL){
        free(*item);
        *item = NULL;
        return(True);
    }
    return(False);
}
    
void itemPrint(ITEM *item){
    if(item != NULL) printf("\n--> Item: %d\n", item->key);
}
    
char itemGetKey(ITEM *item){
    if(item != NULL) return(item->key);
    printf("\nGet key error");
    exit(GET_KEY_ERROR);      
}

bool itemSetKey(ITEM *item, char key){
    if(item != NULL){
        item->key = key;
        return(True);
    }
    return(False);
}
