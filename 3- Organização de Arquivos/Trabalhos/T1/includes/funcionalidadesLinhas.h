#ifndef __FUNCIONALIDADES_LINHAS_H__
    #define __FUNCIONALIDADES_LINHAS_H__

    #include <stdio.h>
    #include <string.h>
    #include "registrosLinhas.h"
    #include "leitorCSV.h"
    #include "util.h"

    #define CREATE_TABLE_LINHAS 2
    #define SELECT_FROM_LINHAS 4
    #define SELECT_WHERE_LINHAS 6
    #define INSERT_INTO_LINHAS 8

    void createTableLinhas(char *arquivoEntrada, char *arquivoSaida);
    void selectFromLinhas(char *arquivoEntrada);
    void selectWhereLinhas(char *arquivoEntrada, char *campo, char *valor);
    void insertIntoLinhas(char *arquivoEntrada, int numeroRegistros);

#endif