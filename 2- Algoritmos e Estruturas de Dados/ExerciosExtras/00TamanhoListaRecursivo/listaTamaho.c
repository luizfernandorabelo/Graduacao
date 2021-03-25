int lista_tamanho_rec(NO *noAtual){
    if(noAtual == NULL) return 0;
    return(lista_tamanho_rec(noAtual->proximo) + 1);
}

int lista_tamanho(LISTA *lista){
    return(lista_tamanho_rec(lista->inicio));
}