#include "aresta.h"

Aresta::Aresta(int idVerticeOrigem, int idVerticeDestino, int peso, bool marcada) {

    if (idVerticeOrigem < 0 || idVerticeDestino < 0) {
        cerr << "Tentativa de criação de aresta com dados inválidos!\n";
        exit(EXIT_FAILURE);
    }

    this->idVerticeOrigem = idVerticeOrigem;
    this->idVerticeDestino = idVerticeDestino;
    this->peso = peso;
    this->marcada = marcada;
}