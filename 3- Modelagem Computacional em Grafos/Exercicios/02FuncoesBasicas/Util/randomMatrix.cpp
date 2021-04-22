#include <randomMatrix.h>

#include <iostream>
#include <stdlib.h>
#include <time.h>

using std::cout;


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

    cout << "  ";

    for (int i = 0; i < numberOfNodes; i++)
        cout << i + 1 << ' ';

    cout << "\n";

    for (int i = 0; i < numberOfNodes; i++) {
        cout << i + 1 << ' ';
        for (int j = 0; j < numberOfNodes; j++)
            cout << matrix[i][j] << ' ';
        cout << "\n";
    }
}


void free_matrix(int **matrix, int numberOfNodes) {

    for (int i = 0; i < numberOfNodes; i++)
        free(matrix[i]);
    
    free(matrix);
}