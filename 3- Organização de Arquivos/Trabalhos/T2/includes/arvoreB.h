// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#ifndef __ARVORE_B__
    #define __ARVORE_B__
    
    #ifndef boolean
        #define boolean
    
        #define bool int
        #define true 1
        #define false 0
    #endif

    #define TAM_PAGINA 77
    #define ORDEM_ARVORE 5 // nro de filhos
    #define VALOR_NULO -1

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #include "util.h"

    typedef struct {
        char status; // '0' = inconsistente e '1' = consistente
        int RRNraiz;
        int RRNproxNo;
        char lixo[68];
    }NoCabecalhoAB;

    typedef struct {
        int chave;
        long long byteOffset;
    }RegistroDadosAB;

    typedef struct {
        char folha; // '0' = nao e '1' = sim
        int nroChavesIndexadas;
        int RRNdoNo;
        RegistroDadosAB *registros[(ORDEM_ARVORE-1)];
        int filhos[ORDEM_ARVORE];
    }NoDadosAB;

    typedef struct {
        int chave;
        long long byteOffset;
        int RRNfilhoDireita;
    }RegistroPromovido;

    NoCabecalhoAB *carregaNoCabecalhoDaAB(FILE *arquivoIndice);
    void escreveNoCabecalhoNaAB(FILE *arquivoIndice, NoCabecalhoAB *cabecalho);
    void insereRegistroDadosNaAB(FILE *arquivoIndice, NoCabecalhoAB *cabecalho, int chaveInserida, long long byteOffset);
    long long buscaRegistroDadosNaAB(FILE *arquivoIndice, NoCabecalhoAB *cabecalho, int chaveBuscada);

#endif