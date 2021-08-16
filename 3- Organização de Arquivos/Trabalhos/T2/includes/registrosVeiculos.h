// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#ifndef __REGISTROS_VEICULOS_H__
    #define __REGISTROS_VEICULOS_H__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "util.h"

    typedef struct CabecalhoVeiculo
    {
        char status;
        long long byteProxReg;
        int nroRegistros; 
        int nroRegRemovidos;
        char descrevePrefixo[19];
        char descreveData[36];
        char descreveLugares[43];
        char descreveLinha[27];
        char descreveModelo[18];
        char descreveCategoria[21];
    }CabecalhoVeiculo;

    typedef struct RegistroVeiculo
    {
        char removido; // '0' = sim ou '1' = não
        int tamanhoRegistro;
        char prefixo[6];
        char data[11]; // AAAA - MM - DD
        int quantidadeLugares;
        int codLinha;
        int tamanhoModelo;
        char modelo[100];
        int tamanhoCategoria;
        char categoria[100];
    }RegistroVeiculo;

    CabecalhoVeiculo *carregaCabecalhoVeiculoDoBIN(FILE *arquivoBIN); 
    RegistroVeiculo *carregaRegistroVeiculoDoBIN(FILE *arquivoBIN); 
    RegistroVeiculo *carregaRegistroVeiculoDaStdin(void);
    void escreveCabecalhoVeiculoNoBIN(CabecalhoVeiculo *cabecalho, FILE *arquivoBIN);
    void escreveRegistroVeiculoNoBIN(RegistroVeiculo *registroVeiculo, FILE *arquivoBIN); 
    void veiculoNaTela (RegistroVeiculo *Reg, CabecalhoVeiculo *cabecalho);

#endif