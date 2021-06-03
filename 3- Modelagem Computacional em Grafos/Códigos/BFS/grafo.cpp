#include "grafo.h"


bool *inicializarMarcacoes(int totalVertices) {

    bool *marcacoes = new bool[totalVertices];

    for (int i = 0; i < totalVertices; i++)
        marcacoes[i] = false;
    
    return marcacoes;
}


list<Aresta*> *inicializarArestas(int totalVertices) {

    list<Aresta*> *arestas = new list<Aresta*>[totalVertices];

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

    marcacoes = inicializarMarcacoes(totalVertices);
    arestas = inicializarArestas(totalVertices);
}


Grafo::~Grafo(void) {

    for (int i = 0; i < totalVertices; i++) {
        while (arestas[i].size()) {
            Aresta *arestaAtual = arestas[i].front();
            arestas[i].pop_front();
            delete arestaAtual;
        }
    }
    
    delete [] arestas;
    delete [] marcacoes;

    totalVertices = 0;
    pesoNulo = 0;
    direcionado = false;
    arestas = NULL;
    marcacoes = NULL;
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


list<Aresta*> Grafo::getArestas(int idVertice) {

    if (!idVerticeEhValido(idVertice, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        list<Aresta*> listaVazia;
        return listaVazia;
    }

    return arestas[idVertice];
}


int Grafo::getGrau(int idVertice) {

    if (!idVerticeEhValido(idVertice, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return 0;
    }
    
    return arestas[idVertice].size();
}


void setPesoArestaDirecionado(int idVerticeOrigem, int idVerticeDestino, int pesoAntigo, int pesoNovo, list<Aresta*> *arestas) {

    list<Aresta*> lista = arestas[idVerticeOrigem];

    for (list<Aresta*>::iterator it = lista.begin(); it != lista.end(); it++) {
        Aresta *arestaAtual = *it;
        if (arestaAtual->idVerticeDestino == idVerticeDestino && arestaAtual->peso == pesoAntigo) {
            arestaAtual->peso = pesoNovo;
            break;
        }
    }
}


void setPesoArestaNaoDirecionado(int idVerticeOrigem, int idVerticeDestino, int pesoAntigo, int pesoNovo, list<Aresta*> *arestas) {
    setPesoArestaDirecionado(idVerticeOrigem, idVerticeDestino, pesoAntigo, pesoNovo, arestas);
    setPesoArestaDirecionado(idVerticeDestino, idVerticeOrigem, pesoAntigo, pesoNovo, arestas);
}


void Grafo::setPesoAresta(int idVerticeOrigem, int idVerticeDestino, int pesoAntigo, int pesoNovo) {

    if (!idsVerticesSaoValidos(idVerticeOrigem, idVerticeDestino, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return;
    }

    if (direcionado)
        setPesoArestaDirecionado(idVerticeOrigem, idVerticeDestino, pesoAntigo, pesoNovo, arestas);
    else
        setPesoArestaNaoDirecionado(idVerticeOrigem, idVerticeDestino, pesoAntigo, pesoNovo, arestas);
}


int *inicializarCaminhoBfs(int grafoTotalVertices) {

    int *caminho = new int[grafoTotalVertices];

    for (int i = 0; i < grafoTotalVertices; i++)
        caminho[i] = ID_NULO;

    return caminho;
}


int obterDistanciaCaminhoBfs(int *caminho, int totalVertices, int idVerticeOrigem, int idVerticeDestino) {

    int distancia = 0;
    int idVerticeAtual = idVerticeDestino;

    while (idVerticeAtual != ID_NULO) {
        if (idVerticeAtual == idVerticeOrigem)
            return distancia;
        idVerticeAtual = caminho[idVerticeAtual];
        distancia++;
    }

    return 0;
}


void limparMarcacoes(bool *marcacoes, int totalVertices) {
    for (int i = 0; i < totalVertices; i++)
        marcacoes[i] = false;
}


int Grafo::bfs(int idVerticeOrigem, int idVerticeDestino) {

    int *caminho = inicializarCaminhoBfs(totalVertices);

    limparMarcacoes(marcacoes, totalVertices);
    marcacoes[idVerticeOrigem] = true;

    queue<int> fila;
    fila.push(idVerticeOrigem);

    while (fila.size()) {
        int idVerticeAtual = fila.front();
        fila.pop();
        list<Aresta*> arestasAtual = getArestas(idVerticeAtual);
        for (list<Aresta*>::iterator it = arestasAtual.begin(); it != arestasAtual.end(); it++) {
            int idVerticeVizinho = (*it)->idVerticeDestino;
            if (!marcacoes[idVerticeVizinho]) {
                marcacoes[idVerticeVizinho] = true;
                fila.push(idVerticeVizinho);
                caminho[idVerticeVizinho] = idVerticeAtual;
            }
            if (idVerticeVizinho == idVerticeDestino) {
                int distancia = obterDistanciaCaminhoBfs(caminho, totalVertices, idVerticeOrigem, idVerticeDestino);
                delete [] caminho;
                return distancia;
            }
        }
    }

    return 0;
}


bool Grafo::existeAresta(int idVerticeOrigem, int idVerticeDestino) {

    if (!idsVerticesSaoValidos(idVerticeOrigem, idVerticeDestino, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return false;
    }

    list<Aresta*> lista = arestas[idVerticeOrigem];

    for (list<Aresta*>::iterator it = lista.begin(); it != lista.end(); it++) {
        Aresta *arestaAtual = *it;
        if (arestaAtual->idVerticeDestino == idVerticeDestino)
            return true;
    }

    return false;
}


void Grafo::inserirAresta(Aresta *aresta) {

    if (!idsVerticesSaoValidos(aresta->idVerticeOrigem, aresta->idVerticeDestino, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return;
    }

    arestas[aresta->idVerticeOrigem].push_back(aresta);

    if (!direcionado) {
        Aresta *arestaSimetrica = new Aresta(aresta->idVerticeDestino, aresta->idVerticeOrigem, aresta->peso);
        arestas[aresta->idVerticeDestino].push_back(arestaSimetrica);
    }
}


void removerArestaDirecionado(int idVerticeOrigem, int idVerticeDestino, int peso, list<Aresta*> *arestas) {

    list<Aresta*>::iterator it = arestas[idVerticeOrigem].begin();
    
    for (it; it != arestas[idVerticeOrigem].end(); it++) {
        Aresta *arestaAtual = *it;
        if (arestaAtual->idVerticeDestino == idVerticeDestino && arestaAtual->peso == peso) {
            arestas[idVerticeOrigem].erase(it); 
            delete arestaAtual; 
            break;
        }
    }
}


void removerArestaNaoDirecionado(int idVerticeOrigem, int idVerticeDestino, int peso, list<Aresta*> *arestas) {
    removerArestaDirecionado(idVerticeOrigem, idVerticeDestino, peso, arestas);
    removerArestaDirecionado(idVerticeDestino, idVerticeOrigem, peso, arestas);
}


void Grafo::removerAresta(int idVerticeOrigem, int idVerticeDestino, int peso) {

    if (!idsVerticesSaoValidos(idVerticeOrigem, idVerticeDestino, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return;
    }

    if (direcionado)
        removerArestaDirecionado(idVerticeOrigem, idVerticeDestino, peso, arestas);
    else
        removerArestaNaoDirecionado(idVerticeOrigem, idVerticeDestino, peso, arestas);
}


void imprimirList(list<Aresta*>& lista) {

    list<Aresta*>::iterator iteradorAtual = lista.begin();
    list<Aresta*>::iterator iteradorFinal = lista.end();

    while (iteradorAtual != iteradorFinal) {
        cout << "V" << (*iteradorAtual)->idVerticeDestino << ": ";
        cout << (*iteradorAtual)->peso << "; ";
        iteradorAtual++;
    }

    cout << "\n";
}


void Grafo::imprimir(void) {

    for (int i = 0; i < totalVertices; i++) {
        cout << "V" << i << " -> ";
        imprimirList(arestas[i]);
    }

    cout << "\n";
}
