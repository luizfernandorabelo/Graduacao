#include <stdio.h>
#include "matrixPgm.h"

int main(int argc, char *argv[]){

    //Leitura e Armazenamento do Tamanho da Matriz, Posição Inicial e Semente:
    int matrixSize, rowStart, colStart, randomSeed;
    scanf("%d %d %d %d", &matrixSize, &rowStart, &colStart, &randomSeed);

    //Alocação de Memória e Inicialização da Matriz Original;
    MATRIX *originalMatrix = matrix_alocate(matrixSize);
    matrix_load_random_numbers(originalMatrix, randomSeed);

    //Alocação de Memória e Cópia dos Dados da Matriz Original para a Matriz Nova:
    MATRIX *newMatrix = matrix_alocate(matrixSize);
    matrix_copy(newMatrix, originalMatrix);

    //Alteração dos Valores da Matriz Nova:
    matrix_change_numbers(newMatrix, rowStart, colStart, randomSeed);

    //Impressão das Matrizes na Saída Padrão:
    matrix_print(originalMatrix, stdout, DEFAULT_FORMAT);
    printf("\n");
    matrix_print(newMatrix, stdout, DEFAULT_FORMAT);

    //Impressão das Matrizes em Arquivos de Formato PGM:
    FILE *fp1 = fopen("original.pgm", "w"); FILE *fp2 = fopen("nova.pgm", "w");
    matrix_print(originalMatrix, fp1, PGM_FORMAT);
    matrix_print(newMatrix, fp2, PGM_FORMAT);
    fclose(fp1); fclose(fp2);

    //Liberação de Memória Alocada para as Matrizes:
    matrix_free(&originalMatrix);
    matrix_free(&newMatrix);

    return(0);
}