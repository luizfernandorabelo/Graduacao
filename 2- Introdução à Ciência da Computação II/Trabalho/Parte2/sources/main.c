#include <stdio.h>
#include <time.h>
#include "server.h"

int main(int argc, char *argv[]){

    //Leitura e Armazenamento do Nome do Arquivo de Dados CSV:
    char csvFileName[20]; scanf("%s", csvFileName);
    
    //Alocação de Memória para o "Servidor":
    SERVER *myServer = serverALocate();

    //Carregamento dos Dados do Arquivo CSV para o Servidor:
    serverLoadFromCsvFile(myServer, csvFileName);

    //Leitura do Número de Buscas e de Músicas Similares:
    int totalSearches = 0, totalSimilar = 0;
    scanf("%d %d", &totalSearches, &totalSimilar);

    //Leitura dos Id's das Músicas e Impressão das Mais Similares na Saída Padrão:
    for(int i = 0; i < totalSearches; i++){
        char trackId[20]; scanf("%s", trackId);
        serverPrintMostSimilarTracks(myServer, trackId, totalSimilar);
    }

    //Liberação de Memória Alocada:
    serverFree(&myServer);

    return(0);
}