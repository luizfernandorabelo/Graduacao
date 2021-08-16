// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#ifndef __REGISTROS_LINHAS_H__
    #define __REGISTROS_LINHAS_H__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "util.h"

    typedef struct CabecalhoLinha
    {
        char status;
        long long int byteProxReg;
        int nroRegistros;
        int nroRegRemovidos;
        char descreveCodigo[16];
        char descreveCartao [14];
        char descreveNome[14];
        char descreveCor[25];
    }CabecalhoLinha;

    typedef struct RegistroLinha
    {
        char removido;
        int tamanhoRegistro;
        int codLinha;
        char aceitaCartao; // 'S' (sim), 'N' (não) ou 'F' (fins de semana)
        int tamanhoNome;
        char nomeLinha[100];
        int tamanhoCor;
        char corLinha[100];
    }RegistroLinha;

    CabecalhoLinha *carregaCabecalhoLinhaDoBIN(FILE *arquivoBIN); 
    CabecalhoLinha *inicializaCabecalhoLinha(void);
    RegistroLinha *carregaRegistroLinhaDoBIN(FILE *arquivoBIN); 
    RegistroLinha **carregaVetorRegistrosLinhaOrdenadoDoBIN(FILE *arquivoBIN);
    void copiaDescricoesCabecalhoLinha(CabecalhoLinha *cabecalhoOriginal, CabecalhoLinha *cabecalhoCopia);
    void escreveCabecalhoLinhaNoBIN(CabecalhoLinha *cabecalho, FILE *arquivoBIN);
    void escreveRegistroLinhaNoBIN(RegistroLinha *registroLinha, FILE *arquivoBIN); 
    void escreveVetorRegistrosLinhaOrdenadoNoBIN(FILE *arquivoBIN, RegistroLinha **registrosLinha, CabecalhoLinha *cabeclho);
    void linhaNaTela (RegistroLinha *Reg, CabecalhoLinha *cabecalho);

#endif