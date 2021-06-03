#ifndef __GRAFO_H__
    #define __GRAFO_H__

    #include "aresta.h"

    #include <iostream>
    #include <stddef.h>
    #include <list>
    #include <queue>

    #define ID_NULO -1

    using std::cerr;
    using std::cout;
    using std::list;
    using std::queue;

    class Grafo {
    private:
        int totalVertices;
        int pesoNulo;
        bool direcionado;
        bool *marcacoes;
        list<Aresta*> *arestas;
    public:
        Grafo(int totalVertices, int pesoNulo = 0, bool direcionado = false);
        ~Grafo();
        int getTotalVertices(void);
        list<Aresta*> getArestas(int idVertice); 
        int getGrau(int idVertice);
        void setPesoAresta(int idVerticeOrigem, int idVerticeDestino, int pesoAntigo, int pesoNovo);
        int bfs(int idVerticeOrigem, int idVerticeDestino);
        bool existeAresta(int idVerticeOrigem, int idVerticeDestino);
        void inserirAresta(Aresta *aresta);
        void removerAresta(int idVerticeOrigem, int idVerticeDestino, int peso);
        void imprimir(void);
    };

#endif