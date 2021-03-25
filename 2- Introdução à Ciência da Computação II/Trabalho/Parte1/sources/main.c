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

    //Determinação do Número de Artistas e de Músicas:
    int numberOfArtists = serverGetNumberOfArtists(myServer);
    int numberOfTracks = serverGetNumberOfTracks(myServer);

    //Impressão de Dados na Saída Padrão:
    printf("O Dataset contem %d Artistas e %d Musicas\n", numberOfArtists, numberOfTracks);
    serverPrintArtistsByPopularity(myServer);

    //Liberação de Memória Alocada:
    serverFree(&myServer);

    return(0);
}