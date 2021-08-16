#ifndef __FUNCIONALIDADES_VEICULOS_H__
    #define __FUNCIONALIDADES_VEICULOS_H__

    #include <stdio.h>
    #include <string.h>
    #include "registrosVeiculos.h"
    #include "leitorCSV.h"
    #include "util.h"

    #define CREATE_TABLE_VEICULOS 1
    #define SELECT_FROM_VEICULOS 3
    #define SELECT_WHERE_VEICULOS 5
    #define INSERT_INTO_VEICULOS 7

    void createTableVeiculos(char *arquivoEntrada, char *arquivoSaida);
    void selectFromVeiculos(char *arquivoEntrada);
    void selectWhereVeiculos(char *arquivoEntrada, char *campo, char *valor);
    void insertIntoVeiculos(char *arquivoEntrada, int numeroRegistros);

#endif