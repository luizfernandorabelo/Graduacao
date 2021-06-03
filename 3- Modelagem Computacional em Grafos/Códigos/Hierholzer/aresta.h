#ifndef __ARESTA_H__
    #define __ARESTA_H__

    #include <iostream>

    using std::cerr;

    class Aresta {
    public:
        Aresta(int idVerticeOrigem, int idVerticeDestino, int peso, bool marcada = false);
        int idVerticeOrigem;
        int idVerticeDestino;
        int peso;
        bool marcada;
    };

#endif