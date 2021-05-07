#ifndef __ADJACENCY_MATRIX_H__
    #define __ADJACENCY_MATRIX_H__

    #include <iostream>
    #include <cstdio>
    #include <cstdlib>

    using std::cout;
    using std::pair;

    /* Classe para representação de uma Matriz de Adjacências de um GRAFO SIMPLES. Implementação em adjacencyMatrix.cpp */

    class AdjacencyMatrix {

    private:
        int **table;

    public:
        int dimension;

        AdjacencyMatrix(int matrix_dimension);

        void print(FILE *stream);
        void fill_randomly(double connection_probability);
        void set_value(pair<int,int> coordinates, int value);
        int get_value(pair<int,int> coordinates);
        int **get_table(void);
    };

#endif