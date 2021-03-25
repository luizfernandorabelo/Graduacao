#include "matrixPgm.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct matrix_{
    int size;
    int **pixels;
};


MATRIX *matrix_alocate(int size){

    MATRIX *matrix = malloc(sizeof(MATRIX));

    if(matrix != NULL){
        matrix->size = size;
        matrix->pixels = malloc(matrix->size * sizeof(int *));
        for(int i = 0; i < matrix->size; i++)
            matrix->pixels[i] = calloc(matrix->size, sizeof(int));
    }

    return(matrix);
}


void matrix_free(MATRIX **matrix){

    if(*matrix == NULL)
        return;

    for(int i = 0; i < (*matrix)->size; i++){
        free((*matrix)->pixels[i]); 
        (*matrix)->pixels[i] = NULL;
    }

    free((*matrix)->pixels); (*matrix)->pixels = NULL;
    free(*matrix); *matrix = NULL;
}


void matrix_load_random_numbers(MATRIX *matrix, int seed){

    if(matrix == NULL)
        return;
    
    srand(seed);

    for(int i = 0; i < matrix->size; i++)
        for(int j = 0; j < matrix->size; j++)
            matrix->pixels[i][j] = rand() % (MAX_VALUE+1);
}


void matrix_change_numbers_recursion(MATRIX *matrix, int initRow, int initCol, int currRow, int currCol, int seed){

    int **pixels = matrix->pixels, size = matrix->size;

    if(!(currRow == initRow && currCol == initCol)){ //se não for a posição de início
        if(currRow < 0 || currRow >= size || currCol < 0 || currCol >= size) return; 
        if(pixels[currRow][currCol] == pixels[initRow][initCol]) return; 
        if(abs(pixels[currRow][currCol] - pixels[initRow][initCol]) > seed) return;
        pixels[currRow][currCol] = pixels[initRow][initCol];
    } 

    matrix_change_numbers_recursion(matrix, initRow, initCol, currRow-1, currCol, seed); //cima
    matrix_change_numbers_recursion(matrix, initRow, initCol, currRow, currCol+1, seed); //direita
    matrix_change_numbers_recursion(matrix, initRow, initCol, currRow+1, currCol, seed); //baixo
    matrix_change_numbers_recursion(matrix, initRow, initCol, currRow, currCol-1, seed); //esquerda
}


void matrix_change_numbers(MATRIX *matrix, int rowStart, int colStart, int seed){
    if(matrix != NULL && seed > 0)
        return (matrix_change_numbers_recursion(matrix, rowStart, colStart, rowStart, colStart, seed));
}


void matrix_copy(MATRIX *matrixDest, MATRIX *matrixOrign){

    if(matrixDest == NULL || matrixOrign == NULL)
        return;

    for(int i = 0; i < matrixOrign->size; i++)
        for(int j = 0; j < matrixOrign->size; j++)
            matrixDest->pixels[i][j] = matrixOrign->pixels[i][j];
}


void matrix_print_default_format(MATRIX *matrix, FILE *fp){

    for(int i = 0; i < matrix->size; i++){ 
        for(int j = 0; j < matrix->size; j++)
            fprintf(fp, "%d\t", matrix->pixels[i][j]);
        fprintf(fp, "\n");
    }
}


void matrix_print_pgm_format(MATRIX *matrix, FILE *fp){

    fprintf(fp, "P2\n%d %d\n%d\n", matrix->size, matrix->size, MAX_VALUE);
    
    for(int i = 0; i < matrix->size; i++){ 
        for(int j = 0; j < matrix->size; j++)
            fprintf(fp, "%d ", matrix->pixels[i][j]);
        fprintf(fp, "\n");
    }
}


void matrix_print(MATRIX *matrix, FILE *fp, int writeFormat){

    if(matrix != NULL){
        switch(writeFormat){
            case DEFAULT_FORMAT:
                return(matrix_print_default_format(matrix, fp));
            case PGM_FORMAT:
                return(matrix_print_pgm_format(matrix, fp));
            default:
                printf("Formato de empressão inválido\n");
        }
    }
}