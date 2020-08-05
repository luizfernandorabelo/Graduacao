#include <stdio.h> 
#include <stdlib.h>

#define INTERACTION 0

int readNumber();
/*Função auxiliar que lê um número da entrada padrão e o retorna.*/

int **loadMatrix(int lines, int columns);
/*Função que lê a matriz da entrada padrão, a aloca dinamicamente e retorna seu endereço.
Tem como parâmetros o número de linhas e de colunas da matriz.*/

void checkMatrixDimensions(int lines, int columns);
/*Função que checa se o determinante da matriz existe e se sua ordem é compatível com
as suportadas pelo programa (1-3). Caso uma das condições não seja satisfeita, o programa
é abortado. Tem como parâmetros o número de linhas e de colunas da matriz.*/

int getDeterminant(int **matrix, int lines);
/*Função que calcula o determinante da matriz e o retorna. Tem como parâmetros o endereço 
da matriz da qual o determinante será calculado e seu número de linhas.*/

void freeMatrix(int **matrix, int lines);
/*Função que libera a memória alocada para o armazenamento da matriz. Tem como parâmetros
o endereço da matriz e seu número de linhas.*/

int main(int argc, char *argv[]){

    //Leitura e Armazenamento do número de Dimensões da Matriz:
    if(INTERACTION) printf("Digite o número de linhas da matriz: ");
    int lines = readNumber();
    if(INTERACTION) printf("Digite o número de colunas da matriz: ");
    int columns = readNumber();

    //Checagem de Possíveis Entradas Inválidas:
    checkMatrixDimensions(lines, columns);

    //Leitura e Armazenamento da Matriz:
    if(INTERACTION) printf("\nDigite cada um dos elementos da matriz:\n");
    int **matrix = loadMatrix(lines, columns);

    //Cálculo e Impressão do Determinante:
    int determinant = getDeterminant(matrix, lines);
    printf("O determinante da matriz de entrada equivale a %d e tem ordem %d\n", determinant, lines); 

    //Liberação de Memória Alocada:
    freeMatrix(matrix, lines);

    return 0;
}

int readNumber(){
    int number = 0;
    scanf("%d", &number);
    return(number);
}

int **loadMatrix(int lines, int colums){
    int **matrix = calloc(lines, sizeof(int *));
    for(int i = 0; i < colums; i++){
        matrix[i] = (int *) calloc (colums, sizeof(int));
        for(int j = 0; j < colums; j++){
            if(INTERACTION) printf("Elemento [%d][%d]: ", i+1, j+1);
            scanf("%d", &matrix[i][j]);
        }
    }
    return(matrix);
}

void checkMatrixDimensions(int lines, int colums){
    if(lines != colums || lines <= 0){
        printf("A matriz de entrada nao possui determinante!\n");
        exit(0);
    }
    if(lines > 3){
        printf("Entradas invalidas!\n");
        exit(0); 
    }
}

int getDeterminant(int **matrix, int lines){
    int determinant = 0;
    switch(lines){
        case 1: 
            determinant = matrix[0][0];
            break;
        case 2: 
            determinant = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
            break;
        case 3: 
            determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0];
            determinant += matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0];
            determinant += -matrix[0][0] * matrix[1][2] * matrix[2][1] - matrix[0][1] * matrix[1][0] * matrix[2][2];
            break;
        default: 
            break;
    }
    return(determinant);
}
    
void freeMatrix(int **matrix, int lines){
    for(int i = 0; i < lines; i++){
        free(matrix[i]);
    }
    free(matrix);
}