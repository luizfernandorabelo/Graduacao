#ifndef __GRAFO_H__
    #define __GRAFO_H__

    #include "aresta.h"

    #include <iostream>
    #include <stddef.h>
    #include <list>
    #include <vector>
    #include <stack>

    using std::cerr;
    using std::cout;
    using std::list;
    using std::vector;
    using std::stack;

    class Grafo {
    private:
        int totalVertices;
        int pesoNulo;
        bool direcionado;
        list<Aresta*> *arestas;
    public:
        Grafo(int totalVertices, int pesoNulo = 0);
        ~Grafo();
        int getTotalVertices(void);
        list<Aresta*> getArestas(int idVertice); 
        int getGrau(int idVertice);
        void setPesoAresta(int idVerticeOrigem, int idVerticeDestino, int pesoAntigo, int pesoNovo);
        bool temCicloEuleriano(void);
        vector<int> obterCicloEuleriano(int idVerticeOrigem); 
        bool existeAresta(int idVerticeOrigem, int idVerticeDestino);
        void inserirAresta(Aresta *aresta);
        void removerAresta(int idVerticeOrigem, int idVerticeDestino, int peso);
        void imprimir(void);
    };

#endif