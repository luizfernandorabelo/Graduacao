#include <iostream>
#include "grafo.h"

using std::cout;
using std::cin;


int main(void) {

    // Lendo o número de vértices:
    cout << "n: ";
    int totalVertices = 0;
    cin >> totalVertices;

    // Lendo a probabilidade de conexão:
    cout << "p: ";
    double probabilidadeConexao = 0.0;
    cin >> probabilidadeConexao;

    // Gerando 2 ids de vértices aleatórios:
    srand(time(NULL));
    int rand1 = totalVertices > 1 ? rand() % (totalVertices - 1) + 1 : totalVertices;
    int rand2 = totalVertices > 1 ? rand() % (totalVertices - 1) + 1 : totalVertices;
    
    // Criando um grafo:
    Grafo *meuGrafo = new Grafo(totalVertices);
    cout << "\nGrafo Inicial:\n";
    meuGrafo->imprimir();

    // Preenchendo o grafo aleatoriamente:
    meuGrafo->preencherAleatoriamente(probabilidadeConexao);
    cout << "Grafo Aleatório:\n";
    meuGrafo->imprimir();

    // Vertificando se existe aresta entre os dois vértices aleatórios:
    cout << "\nExiste aresta entre " << rand1 << " e " << rand2 << "? ";
    if (meuGrafo->existeAresta(rand1, rand2)) cout << "sim\n";
    else cout << "nao\n";

    // Removendo aresta entre os dois vértices aleatórios:
    meuGrafo->removerAresta(rand1, rand2);
    cout << "Grafo após remover aresta entre " << rand1 << " e " << rand2 << "\n";
    meuGrafo->imprimir();

    // Obtendo o grau do primeiro vértice aleatório:
    cout << "O grau do vértice " << rand1 << " é " << meuGrafo->getGrau(rand1) << "\n";

    // Obtendo as arestas do primeiro vértice aleatório:
    cout << "\nVértices relacionados ao vértice " << rand1 << ": ";
    vector<Aresta*> arestas = meuGrafo->getArestas(rand1);
    for (vector<Aresta*>::iterator it = arestas.begin(); it != arestas.end(); it++)
        cout << (*it)->idVerticeDestino << " ";
    cout << "\n";

    // Vertificando se existe aresta entre os dois vértices aleatórios:
    cout << "\nExiste aresta entre " << rand1 << " e " << rand2 << "? ";
    if (meuGrafo->existeAresta(rand1, rand2)) cout << "sim\n";
    else cout << "nao\n";

    // Liberando memória alocada:
    delete meuGrafo;

    return 0;
}
