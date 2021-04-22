#include "randomMatrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int **allocate_matrix(int dimension) {

    int **matrix = (int **) calloc(dimension, sizeof(int *));

    for (int i = 0; i < dimension; i++)
        matrix[i] = (int *) calloc(dimension, sizeof(int));
    
    return matrix;
}


int **create_new_random_matrix(int numberOfNodes, double connectionProbability) {
    
    int **matrix = allocate_matrix(numberOfNodes);

    srand(time(NULL));

    for (int i = 0; i < numberOfNodes; i++) {
        for (int j = i + 1; j < numberOfNodes; j++) {
            if (connectionProbability * 100 >= rand() % 100) {
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }  
        }
    }

    return matrix;
}


void print_matrix(int **matrix, int numberOfNodes) {

    for (int i = 0; i < numberOfNodes; i++) {
        for (int j = 0; j < numberOfNodes; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}


void free_matrix(int **matrix, int numberOfNodes) {

    for (int i = 0; i < numberOfNodes; i++)
        free(matrix[i]);
    
    free(matrix);
}