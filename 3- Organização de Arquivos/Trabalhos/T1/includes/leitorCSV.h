#ifndef __LEITOR_CSV_H__
    #define __LEITOR_CSV_H__

    #ifndef boolean
        #define boolean
    
        #define bool int
        #define true 1
        #define false 0
    #endif

    #define DELIMITADOR_CAMPO ','
    #define STR_TOK_DELIM ","

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    bool fimDoArquivoCSV(FILE *stream);
    bool registroDoCSVEhRemovido(FILE *arquivoCSV);
    char **leDescricoesCabecalhoCSV(FILE *stream);
    char *leStringDoCSV(FILE *stream);
    int leIntDoCSV(FILE *stream);
    long long leLongLongDoCSV(FILE *stream);
    char leCharDoCSV(FILE *stream);

#endif