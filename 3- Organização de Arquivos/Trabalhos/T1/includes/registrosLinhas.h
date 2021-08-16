#ifndef __REGISTROS_LINHAS_H__
    #define __REGISTROS_LINHAS_H__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "leitorCSV.h"
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
        char aceitaCartao; // 'S' (sim), 'N' (não), 'F' (fins de semana)
        int tamanhoNome;
        char nomeLinha[100];
        int tamanhoCor;
        char corLinha[100];
    }RegistroLinha;

    CabecalhoLinha *carregaCabecalhoLinhaDoCSV(FILE *arquivoCSV);
    RegistroLinha *carregaRegistroLinhaDoCSV(FILE *arquivoCSV);
    CabecalhoLinha *carregaCabecalhoLinhaDoBIN(FILE *arquivoBIN); 
    RegistroLinha *carregaRegistroLinhaDoBIN(FILE *arquivoBIN); 
    RegistroLinha *carregaRegistroLinhaDaStdin(void);
    void escreveCabecalhoLinhaNoBIN(CabecalhoLinha *cabecalho, FILE *arquivoBIN);
    void escreveRegistroLinhaNoBIN(RegistroLinha *registroLinha, FILE *arquivoBIN); 
    void linhaNaTela (RegistroLinha *Reg, CabecalhoLinha *cabecalho);
    RegistroLinha *localizaLinha(FILE *arquivoBIN, char* valor, char *campo);

#endif