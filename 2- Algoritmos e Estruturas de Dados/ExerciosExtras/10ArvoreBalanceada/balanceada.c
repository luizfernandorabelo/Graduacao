/* Para que uma árvore seja balanceada, o valor absoluto da diferença
entre as alturas de suas subárvores deve ser de, no máximo, 1 */

int arvore_obter_altura(NO *raiz){
    return((raiz != NULL) ? raiz->altura : -1);
}


void arvore_balanceada_rec(NO *raiz, bool *balanceada){

    if(*balanceada == False || raiz == NULL)
        return;
    
    *balanceada = (abs(arvoreobter_altura(raiz->esquerda) - arvore_obter_altura(raiz->direita)) <= 1) ? True : False;

    arvore_balanceada_rec(raiz->esquerda, balanceada);
    arvore_balanceada_rec(raiz->direita, balanceada);
}


bool arvore_balanceada(ABB *arvore){

    if(arvore != NULL){
        bool balanceada = True;
        arvore_balanceada_rec(arvore->raiz, &balanceada);
        return(balanceada);
    }
    
    return(False);
}