#include "matrizEsparsa.h"
#include "item.h"

#include <stdio.h>

void testarImpressao(ME *matriz){
    printf("\n-> Atualmente, esse é o estado da matriz:\n");    
    matriz_imprimir(matriz);
}

void testarInsercao(ME *matriz, int chave, int linha, int coluna){
    ITEM *buffer = item_criar(chave);
    printf("\nInserindo item na matriz...\n");
    if(buffer != NULL && matriz_inserir(matriz, linha, coluna, buffer) == True)
        printf("Item de chave %.2d inserido em (%d, %d)!\n", item_obter_chave(buffer), linha, coluna);
    else
        printf("Erro na inserção do item de chave %d\n", item_obter_chave(buffer));
    testarImpressao(matriz);
}

void testarRemocao(ME *matriz, int linha, int coluna){
    printf("\nRemovendo item da matriz...\n");
    if(matriz_remover_item(matriz, linha, coluna) == True)
        printf("O item de coordenadas (%d, %d) foi removido!\n", linha, coluna);
    else 
        printf("O elemento de coordenadas (%d, %d) NAO foi removido!\n", linha, coluna);    
    testarImpressao(matriz);
}

void testarBusca(ME *matriz, int linha, int coluna){
    printf("\nBuscando item...\n");
    if(matriz_obter_item(matriz, linha, coluna) != NULL)
        printf("O item de coordenadas (%d, %d) foi retornado pela função \"matriz_obter_item()\"!\n", linha, coluna);
    else 
        printf("A função \"matriz_obter_item()\" retornou NULO. O item (%d,%d) não foi encontrado!\n", linha, coluna);
}

int main(int argc, char *argv[]){

    printf("\nCriando matriz...\n");
    ME *matriz = matriz_criar(5, 5, 0);
    printf("%s!\n", (matriz != NULL) ? "Matriz criada" : "Matriz NAO criada");

    testarInsercao(matriz, 15, 0, 2);
    testarInsercao(matriz, 13, 1, 2);
    testarInsercao(matriz, 7, 2, 1);
    testarInsercao(matriz, 2, 4, 1);
    testarInsercao(matriz, 26, 1, 1);
    testarInsercao(matriz, 4, 4, 0);
    testarInsercao(matriz, 11, 2, 3);
    testarInsercao(matriz, 17, 3, 4);

    testarRemocao(matriz, -1, 4);
    testarRemocao(matriz, 2, 3);
    testarRemocao(matriz, 1, 2);
    testarRemocao(matriz, 2, 1);
    testarRemocao(matriz, 0, 0);

    testarInsercao(matriz, 25, 1, 2);
    testarInsercao(matriz, 18, 3, 4);

    testarBusca(matriz, 6, 0);
    testarBusca(matriz, 4, 4);
    testarBusca(matriz, 0, 2);
    testarBusca(matriz, 1, 2);
    testarBusca(matriz, 2, 1);
    testarBusca(matriz, 4, 1);
    testarBusca(matriz, 1, 1);
    testarBusca(matriz, 4, 0);
    testarBusca(matriz, 2, 3);
    testarBusca(matriz, 3, 4);
 
    printf("\nApagando matriz...\n");
    printf("\n%s!\n", (matriz_apagar(&matriz) == True) ? "Matriz apagada" : "Matriz NAO apagada");
    
    return(0);
}