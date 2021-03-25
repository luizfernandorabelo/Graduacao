#include "servidor.h"
#include "site.h"
#include "csvManager.h"

#include <stdlib.h>


struct servidor_{
    SITE *sites[TAM_MAX];
    int qtSitesAtivos;
};


SERVIDOR *servidor_criar(void){

    SERVIDOR *servidor = malloc(sizeof(SERVIDOR));
    
    if(servidor != NULL){
        for(int i = 0; i < TAM_MAX; i++)
            servidor->sites[i] = site_criar();
    }

    return(servidor);
}


boolean servidor_apagar(SERVIDOR **servidor){

    if(*servidor == NULL)
        return(FALSE);

    free(*servidor);
    *servidor = NULL;

    return(TRUE);
}


boolean servidor_apagar_sites(SERVIDOR *servidor){

    if(servidor == NULL)
        return(FALSE);

    for(int i = 0; i < TAM_MAX; i++)
        site_apagar(&servidor->sites[i]);

    servidor->qtSitesAtivos = 0;

    return(TRUE);
}


boolean servidor_cheio(SERVIDOR *servidor){
    return(servidor != NULL ? servidor->qtSitesAtivos == TAM_MAX : FALSE);
}


boolean servidor_vazio(SERVIDOR *servidor){
    return (servidor != NULL ? servidor->qtSitesAtivos == 0 : FALSE);
}


boolean servidor_inserir_site(SERVIDOR *servidor, SITE *site){

    if(servidor == NULL || site == NULL)
        return(FALSE);

    int pos = site_obter_codigo(site);
    site_apagar(&servidor->sites[pos]);
    servidor->sites[pos] = site;
    site_ativar(site);
    servidor->qtSitesAtivos += 1;

    return(TRUE);
}


boolean servidor_remover_site(SERVIDOR *servidor, int codigo){

    if(servidor != NULL && codigo > -1 && codigo < TAM_MAX && site_ativo(servidor->sites[codigo])){
        site_apagar(&servidor->sites[codigo]);
        servidor->sites[codigo] = site_criar();
        servidor->qtSitesAtivos -= 1;
        return(TRUE);
    }   

    return(FALSE);
}


SITE *servidor_obter_site(SERVIDOR *servidor, int codigo){

    if(servidor == NULL || codigo < 0 || codigo > TAM_MAX || !site_ativo(servidor->sites[codigo]))
        return(NULL);

    return(servidor->sites[codigo]);
}


boolean servidor_listar_sites(SERVIDOR *servidor){

    if(servidor != NULL){
        for(int i = 0; i < TAM_MAX; i++){
            SITE *siteAtual = servidor_obter_site(servidor, i);
            if(site_ativo(siteAtual)){
                site_imprimir(servidor_obter_site(servidor, i));
                printf("\n");
            }
        }
        return(TRUE);
    }

    return(FALSE);
}


boolean servidor_carregar_sites_iniciais(SERVIDOR *servidor){

    FILE *fp = fopen(CSV_FILE_NAME, "r");
    
    if(servidor == NULL || fp == NULL)
        return(FALSE);
    
    while(!feof(fp)){
        line_ *line = readLineFromCsvFile(fp);
        if(line != NULL){ 
            int codigo = line->code;
            char *nome = line->name;
            int relevancia = line->relevance;
            char *link = line->link;
            int qtPalavrasChave = line->keyWords->size;
            char **palavrasChve = line->keyWords->words;
            SITE *site = site_criar();
            site_inserir_dados(site, codigo, nome, relevancia, link, qtPalavrasChave, palavrasChve);
            servidor_inserir_site(servidor, site);
            free(line->keyWords);
            free(line);
        }
    }

    fclose(fp);

    return(TRUE);
}


boolean servidor_descarregar_sites_finais(SERVIDOR *servidor){

    FILE *fp = fopen(CSV_FILE_NAME, "w");
    
    if(servidor == NULL || fp == NULL)
        return(FALSE);

    for(int i = 0; i < TAM_MAX; i++){
        SITE *site = servidor_obter_site(servidor, i);
        if(site != NULL && site_ativo(site)){
            line_ *line = malloc(sizeof(line_));
            line->code = site_obter_codigo(site);
            line->name = site_obter_nome(site);
            line->relevance = site_obter_relevancia(site);
            line->link = site_obter_link(site);
            line->keyWords = malloc(sizeof(key_words));
            line->keyWords->size = site_obter_qt_palavras(site);
            line->keyWords->words = site_obter_palavras_chave(site);
            writeLineToCsvFile(line, fp);
            free(line->keyWords);
            free(line);
        }
    }

    fclose(fp);

    return(TRUE);
}