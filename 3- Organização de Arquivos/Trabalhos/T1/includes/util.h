#ifndef __UTIL_H__
    #define __UTIL_H__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    char* verMes(int num);
    void imprimeMensagemErro(FILE *stream);
    int fimDoArquivoBIN(FILE *arquivoBIN);
    void binarioNaTela(char *nomeArquivoBinario); 
    void scan_quote_string(char *str);

#endif