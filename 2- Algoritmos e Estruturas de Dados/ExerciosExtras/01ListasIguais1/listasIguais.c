bool listas_iguais(LISTA *lista1, LISTA *lista2){

    if(lista1 != NULL && lista2 != NULL && lista1->tamanho == lista2->tamanho){
        NO *noLista1 = lista1->inicio;
        NO *noLista2 = lista2->inicio;
        while(noLista1 != NULL && noLista2 != NULL){
            if(item_obter_chave(noLista1->item) != item_obter_chave(noLista2->item))
                return(False);
            noLista1 = noLista1->proximo;
            noLista2 = noLista2->proximo;
        }
        return(True);
    }

    return(False);
}