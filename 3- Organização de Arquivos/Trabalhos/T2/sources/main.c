// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#include <stdio.h>

#include "funcionalidadesLinhas.h"
#include "funcionalidadesVeiculos.h"


int main(int argc, char *argv[]) {

    int funcionalidade = 0;
    scanf("%d", &funcionalidade);

    if (funcionalidade == CREATE_INDEX_VEICULOS) {
        char nomeArquivoDados[100];
        char nomeArquivoIndice[100];
        scanf("%s %s", nomeArquivoDados, nomeArquivoIndice);
        createIndexVeiculos(nomeArquivoDados, nomeArquivoIndice);
    }
    else if (funcionalidade == CREATE_INDEX_LINHAS) {
        char nomeArquivoDados[100];
        char nomeArquivoIndice[100];
        scanf("%s %s", nomeArquivoDados, nomeArquivoIndice);
        createIndexLinhas(nomeArquivoDados, nomeArquivoIndice);
    }
    else if (funcionalidade == SELECT_WHERE_VEICULOS) {
        char nomeArquivoDados[100];
        char nomeArquivoIndice[100];
        char prefixo[100];
        char valor[100];
        scanf("%s %s %s", nomeArquivoDados, nomeArquivoIndice, prefixo);
        scan_quote_string(valor);
        selectWhereVeiculos(nomeArquivoDados, nomeArquivoIndice, prefixo, valor);
    }
    else if (funcionalidade == SELECT_WHERE_LINHAS) {
        char nomeArquivoDados[100];
        char nomeArquivoIndice[100];
        char codigoLinha[100];
        int valor;
        scanf("%s %s %s %d", nomeArquivoDados, nomeArquivoIndice, codigoLinha, &valor);
        selectWhereLinhas(nomeArquivoDados, nomeArquivoIndice, codigoLinha, valor);
    }
    else if (funcionalidade == INSERT_INTO_VEICULOS) {
        char nomeArquivoDados[100];
        char nomeArquivoIndice[100];
        int numeroRegistros;
        scanf("%s %s %d", nomeArquivoDados, nomeArquivoIndice, &numeroRegistros);
        insertIntoVeiculos(nomeArquivoDados, nomeArquivoIndice, numeroRegistros);
    } 
    else if (funcionalidade == INSERT_INTO_LINHAS) {
        char nomeArquivoDados[100];
        char nomeArquivoIndice[100];
        int numeroRegistros;
        scanf("%s %s %d", nomeArquivoDados, nomeArquivoIndice, &numeroRegistros);
        insertIntoLinhas(nomeArquivoDados, nomeArquivoIndice, numeroRegistros);
    } 
    else
        imprimeMensagemErro(stdout);
    
    return 0;
}