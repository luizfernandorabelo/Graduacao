bool pilhas_iguais(PILHA *pilha1, PILHA *pilha2){

    if(pilha1 != NULL && pilha2 != NULL){
        int tamPilha1 = pilha_tamanho(pilha1);
        int tamPilha2 = pilha_tamanho(pilha2);
        if(tamPilha1 == tamPilha2){
            for(int i = 0; i < tamPilha1; i++){
                if(item_obter_chave(pilha1->itens[i]) != item_obter_chave(pilha2->itens[i]))
                    return(False);
            }
            return(True);
        }
    }

    return(False);
}