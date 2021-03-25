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


void lista_receber_maior_e_menor_chave(LISTA *lista, int *maior, int *menor){

    NO *noAtual = lista->inicio;
    int maiorChave = item_obter_chave(lista->inicio->item);
    int menorChave = item_obter_chave(lista->inicio->item);

    while(noAtual != lista->fim->proximo){
        int chaveAtual = item_obter_chave(noAtual->item);
        if(chaveAtual < menorChave) menorChave = chaveAtual; 
        else if(chaveAtual > maiorChave) maiorChave = chaveAtual;
        noAtual = noAtual->proximo;
    }

    *maior = maiorChave;
    *menor = menorChave;
}


BUCKET *lista_obter_buckets(LISTA *lista, int bucketRange, int menorChave){

    BUCKET *buckets = calloc(bucketRange, sizeof(BUCKET));

    NO *noAtual = lista->inicio;
    while(noAtual != lista->fim->proximo){
        NO *proximo = noAtual->proximo;
        int posicaoInsercao = item_obter_chave(noAtual->item) - menorChave;
        printf("Posicao de insercao = %d\n", posicaoInsercao);
        if(buckets[posicaoInsercao].inicio == NULL)
            buckets[posicaoInsercao].inicio = noAtual;
        else
            buckets[posicaoInsercao].fim->proximo = noAtual;
        buckets[posicaoInsercao].fim = noAtual;
        buckets[posicaoInsercao].fim->proximo = NULL;
        noAtual = proximo;
    }

    return(buckets);
}


void lista_remover_repeticoes(LISTA *lista){

    if(lista == NULL || lista->tamanho == 0) return;

    LISTA *copia = lista_copia(lista);

    int maiorChave = 0, menorChave = 0;
    lista_receber_maior_e_menor_chave(copia, &maiorChave, &menorChave);
    int bucketRange = maiorChave - menorChave + 1;

    BUCKET *buckets = lista_obter_buckets(copia, bucketRange, menorChave);

    for(int i = 0; i < bucketRange; i++){
        NO *noAtual = buckets[i].inicio;
        while(noAtual != buckets[i].fim){
            NO *proximo = noAtual->proximo;
            lista_remover_item(lista, item_obter_chave(noAtual->item));
            item_apagar(&noAtual->item);
            free(noAtual); noAtual = NULL;
            noAtual = proximo;
        }
        if(noAtual != NULL){
            item_apagar(&noAtual->item);
            free(noAtual); noAtual = NULL;
        }
    }

    copia->inicio = NULL;
    lista_apagar(&copia);
    free(buckets);
}