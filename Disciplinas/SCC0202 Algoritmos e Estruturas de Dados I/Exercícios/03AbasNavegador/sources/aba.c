#include "aba.h"

#include <stdio.h>
#include <stdlib.h>

struct aba_{
    char *titulo;
    char *url;
};

ABA *aba_criar(){
    ABA *aba = malloc(sizeof(ABA));
    if(aba != NULL){
        aba->titulo = NULL;
        aba->url = NULL;
    }
    return aba;
}

bool aba_set_titulo(ABA *aba, char *titulo){
    if(aba == NULL || titulo == NULL) return False;
    aba->titulo = titulo;
    return True;
}

bool aba_set_url(ABA *aba, char *url){
    if(aba == NULL || url == NULL) return False;
    aba->url = url;
    return True;
}

char *aba_get_titulo(ABA *aba){
    if(aba != NULL) return aba->titulo;
    return NULL;
}

char *aba_get_url(ABA *aba){
    if(aba != NULL) return aba->url;
    return NULL;
}

void aba_imprimir(ABA *aba){
    if(aba != NULL){
        fprintf(stdout, "%s %s", aba->titulo, aba->url);
    }
}

bool aba_apagar(ABA **aba){
    if(*aba != NULL){
        free((*aba)->titulo);
        free((*aba)->url);
        free(*aba);
        *aba = NULL;
        return True;
    }
    return False;
}