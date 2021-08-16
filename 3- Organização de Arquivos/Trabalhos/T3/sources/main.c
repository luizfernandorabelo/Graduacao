// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#include <stdio.h>

#include "funcionalidades.h"

int main(int argc, char *argv[]) {

    int funcionalidade = 0;
    scanf("%d", &funcionalidade);

    if (funcionalidade == JUNCAO_LOOP_UNICO) {
        char nomeArqVeic[100];
        char nomeArqLinhas[100];
        char campoVeiculo[100];
        char campoLinha[100];
        scanf("%s %s %s %s", nomeArqVeic, nomeArqLinhas, campoVeiculo, campoLinha);
        juncaoLoopUnico(nomeArqVeic, nomeArqLinhas, campoVeiculo, campoLinha);
    }
    else if (funcionalidade == JUNCAO_ARQUIVO_INDICE) {
        char nomeArqVeic[100];
        char nomeArqLinhas[100];
        char campoVeiculo[100];
        char campoLinha[100];
        char nomeArqIndice[100];
        scanf("%s %s %s %s %s", nomeArqVeic, nomeArqLinhas, campoVeiculo, campoLinha, nomeArqIndice);
        juncaoArquivoIndice(nomeArqVeic, nomeArqLinhas, campoVeiculo, campoLinha, nomeArqIndice);
    }
    else if (funcionalidade == ORDENACAO_VEICULOS) {
        char nomeArqDesordenado[100];
        char nomeArqOrdenado[100];
        char campoOrdenacao[100];
        scanf("%s %s %s", nomeArqDesordenado, nomeArqOrdenado, campoOrdenacao);
        ordenacaoVeiculos(nomeArqDesordenado, nomeArqOrdenado, campoOrdenacao);
    }
    else if (funcionalidade == ORDENACAO_LINHAS) {
        char nomeArqDesordenado[100];
        char nomeArqOrdenado[100];
        char campoOrdenacao[100];
        scanf("%s %s %s", nomeArqDesordenado, nomeArqOrdenado, campoOrdenacao);
        ordenacaoLinhas(nomeArqDesordenado, nomeArqOrdenado, campoOrdenacao);
    }
    else if (funcionalidade == JUNCAO_ORDENADA) {
        char nomeArqVeic[100];
        char nomeArqLinhas[100];
        char campoVeiculo[100];
        char campoLinha[100];
        scanf("%s %s %s %s", nomeArqVeic, nomeArqLinhas, campoVeiculo, campoLinha);
        juncaoOrdenada(nomeArqVeic, nomeArqLinhas, campoVeiculo, campoLinha);
    } 
    else
        imprimeMensagemErro(stdout);
    
    return 0;
}