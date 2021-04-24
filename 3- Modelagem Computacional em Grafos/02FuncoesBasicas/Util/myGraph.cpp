#include "randomMatrix.h"
#include "myGraph.h"

#include <iostream>


Graph::Graph(int totalVertices, double edgeConnectionProbability) {
    total_vertices = totalVertices;
    edge_connection_probability = edgeConnectionProbability;
    adjacency_matrix = create_new_random_matrix(totalVertices, edgeConnectionProbability);
}


void Graph::print_adjacency_matrix() {
    print_matrix(adjacency_matrix, total_vertices);
}


bool is_valid_index(int index, int min_range, int max_range) {
    return index >= min_range && index <= max_range;
} 


bool are_valid_coordinates(std::pair<int,int> coordinates, int min_range, int max_range) {
    return is_valid_index(coordinates.first, min_range, max_range) &&
           is_valid_index(coordinates.second, min_range, max_range);
}


int Graph::get_vertex_degree(int vertex) {

    int degree = 0;

    if (is_valid_index(vertex, 1, total_vertices)) {
        int row = vertex - 1;
        for (int col = 0; col < total_vertices; col++)
            degree += adjacency_matrix[row][col];
    }

    return degree;
}


std::vector<int> Graph::get_vertex_adjacencies(int vertex) {

    std::vector<int> adjacencies(0);

    if (is_valid_index(vertex, 1, total_vertices)) {
        int row = vertex - 1;
        for (int col = 0; col < total_vertices; col++)
            if (adjacency_matrix[row][col] != 0)
                adjacencies.push_back(col + 1);
    }

    return adjacencies;        
}


bool Graph::edge_exists(std::pair<int,int> coordinates) { 

    if (are_valid_coordinates(coordinates, 1, total_vertices)) 
        return adjacency_matrix[coordinates.first-1][coordinates.second-1] != 0;
    
    return false;
}