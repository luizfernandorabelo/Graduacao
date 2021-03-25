#ifndef BUFFER_H
    #define BUFFER_H
    
    #ifndef BOOLEAN_TYPE 
        #define BOOLEAN_TYPE 

        #define boolean int 
        #define TRUE 1
        #define FALSE 0
    #endif

    #include "site.h"

    typedef struct buffer_sites_ BUFFER;

    BUFFER *buffer_criar(void);
    boolean buffer_apagar(BUFFER **buffer);
    boolean buffer_inserir_site(BUFFER *buffer, SITE *site);
    boolean buffer_remover_inicio(BUFFER *buffer);
    SITE *buffer_inicio(BUFFER *buffer);
    SITE *buffer_obter_site(BUFFER *buffer, int codigo);
    int buffer_tamanho(BUFFER *buffer);

#endif