#include <iostream>
#include <vector>

#include "graph.h"
#include "readInputs.h"

using std::cout;
using std::vector;


int main(void) {

    cout << "n: ";
    int total_vertices = read_number_of_vertices(stdin);

    cout << "p: ";
    double connection_probability = read_connection_probability(stdin);

    srand(time(NULL));
    int random_vertex_1 = rand() % (total_vertices - 1) + 1;
    int random_vertex_2 = rand() % (total_vertices - 1) + 1;

    Graph myGraph(total_vertices);
    myGraph.adjacency_matrix.fill_randomly(connection_probability);

    cout << "\n\nMatriz de Adjacências:\n";
    myGraph.adjacency_matrix.print(stdout);

    cout << "\nO grau do vértice " << random_vertex_1 << " é " << myGraph.get_vertex_degree(random_vertex_1);

    cout << "\n\nVértices Adjacentes ao vértice " << random_vertex_1 << ": ";
    vector<int> adjacencies = myGraph.get_vertex_adjacencies(random_vertex_1);
    for (vector<int>::iterator i = adjacencies.begin(); i != adjacencies.end(); i++)
        cout << *i << ' ';

    cout << "\n\nExiste aresta entre os vértices " << random_vertex_1 << " e " << random_vertex_2 << "? ";
    if(myGraph.edge_exists(pair<int,int>(random_vertex_1,random_vertex_2))) cout << "sim\n";
    else cout << "nao\n";

    return 0;
}