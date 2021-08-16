// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#ifndef __UTIL_H__
    #define __UTIL_H__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    #include "registrosVeiculos.h"
    #include "registrosLinhas.h"

    char* verMes(int num);
    void imprimeMensagemErro(FILE *stream);
    int fimDoArquivoBIN(FILE *arquivoBIN);
    void binarioNaTela(char *nomeArquivoBinario); 
    int comparVeiculos(const void *a, const void *b);
    int comparLinhas(const void *a, const void *b);

#endif