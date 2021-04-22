#include "readInputs.h"
#include "myGraph.h"

#include <iostream>

using std::cout;
using std::vector;
using std::pair;


int main() {

    int total_vertices = read_number_of_vertices_from_stdin();
    double connection_probability = read_connection_probability_from_stdin();

    Graph myGraph(total_vertices, connection_probability);

    cout << "\n\nMatriz de Adjacências:\n";
    myGraph.print_adjacency_matrix();

    cout << "\n\n\nO grau do Vértice 1 é " << myGraph.get_vertex_degree(1);

    cout << "\n\n\nVértices Adjacentes ao vértice 1:\n";
    vector<int> adjacencies = myGraph.get_vertex_adjacencies(1);
    for (vector<int>::iterator i = adjacencies.begin(); i != adjacencies.end(); i++)
        cout << *i << ' ';

    cout << "\n\n\nExiste aresta entre os vértices 1 e 5? ";
    if(myGraph.edge_exists(pair<int,int>(1,5)))
        cout << "sim\n";
    else
        cout << "nao\n";

    return 0;
}