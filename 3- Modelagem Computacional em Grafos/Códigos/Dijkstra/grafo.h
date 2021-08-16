#ifndef __GRAFO_H__
    #define __GRAFO_H__

    #include "aresta.h"

    #include <iostream>
    #include <stddef.h>
    #include <vector>
    #include <cstring>
    #include <queue>

    using std::cerr;
    using std::cout;
    using std::vector;
    using std::priority_queue;
    using std::pair;
    using std::make_pair;
    using std::greater;

    class Grafo {
    private:
        int totalVertices;
        int pesoNulo;
        bool direcionado;
        bool *marcacoes;
        Aresta ***arestas;
    public:
        Grafo(int totalVertices, int pesoNulo = 0, bool direcionado = false);
        ~Grafo();
        int getTotalVertices(void);
        vector<Aresta*> getArestas(int idVertice); 
        int getGrau(int idVertice);
        unsigned int **getDistancias(void);
        void setPesoAresta(int idVerticeOrigem, int idVerticeDestino, int pesoNovo);
        bool existeAresta(int idVerticeOrigem, int idVerticeDestino);
        void inserirAresta(Aresta *aresta);
        void removerAresta(int idVerticeOrigem, int idVerticeDestino);
        void imprimir(void);
    };

#endif