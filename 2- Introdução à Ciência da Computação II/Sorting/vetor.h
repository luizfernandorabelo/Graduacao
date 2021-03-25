#ifndef VETOR_H
    #define VETOR_H

    typedef struct{
        int *chaves;
        int tamanho;
    }VETOR;

    #include <stdio.h>

    VETOR *gerar_vetor(int min, int max, int tamanho);
    void imprimir_vetor(VETOR *vetor, FILE *stream);
    void liberar_vetor(VETOR **vetor);

#endif