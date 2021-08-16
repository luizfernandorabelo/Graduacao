#include <iostream>
#include "grafo.h"

using std::cout;
using std::cin;


int main(void) {

    Grafo *meuGafo = new Grafo(11, 0, true);

    Aresta *aresta0 = new Aresta(5, 9, 1);

    Aresta *aresta1 = new Aresta(7, 0, 1);
    Aresta *aresta2 = new Aresta(0, 3, 1);
    Aresta *aresta3 = new Aresta(3, 1, 1);
    Aresta *aresta4 = new Aresta(1, 4, 1);
    Aresta *aresta5 = new Aresta(4, 6, 1);
    Aresta *aresta6 = new Aresta(6, 2, 1);
    Aresta *aresta7 = new Aresta(2, 0, 1);

    Aresta *aresta8 = new Aresta(8, 10, 1);

    meuGafo->inserirAresta(aresta0);
    meuGafo->inserirAresta(aresta1);
    meuGafo->inserirAresta(aresta2);
    meuGafo->inserirAresta(aresta3);
    meuGafo->inserirAresta(aresta4);
    meuGafo->inserirAresta(aresta5);
    meuGafo->inserirAresta(aresta6);
    meuGafo->inserirAresta(aresta7);
    meuGafo->inserirAresta(aresta8);

    /*
        V9     V7 → V0 → V3 → V1      V8
        ↑           ↑         ↓       ↓
        V5          V2 ← V6 ← V4      V10
    */

    cout << "Estado do Grafo:\n";
    meuGafo->imprimir();

    cout << "O grafo contém algum ciclo?\n";
    if (meuGafo->existeCiclo())
        cout << "Sim!\n";
    else
        cout << "Não!\n";

    delete meuGafo;

    return 0;
}