#include "grafo.h"


Aresta ***inicializarArestas(int totalVertices, int pesoNulo) {

    Aresta ***arestas = new Aresta**[totalVertices];

    for (int i = 0; i < totalVertices; i++) {
        arestas[i] = new Aresta*[totalVertices];
        for (int j = 0; j < totalVertices; j++)
            arestas[i][j] = new Aresta(i, j, pesoNulo);
    }

    return arestas;
}


Grafo::Grafo(int totalVertices, int pesoNulo, bool direcionado) {

    if (totalVertices <= 0) {
        cerr << "Tentativa de criação de grafo com total de vértices inválido!\n";
        exit(EXIT_FAILURE);
    }

    this->totalVertices = totalVertices;
    this->pesoNulo = pesoNulo;
    this->direcionado = direcionado;

    arestas = inicializarArestas(totalVertices, pesoNulo);
}


Grafo::~Grafo(void) {

    for (int i = 0; i < totalVertices; i++) {
        for (int j = 0; j < totalVertices; j++)
            delete arestas[i][j];
        delete [] arestas[i];
    }

    delete [] arestas;

    totalVertices = 0;
    pesoNulo = 0;
    direcionado = false;
    arestas = NULL;
}


int Grafo::getTotalVertices(void) {
    return totalVertices;
}


bool idVerticeEhValido(int idVertice, int idMinimo, int idMaximo) {
    return idVertice >= idMinimo && idVertice <= idMaximo;
}


bool idsVerticesSaoValidos(int idVertice1, int idVertice2, int idMinimo, int idMaximo) {
    return idVerticeEhValido(idVertice1, idMinimo, idMaximo) &&
           idVerticeEhValido(idVertice2, idMinimo, idMaximo);
}


vector<Aresta*> Grafo::getArestas(int idVertice) {

    vector<Aresta*> arestasAdjacentes;

    if (!idVerticeEhValido(idVertice, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return arestasAdjacentes;
    }

    for (int i = 0; i < totalVertices; i++) {
        Aresta *arestaAtual = arestas[idVertice][i];
        if (arestaAtual->peso != pesoNulo)
            arestasAdjacentes.push_back(arestaAtual);
    }

    return arestasAdjacentes;
}


int Grafo::getGrau(int idVertice) {

    if (!idVerticeEhValido(idVertice, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return 0;
    }

    int grau = 0;

    for (int i = 0; i < totalVertices; i++)
        grau = arestas[idVertice][i]->peso != pesoNulo ? grau + 1 : grau;

    return grau; 
}


void Grafo::setPesoAresta(int idVerticeOrigem, int idVerticeDestino, int peso) {

    if (!idsVerticesSaoValidos(idVerticeOrigem, idVerticeDestino, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return;
    }

    arestas[idVerticeOrigem][idVerticeDestino]->peso = peso;

    if (!direcionado)
        arestas[idVerticeDestino][idVerticeOrigem]->peso = peso;
}


void Grafo::preencherAleatoriamente(double probabilidadeConexao) {

    for (int i = 0; i < totalVertices - 1; i++) {
        for (int j = i + 1; j < totalVertices; j++) {
            if (rand() % 100 <= probabilidadeConexao * 100) {
                Aresta *novaAresta = new Aresta(i, j, 1);
                inserirAresta(novaAresta);
            }
        }
    }
}


bool Grafo::existeAresta(int idVerticeOrigem, int idVerticeDestino) {

    if (!idsVerticesSaoValidos(idVerticeOrigem, idVerticeDestino, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return false;
    }

    return arestas[idVerticeOrigem][idVerticeDestino]->peso != pesoNulo;
}


void Grafo::inserirAresta(Aresta *aresta) {

    if (!idsVerticesSaoValidos(aresta->idVerticeOrigem, aresta->idVerticeDestino, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return;
    }

    delete arestas[aresta->idVerticeOrigem][aresta->idVerticeDestino];
    arestas[aresta->idVerticeOrigem][aresta->idVerticeDestino] = aresta;

    if (!direcionado) {
        Aresta *arestaSimetrica = new Aresta(aresta->idVerticeDestino, aresta->idVerticeOrigem, aresta->peso);
        delete arestas[aresta->idVerticeDestino][aresta->idVerticeOrigem];
        arestas[aresta->idVerticeDestino][aresta->idVerticeOrigem] = arestaSimetrica;

    }
}


void Grafo::removerAresta(int idVerticeOrigem, int idVerticeDestino) {

    if (!idsVerticesSaoValidos(idVerticeOrigem, idVerticeDestino, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return;
    }
    
    arestas[idVerticeOrigem][idVerticeDestino]->peso = pesoNulo;

    if (!direcionado)
        arestas[idVerticeDestino][idVerticeOrigem]->peso = pesoNulo;
}


void Grafo::imprimir(void) {

    cout << "  ";

    for (int i = 0; i < totalVertices; i++)
        cout << i << " ";
    cout << "\n";
    
    for (int i = 0; i < totalVertices; i++) {
        cout << i << " ";
        for (int j = 0; j < totalVertices; j++) {
            if (arestas[i][j] == NULL)
                cout << pesoNulo << " ";
            else
                cout << arestas[i][j]->peso << " ";
        }
        cout << "\n";
    }

    cout << "\n";
}
