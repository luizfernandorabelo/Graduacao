#ifndef __RANDOM_MATRIX_H__
    #define __RANDOM_MATRIX_H__

    /* Funções auxiliares para representar a matriz de adjacência aleatória de um grafo. Implementações no arquivo randomMatrix.cpp */

    int **create_new_random_matrix(int numberOfNodes, double connectionProbability);
    void print_matrix(int **matrix, int numberOfNodes);
    void free_matrix(int **matrix, int numberOfNodes);
    
#endif