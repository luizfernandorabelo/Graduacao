#ifndef __GRAFO_H__
    #define __GRAFO_H__

    #include "aresta.h"

    #include <iostream>
    #include <stddef.h>
    #include <vector>

    using std::cerr;
    using std::cout;
    using std::vector;

    class Grafo {
    private:
        int totalVertices;
        int pesoNulo;
        bool direcionado;
        Aresta ***arestas;
    public:
        Grafo(int totalVertices, int pesoNulo = 0, bool direcionado = false);
        ~Grafo();
        int getTotalVertices(void);
        vector<Aresta*> getArestas(int idVertice); 
        int getGrau(int idVertice);
        void setPesoAresta(int idVerticeOrigem, int idVerticeDestino, int pesoNovo);
        void preencherAleatoriamente(double probabilidadeConexao);
        bool existeAresta(int idVerticeOrigem, int idVerticeDestino);
        void inserirAresta(Aresta *aresta);
        void removerAresta(int idVerticeOrigem, int idVerticeDestino);
        void imprimir(void);
    };

#endif