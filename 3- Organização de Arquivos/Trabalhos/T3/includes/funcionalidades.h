// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#ifndef __FUNCIONALIDADES_H__
    #define __FUNCIONALIDADES_H__

    #include <stdio.h>
    #include <string.h>
    #include "registrosVeiculos.h"
    #include "registrosLinhas.h"
    #include "arvoreB.h"
    #include "util.h"

    #define JUNCAO_LOOP_UNICO 15
    #define JUNCAO_ARQUIVO_INDICE 16
    #define ORDENACAO_VEICULOS 17
    #define ORDENACAO_LINHAS 18
    #define JUNCAO_ORDENADA 19

    void juncaoLoopUnico(char *nomeArqVeic, char *nomeArqLinhas, char *campoVeiculo, char *campoLinha);
    void juncaoArquivoIndice(char *nomeArqVeic, char *nomeArqLinhas, char *campoVeiculo, char *campoLinha, char *nomeArqIndice);
    void ordenacaoVeiculos(char *nomeArqDesordenado, char *nomeArqOrdenado, char *campoOrdenacao);
    void ordenacaoLinhas(char *nomeArqDesordenado, char *nomeArqOrdenado, char *campoOrdenacao);
    void juncaoOrdenada(char *nomeArqVeic, char *nomeArqLinhas, char *campoVeiculo, char *campoLinha);

#endif