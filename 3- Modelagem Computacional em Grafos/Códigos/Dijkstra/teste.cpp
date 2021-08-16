#include <iostream>
#include "grafo.h"

using std::cout;
using std::cin;


int main(void) {

    Grafo *meuGrafo = new Grafo(11, 0, true);

    Aresta *aresta0 = new Aresta(0, 1, 7);
    Aresta *aresta1 = new Aresta(0, 2, 2);
    Aresta *aresta2 = new Aresta(2, 3, 1);
    Aresta *aresta3 = new Aresta(3, 1, 2);
    Aresta *aresta4 = new Aresta(1, 4, 1);
    Aresta *aresta5 = new Aresta(4, 6, 2);
    Aresta *aresta6 = new Aresta(4, 5, 3);
    Aresta *aresta7 = new Aresta(6, 7, 5);
    Aresta *aresta8 = new Aresta(7, 5, 4);
    Aresta *aresta9 = new Aresta(7, 8, 1);
    Aresta *aresta10 = new Aresta(8, 9, 3);
    Aresta *aresta11 = new Aresta(9, 5, 4);

    meuGrafo->inserirAresta(aresta0);
    meuGrafo->inserirAresta(aresta1);
    meuGrafo->inserirAresta(aresta2);
    meuGrafo->inserirAresta(aresta3);
    meuGrafo->inserirAresta(aresta4);
    meuGrafo->inserirAresta(aresta5);
    meuGrafo->inserirAresta(aresta6);
    meuGrafo->inserirAresta(aresta7);
    meuGrafo->inserirAresta(aresta8);
    meuGrafo->inserirAresta(aresta9);
    meuGrafo->inserirAresta(aresta10);
    meuGrafo->inserirAresta(aresta11);

    /* 
             7       1       3       4
        V00  →  V01  →  V04  →  V05  ←  V09
        2 ↓     2 ↑     2 ↓     4 ↑     3 ↑      V10
        V02  →  V03     V06  →  V07  →  V08
             1               5       1
    */

    cout << "Matriz de Distâncias:\n";

    unsigned int **distancias = meuGrafo->getDistancias();

    for (int i = 0; i < meuGrafo->getTotalVertices(); i++) {
        for (int j = 0; j < meuGrafo->getTotalVertices(); j++)
            if (distancias[i][j] >= INT32_MAX)
                cout << "inf\t";
            else
                cout << distancias[i][j] << '\t';
        cout << '\n';
    }

    delete meuGrafo;

    return 0;
}
