/*noAtual = topo da pilha de origem*/
void pilha_transferir_elementos(PILHA *destino, NO *noAtual){

    if(noAtual == NULL) return;

    pilha_transferir_elementos(destino, noAtual->proximo);
    ITEM *itemAtual = noAtual->item;
    free(noAtual);
    pilha_empilhar(destino, itemAtual);
}

bool pilha_inverter(PILHA *pilha){

    if(pilha != NULL){
        int tamPilha = pilha_tamanho(pilha);
        PILHA *aux = pilha_criar();
        pilha_transferir_elementos(aux, pilha->topo);
        pilha->tamanho = 0;
        pilha->topo = NULL;
        NO *noAtual = aux->topo;
        while(noAtual != NULL){
            NO *proximo = noAtual->proximo;
            ITEM *itemAtual = noAtual->item;
            free(noAtual);
            pilha_empilhar(pilha, itemAtual);
            noAtual = proximo;
        }
        free(aux);
        return(True);
    }

    return(False);
}