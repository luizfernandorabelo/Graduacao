#include "trie.h"

#include <stdio.h>

void testar_impressao(TRIE *trie){
    printf("\nPalavras na Trie:\n");
    trie_imprimir(trie); 
    printf("TOTAL = %d palavras\n", trie_tamanho(trie));
}

void testar_insercao(TRIE *trie, char *chave){
    printf("\nInserindo item...\n");
    ITEM *buffer = item_criar(chave);
    bool inserido = trie_inserir(trie, buffer);
    if(inserido == True)
        printf("Item de chave '%s' inserido na trie com sucesso!\n", chave);
    else
        printf("Erro na inserção do item de chave '%s'!\n", chave);
    testar_impressao(trie);
}

void testar_busca(TRIE *trie, char *chave){
    printf("\nBuscando item...\n");
    ITEM *item = trie_buscar_item(trie, chave);
    if(item != NULL)
        printf("Item de chave '%s' retornado pela função trie_buscar_item()\n", chave);
    else
        printf("'%s' não está presente na trie! A função trie_buscar_item() retornou NULL\n", chave);
}

void testar_remocao(TRIE *trie, char *chave){
    printf("\nRemovendo item...\n");
    bool removido = trie_remover(trie, chave);
    if(removido == True)
        printf("Item de chave '%s' removido da Trie com sucesso!\n", chave);
    else
        printf("O item de chave '%s' NÃO foi removido da Trie!\n", chave);
    testar_impressao(trie);
}

int main(int argc, char *argv[]){

    TRIE *trie = NULL;
    printf("Trie %s!\n", ((trie = trie_criar()) != NULL) ? "criada" : "NAO criada");

    testar_insercao(trie, "oi");
    testar_insercao(trie, "tudo");
    testar_insercao(trie, "bem");
    testar_insercao(trie, "benigno");
    testar_insercao(trie, "estrutura");
    testar_insercao(trie, "estruturadedados");

    testar_busca(trie, "oi");
    testar_busca(trie, "bem");
    testar_busca(trie, "benigno");
    testar_busca(trie, "benignos");
    testar_busca(trie, "oie");

    testar_remocao(trie, "oi");
    testar_remocao(trie, "bem");
    testar_remocao(trie, "estrutura");

    testar_insercao(trie, "benevolente");

    testar_busca(trie, "estrutura");
    testar_busca(trie, "benevolente");

    printf("\nTrie %s!\n", (trie_apagar(&trie) == True) ? "apagada com sucesso" : "NÃO apagada");

    return(0);
}