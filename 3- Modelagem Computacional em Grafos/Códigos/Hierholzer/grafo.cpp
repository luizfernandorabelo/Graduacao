#include "grafo.h"


list<Aresta*> *inicializarArestas(int totalVertices) {

    list<Aresta*> *arestas = new list<Aresta*>[totalVertices];

    return arestas;
}


Grafo::Grafo(int totalVertices, int pesoNulo) {

    if (totalVertices <= 0) {
        cerr << "Tentativa de criação de grafo com total de vértices inválido!\n";
        exit(EXIT_FAILURE);
    }

    this->totalVertices = totalVertices;
    this->pesoNulo = pesoNulo;

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

    totalVertices = 0;
    pesoNulo = 0;
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

    setPesoArestaNaoDirecionado(idVerticeOrigem, idVerticeDestino, pesoAntigo, pesoNovo, arestas);
}


bool Grafo::temCicloEuleriano(void) {

    for (int i = 0; i < totalVertices; i++)
        if (arestas[i].size() % 2 != 0)
            return false;

    return true;
}


vector<int> Grafo::obterCicloEuleriano(int idVerticeOrigem) {

    vector<int> ciclo;

    if (!idVerticeEhValido(idVerticeOrigem, 0, totalVertices-1)) {
        cerr << "Tentativa de acesso à vértice inválido!\n";
        return ciclo;
    }

    if (!temCicloEuleriano()) {
        cerr << "O grafo não possui ciclo euleriano!\n";
        return ciclo;
    }

    stack<int> pilha;
    pilha.push(idVerticeOrigem);

    while (pilha.size()) {

        int idVerticeTopo = pilha.top();
        list<Aresta*> arestasAdjacentes = arestas[idVerticeTopo];
        bool novoVerticeEmpilhado = false;

        for (list<Aresta*>::iterator it = arestasAdjacentes.begin(); it != arestasAdjacentes.end(); it++) {
            if (!(*it)->marcada) {
                (*it)->marcada = true;
                pilha.push((*it)->idVerticeDestino);
                novoVerticeEmpilhado = true;
                list<Aresta*> arestasSimetricas = arestas[(*it)->idVerticeDestino];
                for (it = arestasSimetricas.begin(); it != arestasSimetricas.end(); it++) {
                    if ((*it)->idVerticeDestino == idVerticeTopo)
                        (*it)->marcada = true;
                }
                break;
            }
        }

        if (!novoVerticeEmpilhado) {
            ciclo.push_back(pilha.top());
            pilha.pop();
        }
    }

    return ciclo;
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

    Aresta *arestaSimetrica = new Aresta(aresta->idVerticeDestino, aresta->idVerticeOrigem, aresta->peso);
    arestas[aresta->idVerticeDestino].push_back(arestaSimetrica);
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
