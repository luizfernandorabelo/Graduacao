#include "graph.h"


Graph::Graph(int graph_total_vertices) : adjacency_matrix(graph_total_vertices) {
    total_vertices = graph_total_vertices >= 0 ? graph_total_vertices : 0;
}


int Graph::get_vertex_degree(int vertex) {

    int degree = 0;

    for (int i = 1; i <= total_vertices; i++) 
        degree += adjacency_matrix.get_value(pair<int,int> (vertex, i));
    
    return degree;
}


vector<int> Graph::get_vertex_adjacencies(int vertex) {

    vector<int> adjacencies;

    for (int i = 1; i <= total_vertices; i++)
        if (edge_exists(pair<int,int> (vertex, i)))
            adjacencies.push_back(i);

    return adjacencies;
}


bool Graph::edge_exists(pair<int,int> coordinates) {
    return adjacency_matrix.get_value(coordinates) == 1;
}
