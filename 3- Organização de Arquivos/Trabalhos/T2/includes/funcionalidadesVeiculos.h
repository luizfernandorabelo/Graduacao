// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#ifndef __FUNCIONALIDADES_VEICULOS_H__
    #define __FUNCIONALIDADES_VEICULOS_H__

    #include <stdio.h>
    #include <string.h>
    #include "registrosVeiculos.h"
    #include "arvoreB.h"
    #include "util.h"

    #define CREATE_INDEX_VEICULOS 9
    #define SELECT_WHERE_VEICULOS 11
    #define INSERT_INTO_VEICULOS 13

    void createIndexVeiculos(char *nomeArquivoDados, char *nomeArquivoIndice);
    void selectWhereVeiculos(char *nomeArquivoDados, char *nomeArquivoIndice, char *campo, char *valor);
    void insertIntoVeiculos(char *nomeArquivoDados, char *nomeArquivoIndice, int numeroRegistros);

#endif