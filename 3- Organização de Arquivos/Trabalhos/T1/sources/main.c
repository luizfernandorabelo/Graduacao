#include <stdio.h>

#include "funcionalidadesLinhas.h"
#include "funcionalidadesVeiculos.h"


int main(int argc, char *argv[]) {

    int funcionalidade = 0;
    scanf("%d", &funcionalidade);
    
    if (funcionalidade == CREATE_TABLE_VEICULOS) {
        char arquivoEntrada[100];
        char arquivoSaida[100];
        scanf("%s %s", arquivoEntrada, arquivoSaida);
        createTableVeiculos(arquivoEntrada, arquivoSaida);
    }
    else if (funcionalidade == CREATE_TABLE_LINHAS) {
        char arquivoEntrada[100];
        char arquivoSaida[100];
        scanf("%s %s", arquivoEntrada, arquivoSaida);
        createTableLinhas(arquivoEntrada, arquivoSaida);
    }
    else if (funcionalidade == SELECT_FROM_VEICULOS) {
        char arquivoEntrada[100];
        scanf("%s", arquivoEntrada);
        selectFromVeiculos(arquivoEntrada);
    }
    else if (funcionalidade == SELECT_FROM_LINHAS) {
        char arquivoEntrada[100];
        scanf("%s", arquivoEntrada);
        selectFromLinhas(arquivoEntrada);
    }
    else if (funcionalidade == SELECT_WHERE_VEICULOS) {
        char arquivoEntrada[100];
        char nomeCampo[100];
        char valor[100];
        scanf("%s %s", arquivoEntrada, nomeCampo);
        scan_quote_string(valor);
        selectWhereVeiculos(arquivoEntrada, nomeCampo, valor);
    }
    else if (funcionalidade == SELECT_WHERE_LINHAS) {
        char arquivoEntrada[100];
        char nomeCampo[100];
        char valor[100];
        scanf("%s %s", arquivoEntrada, nomeCampo);
        scan_quote_string(valor);
        selectWhereLinhas(arquivoEntrada, nomeCampo, valor);
    }
    else if (funcionalidade ==  INSERT_INTO_VEICULOS) {
        char arquivoEntrada[100];
        int numeroRegistros;
        scanf("%s %d", arquivoEntrada, &numeroRegistros);
        insertIntoVeiculos(arquivoEntrada, numeroRegistros);
    }
    else if(funcionalidade == INSERT_INTO_LINHAS) {
        char arquivoEntrada[100];
        int numeroRegistros;
        scanf("%s %d", arquivoEntrada, &numeroRegistros);
        insertIntoLinhas(arquivoEntrada, numeroRegistros);
    }
    else 
        imprimeMensagemErro(stdout);

    return 0;
}