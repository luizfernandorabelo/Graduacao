#include <iostream>
#include "grafo.h"

using std::cout;
using std::cin;


int main(void) {

    Grafo *meuGafo = new Grafo(5);

    Aresta *aresta1 = new Aresta(0, 1, 1);
    Aresta *aresta2 = new Aresta(0, 2, 1);
    Aresta *aresta3 = new Aresta(0, 3, 1);
    Aresta *aresta4 = new Aresta(3, 4, 1);

    meuGafo->inserirAresta(aresta1);
    meuGafo->inserirAresta(aresta2);
    meuGafo->inserirAresta(aresta3);
    meuGafo->inserirAresta(aresta4);

    /*
        V1 __ V0 __ V3
              |     |
              V2    V4
    */

    cout << "Estado do Grafo:\n";
    meuGafo->imprimir();

    cout << "Matriz de Distâncias:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << meuGafo->bfs(i, j) << " ";
        cout << "\n";
    }

    delete meuGafo;

    return 0;
}