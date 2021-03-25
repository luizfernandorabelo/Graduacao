#ifndef PALAVRAS_CHAVE_H
    #define PALAVRAS_CHAVE_H

    #ifndef BOOLEAN_TYPE 
        #define BOOLEAN_TYPE

        #define boolean char
        #define TRUE 1
        #define FALSE 0
    #endif

    struct codigos_relacionados_{
        int *codigos;
        int quantidade;
    };

    typedef struct codigos_relacionados_ CODIGOS;
    typedef struct palavras_chave_ PALAVRAS_CHAVE;

    PALAVRAS_CHAVE *palavras_chave_criar(void);
    boolean palavras_chave_apagar(PALAVRAS_CHAVE **palavrasChave);
    boolean palavras_chave_inserir(PALAVRAS_CHAVE *palavrasChave, char *chave, int codigoSite);
    boolean palavras_chave_remover(PALAVRAS_CHAVE *palavrasChave, char *chave, int codigoSite);
    CODIGOS *palavras_chave_buscar_codigos_relacionados(PALAVRAS_CHAVE *palavrasChave, char *chave);

#endif