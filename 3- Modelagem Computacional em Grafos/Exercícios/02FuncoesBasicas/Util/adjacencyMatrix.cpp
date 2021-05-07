#include "adjacencyMatrix.h"


int **alocate_table(int dimension) {

    if (dimension <= 0)
        return NULL;

    int **table = (int **) calloc(dimension, sizeof(int *));

    for (int i = 0; i < dimension; i++)
        table[i] = (int *) calloc(dimension, sizeof(int));
    
    return table;
}


AdjacencyMatrix::AdjacencyMatrix(int matrix_dimension) {
    dimension = matrix_dimension;
    table = alocate_table(dimension);
}


void AdjacencyMatrix::print(FILE *stream) {

    if (table == NULL) {
        fprintf(stream, "Could not print null matrix");
        return;
    }

    fprintf(stream, "  ");

    for (int i = 0; i < dimension; i++)
        fprintf(stream, "%d ", i+1);

    fprintf(stream, "\n");

    for (int i = 0; i < dimension; i++) {
        fprintf(stream, "%d ", i+1);
        for (int j = 0; j < dimension; j++)
            fprintf(stream, "%d ", table[i][j]);
        fprintf(stream, "\n");
    }
}


void AdjacencyMatrix::fill_randomly(double connection_probability) {

    if (table == NULL)
        return;

    srand(time(NULL));

    for (int i = 0; i < dimension; i++) {
        for (int j = i + 1; j < dimension; j++) {
            if (connection_probability * 100 >= rand() % 100) { table[i][j] = 1; table[j][i] = 1; }  
        }
    }
}


bool are_valid_coordinates(pair<int,int> coordinates, int min_range, int max_range) {

    if (coordinates.first < min_range || coordinates.first > max_range)
        return false;

    if (coordinates.second < min_range || coordinates.second > max_range)
        return false;

    return true;
} 


void AdjacencyMatrix::set_value(pair<int,int> coordinates, int value) {

    if (table == NULL || !are_valid_coordinates(coordinates, 1, dimension))
        return;
    
    table[coordinates.first-1][coordinates.second-1] = value;
    table[coordinates.second-1][coordinates.first-1] = value;
}


int AdjacencyMatrix::get_value(pair<int,int> coordinates) {

    if (table == NULL || !are_valid_coordinates(coordinates, 1, dimension))
        return -1;
    
    return table[coordinates.first-1][coordinates.second-1];
}


int **AdjacencyMatrix::get_table() {
    return table;
}
