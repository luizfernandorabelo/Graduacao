/*  
    Programa de Teste das Funcionalidades Implementadas para o Grafo

    Passos:
        1) são lidos da entrada padrão os valores de n e p;
        2) são escolhidos dois vértices aleatórios para teste (random_vertex 1 e 2);
        3) o objeto myGraph é instanciado com o valor de n;
        3) a matriz de adjacências é preenchida aleatóriamente com o valor de p e é impressa na saída padrão;
        4) é calculado e impresso o grau do vértice aleatório 1;
        5) é obtida e impressa a lista dos vértices adjacentes ao vértice aleatório 1;
        6) é verificado e impresso se existe aresta entre os vértices aleatórios 1 e 2;
*/


#include <iostream>
#include <vector>

#include "graph.h"

using std::cout;
using std::cin;
using std::vector;


int main(void) {

    cout << "n: ";
    int total_vertices = 0;
    cin >> total_vertices;

    cout << "p: ";
    double connection_probability = 0.0;
    cin >> connection_probability;

    srand(time(NULL));
    int random_vertex_1 = total_vertices > 1 ? rand() % (total_vertices - 1) + 1 : total_vertices;
    int random_vertex_2 = total_vertices > 1 ? rand() % (total_vertices - 1) + 1 : total_vertices;

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
