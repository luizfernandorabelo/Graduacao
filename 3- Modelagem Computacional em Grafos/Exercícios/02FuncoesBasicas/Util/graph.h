#ifndef __GRAPH_H__
    #define __GRAPH_H__

    #include <iostream>
    #include <vector>

    #include "adjacencyMatrix.h"

    using std::cout;
    using std::pair;
    using std::vector;
    
    /* Classe para representação de um GRAFO SIMPLES. Implementação em graph.cpp */

    class Graph {

    public:
        AdjacencyMatrix adjacency_matrix;
        int total_vertices;

        Graph(int graph_total_vertices);

        int get_vertex_degree(int vertex);
        vector<int> get_vertex_adjacencies(int vertex);
        bool edge_exists(pair<int,int> coordinates);
    };

#endif
