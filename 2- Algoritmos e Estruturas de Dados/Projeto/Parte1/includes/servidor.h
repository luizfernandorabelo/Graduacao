#ifndef SERVIDOR_H
    #define SERVIDOR_H

    #ifndef BOOLEAN_TYPE
        #define BOOLEAN_TYPE

        #define boolean int
        #define TRUE 1
        #define FALSE 0
    #endif

    #include "site.h"

    #define TAM_MAX 10000

    typedef struct servidor_ SERVIDOR;

    SERVIDOR *servidor_criar(void); 
    boolean servidor_apagar(SERVIDOR **servidor);
    boolean servidor_apagar_sites(SERVIDOR *servidor);
    boolean servidor_cheio(SERVIDOR *servidor);
    boolean servidor_vazio(SERVIDOR *servidor);    
    boolean servidor_inserir_site(SERVIDOR *servidor, SITE *site);
    boolean servidor_remover_site(SERVIDOR *servidor, int codigo);
    SITE *servidor_obter_site(SERVIDOR *servidor, int codigo);
    boolean servidor_listar_sites(SERVIDOR *servidor);
    boolean servidor_carregar_sites_iniciais(SERVIDOR *servidor); 
    boolean servidor_descarregar_sites_finais(SERVIDOR *servidor);
    
#endif