/*noAtual = pilhaOriginal->topo*/
void pilha_copiar_nos(PILHA *copia, NO *noAtual){

    if(noAtual == NULL) return;

    pilha_copiar_nos(copia, noAtual->proximo);

    int chaveAtual = item_obter_chave(noAtual->item);

    pilha_empilhar(copia, item_criar(chaveAtual));
}


PILHA *pilha_copia(PILHA *pilha){

    if(pilha != NULL){
        PILHA *copia = pilha_criar();
        pilha_copiar_nos(copia, pilha->topo);
        return(copia);
    }

    return(NULL);
}