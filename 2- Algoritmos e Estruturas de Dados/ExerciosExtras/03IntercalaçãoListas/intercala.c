LISTA *lista_copia(LISTA *lista){ 

    if(lista != NULL){
        LISTA *copia = lista_criar();
        NO *noAtual = lista->inicio;
        while(noAtual != lista->fim->proximo){
            ITEM *itemCopia = item_criar(item_obter_chave(noAtual->item));
            lista_inserir(copia, itemCopia);
            noAtual = noAtual->proximo;
        }
        return(copia);
    }

    return(NULL);
}


void lista_ordenar(LISTA *lista){ 

    int menorChave = item_obter_chave(lista->inicio->item);    
    int maiorChave = item_obter_chave(lista->inicio->item);    

    NO *noAtual = lista->inicio->proximo;
    while(noAtual != lista->fim->proximo){
        int chaveAtual = item_obter_chave(noAtual->item);
        if(chaveAtual < menorChave) menorChave = chaveAtual;
        else if(chaveAtual > maiorChave) maiorChave = chaveAtual;
        noAtual = noAtual->proximo; 
    }

    int rangeChaves = maiorChave - menorChave + 1;

    ITEM **arrayAux = calloc(rangeChaves, sizeof(ITEM *));

    noAtual = lista->inicio;
    while(noAtual != NULL){
        int posInsercao = item_obter_chave(noAtual->item) - menorChave;
        arrayAux[posInsercao] = noAtual->item;
        NO *proximo = noAtual->proximo;
        free(noAtual);
        noAtual = proximo;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;

    for(int i = 0; i < rangeChaves; i++){
        if(arrayAux[i] != NULL)
            lista_inserir(lista, arrayAux[i]);
    }
}


LISTA *lista_intercalar(LISTA *lista1, LISTA *lista2){ 

    if(lista1 == NULL || lista2 == NULL) return(NULL);

    #ifdef LISTA_NAO_ORDENADA
        lista1 = lista_copia(lista1);
        lista2 = lista_copia(lista2);
        lista_ordenar(lista1);
        lista_ordenar(lista2);
    #endif

    LISTA * listaIntercalada = lista_criar();
    NO *noLista1 = lista1->inicio;
    NO *noLista2 = lista2->inicio;
    long ultimoInserido = __LONG_MAX__; // valor inatingivel para um int de 32 bits (tipo da chave)

    while(noLista1 != NULL && noLista2 != NULL){
        int chave1 = item_obter_chave(noLista1->item);
        int chave2 = item_obter_chave(noLista2->item);
        if(chave1 <= chave2){
            if(chave1 != ultimoInserido)
                lista_inserir(listaIntercalada, item_criar(chave1));
            ultimoInserido = chave1;
            noLista1 = noLista1->proximo;                    
        }
        else{
            if(chave2 != ultimoInserido)
                lista_inserir(listaIntercalada, item_criar(chave2));
            ultimoInserido = chave2;
            noLista2 = noLista2->proximo;                    
        }
    }

    while(noLista1 != NULL){
        int chave1 = item_obter_chave(noLista1->item);
        if(chave1 != ultimoInserido)
            lista_inserir(listaIntercalada, item_criar(chave1));
        ultimoInserido = chave1;
        noLista1 = noLista1->proximo; 
    }

    while(noLista2 != NULL){
        int chave2 = item_obter_chave(noLista2->item);
        if(chave2 != ultimoInserido)
            lista_inserir(listaIntercalada, item_criar(chave2));
        ultimoInserido = chave2;
        noLista2 = noLista2->proximo; 
    }

    #ifdef LISTA_NAO_ORDENADA
        free(lista1);
        free(lista2);
    #endif

    return(listaIntercalada);
}