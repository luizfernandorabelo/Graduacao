/* item_imprimir() deve apresentar a máscara "%c" na impressão*/

int lista_strlen(LISTA *lista){
    return(lista_tamanho(lista) - 1); // desconsiderando o '\0'
}

int lista_strcmp_rec(NO *noLista1, NO *noLista2){

    int chave1 = item_obter_chave(noLista1->item);
    int chave2 = item_obter_chave(noLista2->item);

    if(chave1 != '\0' && chave2 != '\0'){
        if(chave1 < chave2) return(-1);
        if(chave2 < chave1) return(1);
        return(lista_strcmp_rec(noLista1->proximo, noLista2->proximo));
    }

    if(chave1 == '\0' && chave2 == '\0') return(0);
    if(chave1 == '\0') return(-1);
    return(1); // chave 2 é igual a '\0'
}


int lista_strcmp(LISTA *lista1, LISTA *lista2){

    if(lista1 != NULL && lista2 != NULL)
        return(lista_strcmp_rec(lista1->inicio, lista2->inicio));        
}

void lista_strcpy(LISTA *origem, LISTA *destino){

    if(lista_tamanho(destino) > 0){
        lista_apagar_nos(&destino->inicio);
        destino->tamanho = 0;
    }

    NO *noAtual = origem->inicio;

    while(noAtual != NULL){
        int chaveAtual = item_obter_chave(noAtual->item);
        lista_inserir(destino, item_criar(chaveAtual));
        noAtual = noAtual->proximo;    
    }
}

LISTA *lista_strcat(LISTA *lista1, LISTA *lista2){

    LISTA *concatenada = lista_criar();

    lista_strcpy(lista1, concatenada);

    lista_remover_item(concatenada, '\0');

    NO *noAtual = lista2->inicio;

    while(noAtual != NULL){
        int chaveAtual = item_obter_chave(noAtual->item);
        lista_inserir(concatenada, item_criar(chaveAtual));
        noAtual = noAtual->proximo;    
    }

    return(concatenada);
}