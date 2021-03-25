#ifndef TRIE_H
    #define TRIE_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #include "item.h"

    typedef struct trie_ TRIE;

    TRIE *trie_criar(void);
    bool trie_apagar(TRIE **trie);
    bool trie_inserir(TRIE *trie, ITEM *item);
    bool trie_remover(TRIE *trie, char *chave);
    ITEM *trie_buscar_item(TRIE *trie, char *chave);
    void trie_imprimir(TRIE *trie);
    int trie_tamanho(TRIE *trie);
    bool trie_cheia(TRIE *trie);
    bool trie_vazia(TRIE *trie);

#endif