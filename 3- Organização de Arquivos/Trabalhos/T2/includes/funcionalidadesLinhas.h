// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#ifndef __FUNCIONALIDADES_LINHAS_H__
    #define __FUNCIONALIDADES_LINHAS_H__

    #include <stdio.h>
    #include <string.h>
    #include "registrosLinhas.h"
    #include "arvoreB.h"
    #include "util.h"

    #define CREATE_INDEX_LINHAS 10
    #define SELECT_WHERE_LINHAS 12
    #define INSERT_INTO_LINHAS 14

    void createIndexLinhas(char *nomeArquivoDados, char *nomeArquivoIndice);
    void selectWhereLinhas(char *nomeArquivoDados, char *nomeArquivoIndice, char *campo, int valor);
    void insertIntoLinhas(char *nomeArquivoDados, char *nomeArquivoIndice, int numeroRegistros);

#endif