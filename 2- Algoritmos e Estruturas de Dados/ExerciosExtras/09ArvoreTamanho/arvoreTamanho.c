int arvore_tamanho(NO *raiz){

    if(raiz == NULL)
        return(0);
    
    return(arvore_tamanho(raiz->filhoEsquerda) + arvore_tamanho(raiz->filhoDireita) + 1);
}