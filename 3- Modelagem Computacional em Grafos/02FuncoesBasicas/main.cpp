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

    int randomVertex1 = rand() % (total_vertices - 1) + 1; 
    int randomVertex2 = rand() % (total_vertices - 1) + 1; 

    cout << "\n\nMatriz de Adjacências:\n";
    myGraph.print_adjacency_matrix();

    cout << "\n\n\nO grau do Vértice " << randomVertex1 << " é " << myGraph.get_vertex_degree(randomVertex1);

    cout << "\n\n\nVértices Adjacentes ao vértice " << randomVertex1 << ": ";
    vector<int> adjacencies = myGraph.get_vertex_adjacencies(randomVertex1);
    for (vector<int>::iterator i = adjacencies.begin(); i != adjacencies.end(); i++)
        cout << *i << ' ';

    cout << "\n\n\nExiste aresta entre os vértices " << randomVertex1 << " e " << randomVertex2 << "? ";
    if(myGraph.edge_exists(pair<int,int>(randomVertex1,randomVertex2)))
        cout << "sim\n";
    else
        cout << "nao\n";

    return 0;
}