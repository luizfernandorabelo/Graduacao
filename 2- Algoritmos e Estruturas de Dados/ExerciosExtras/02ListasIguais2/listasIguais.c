bool listas_iguais_rec(NO *noLista1, NO *noLista2){
    
    if(noLista1 == NULL && noLista2 == NULL)
        return(True);

    if(item_obter_chave(noLista1->item) != item_obter_chave(noLista2->item))
        return(False);
        
    return(listas_iguais_rec(noLista1->proximo, noLista2->proximo));
}


bool listas_iguais(LISTA *lista1, LISTA *lista2){
    if(lista1 != NULL && lista2 != NULL && lista1->tamanho == lista2->tamanho && lista2->tamanho > 0)
        return(listas_iguais_rec(lista1->inicio, lista2->inicio));
    return(False);
}