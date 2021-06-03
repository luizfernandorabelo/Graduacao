#include <iostream>
#include "grafo.h"


int main(void) {

    Grafo *meuGrafo = new Grafo(6);

    Aresta *aresta1 = new Aresta(0, 1, 1);
    Aresta *aresta2 = new Aresta(0, 3, 1);
    Aresta *aresta3 = new Aresta(1, 2, 1);
    Aresta *aresta4 = new Aresta(1, 4, 1);
    Aresta *aresta5 = new Aresta(1, 5, 1);
    Aresta *aresta6 = new Aresta(2, 3, 1);
    Aresta *aresta7 = new Aresta(2, 4, 1);
    Aresta *aresta8 = new Aresta(2, 5, 1);

    meuGrafo->inserirAresta(aresta1);
    meuGrafo->inserirAresta(aresta2);
    meuGrafo->inserirAresta(aresta3);
    meuGrafo->inserirAresta(aresta4);
    meuGrafo->inserirAresta(aresta5);
    meuGrafo->inserirAresta(aresta6);
    meuGrafo->inserirAresta(aresta7);
    meuGrafo->inserirAresta(aresta8);

    /*
         ___________
        |           | 
        V0   V4 __ V1 __ V5
        |     |     |    |
        |     | __ V2 __ |
        |           |
        |___ V3 ____| 

    */

    cout << "Estado do grafo:\n";
    meuGrafo->imprimir();

    vector<int> cicloEuleriano = meuGrafo->obterCicloEuleriano(0);

    cout << "Ciclo Euleriano partindo do vértice 0: ";
    for (int i = 0; i < cicloEuleriano.size(); i++)
        cout << cicloEuleriano[i] << " ";
    cout << "\n";

    return 0;
}