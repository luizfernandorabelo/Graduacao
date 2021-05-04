#include "readInputs.h"


int read_number_of_vertices(FILE *stream) {

    int total_vertices = 0;

    fscanf(stream, "%d", &total_vertices);

    while (total_vertices <= 0) {
        fprintf(stderr, "O número de vértices não pode ser <= 0. O valor deve ser inserido novamente\n");
        fscanf(stream, "%d", &total_vertices);
    }

    return total_vertices;
}


double read_connection_probability(FILE *stream) {

    double connection_probability = 0.0;

    fscanf(stream, "%lf", &connection_probability);

    while (connection_probability < 0 || connection_probability > 1) {
        fprintf(stderr, "A probabilidade precisa ser um número entre 0 e 1. O valor deve ser inserido novamente\n");
        fscanf(stream, "%lf", &connection_probability);
    }

    return connection_probability;
}