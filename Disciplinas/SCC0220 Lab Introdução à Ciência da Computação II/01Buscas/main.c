#include <stdio.h>
#include <stdlib.h>

#include "myNumber.h"
#include "numberArrayAloc.h"
#include "mySearch.h"

int main(int argc, char *argv[]){

    //Leitura do Total de Registros e do Total de Buscas:
    int registersNumber = readInteger(stdin);
    int searchesNumber = readInteger(stdin);

    //Carregamento dos Registros para a Memória Heap:
    NUMBER_ARRAY *numberArray = loadNumberArray(registersNumber);

    //Busca(s) entre os Registros:
    for(int i = 0, searchType, keySearched, position; i < searchesNumber; i++){
        //Leitura do Tipo de Busca e da Chave Buscada:
        searchType = readInteger(stdin);
        keySearched = readInteger(stdin);        
        //Busca de Acordo com o Tipo:
        position = search(numberArray, keySearched, searchType);
        //Impressão da Posição:
        printf("%d\n", position);
    }

    //Liberação de Memória Alocada para os Registros:
    unloadNumberArray(numberArray);

    return 0;
}
