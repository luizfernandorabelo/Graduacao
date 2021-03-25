#include "servidor.h"
#include "palavrasChave.h"
#include "bufferSites.h"

#include <stdio.h>
#include <stdlib.h>

#define POINTER_SIZE 8

typedef struct no_ NO;

struct no_{
    SITE *site;
    NO *filhoEsquerda;
    NO *filhoDireita;
    int altura;
};

struct servidor_{
    NO *raiz;
    PALAVRAS_CHAVE *palavasChave;
    int tamanho;
};


int max(int a, int b){
    return((a >= b) ? a : b);
}


int min(int a, int b){
    return((a <= b) ? a : b);
}


NO *servidor_criar_no(SITE *site){

    NO *novoNo = malloc(sizeof(NO));

    if(novoNo != NULL){
        novoNo->site = site;
        novoNo->filhoEsquerda = NULL;
        novoNo->filhoDireita = NULL;
        novoNo->altura = 0;
    }

    return(novoNo);
}


int servidor_obter_altura_no(NO *no){
    return((no != NULL) ? no->altura : -1);
}


SERVIDOR *servidor_criar(void){

    SERVIDOR *novoServidor = malloc(sizeof(SERVIDOR));

    if(novoServidor != NULL){
        novoServidor->raiz = NULL;
        novoServidor->palavasChave = palavras_chave_criar();
        novoServidor->tamanho = 0;
    }

    return(novoServidor);
}


void servidor_apagar_rec(NO *raiz){

    if(raiz == NULL)
        return;
    
    servidor_apagar_rec(raiz->filhoEsquerda);
    servidor_apagar_rec(raiz->filhoDireita);

    free(raiz);
}


boolean servidor_apagar(SERVIDOR **servidor){

    if(*servidor != NULL){
        servidor_apagar_rec((*servidor)->raiz);
        free(*servidor);
        *servidor = NULL;
        return(TRUE);
    }

    return(FALSE);
}


void servidor_apagar_sites_rec(NO *raiz){

    if(raiz == NULL)
        return;
    
    servidor_apagar_sites_rec(raiz->filhoEsquerda);
    servidor_apagar_sites_rec(raiz->filhoDireita);

    site_apagar(&raiz->site);
}


boolean servidor_apagar_sites(SERVIDOR *servidor){

    if(servidor != NULL){
        servidor_apagar_sites_rec(servidor->raiz);
        palavras_chave_apagar(&servidor->palavasChave);
        return(TRUE);
    }

    return(FALSE);
}


NO *servidor_obter_no(NO *raiz, int codigo){

    if(raiz == NULL)
        return(NULL);

    if((site_obter_codigo(raiz->site) == codigo))
        return(raiz);

    if(codigo < site_obter_codigo(raiz->site))
        return(servidor_obter_no(raiz->filhoEsquerda, codigo));

    return(servidor_obter_no(raiz->filhoDireita, codigo));
}


SITE *servidor_obter_site(SERVIDOR *servidor, int codigo){

    if(servidor != NULL){
        NO *noBuscado = servidor_obter_no(servidor->raiz, codigo);
        if(noBuscado != NULL)
            return(noBuscado->site);
    }

    return(NULL);
}


NO *servidor_rodar_esquerda(NO *raizDesbalanceada){

    NO *novaRaiz = raizDesbalanceada->filhoDireita;
    raizDesbalanceada->filhoDireita = novaRaiz->filhoEsquerda;
    novaRaiz->filhoEsquerda = raizDesbalanceada;

    raizDesbalanceada->altura = max(servidor_obter_altura_no(raizDesbalanceada->filhoEsquerda),
                                    servidor_obter_altura_no(raizDesbalanceada->filhoDireita)) + 1;
    novaRaiz->altura = max(raizDesbalanceada->altura, servidor_obter_altura_no(novaRaiz->filhoDireita)) + 1;

    return(novaRaiz);
}


NO *servidor_rodar_direita(NO *raizDesbalanceada){
    
    NO *novaRaiz = raizDesbalanceada->filhoEsquerda;
    raizDesbalanceada->filhoEsquerda = novaRaiz->filhoDireita;
    novaRaiz->filhoDireita = raizDesbalanceada;

    raizDesbalanceada->altura = max(servidor_obter_altura_no(raizDesbalanceada->filhoEsquerda),
                                    servidor_obter_altura_no(raizDesbalanceada->filhoDireita)) + 1;
    novaRaiz->altura = max(servidor_obter_altura_no(novaRaiz->filhoEsquerda), raizDesbalanceada->altura) + 1;

    return(novaRaiz);
}


NO *servidor_rodar_esquerda_direita(NO *raizDesbalanceada){

    raizDesbalanceada->filhoEsquerda = servidor_rodar_esquerda(raizDesbalanceada->filhoEsquerda);

    return(servidor_rodar_direita(raizDesbalanceada));
}


NO *servidor_rodar_direita_esquerda(NO *raizDesbalanceada){

    raizDesbalanceada->filhoDireita = servidor_rodar_direita(raizDesbalanceada->filhoDireita);

    return(servidor_rodar_esquerda(raizDesbalanceada));
}


NO *servidor_corrigir_balanceamento(NO *raiz){

    if(servidor_obter_altura_no(raiz->filhoEsquerda) - servidor_obter_altura_no(raiz->filhoDireita) == -2){
        if(servidor_obter_altura_no(raiz->filhoDireita->filhoEsquerda) >=
            servidor_obter_altura_no(raiz->filhoDireita->filhoDireita))
            raiz = servidor_rodar_direita_esquerda(raiz);
        else
            raiz = servidor_rodar_esquerda(raiz);
    }
    else if(servidor_obter_altura_no(raiz->filhoEsquerda) - servidor_obter_altura_no(raiz->filhoDireita) == 2){
        if(servidor_obter_altura_no(raiz->filhoEsquerda->filhoEsquerda) <
           servidor_obter_altura_no(raiz->filhoEsquerda->filhoDireita))
            raiz = servidor_rodar_esquerda_direita(raiz);
        else
            raiz = servidor_rodar_direita(raiz);
    }

    return(raiz);
}


boolean servidor_inserir_palavra_chave_site(SERVIDOR *servidor, char *palavra, int codigoSite){
    return(palavras_chave_inserir(servidor->palavasChave, palavra, codigoSite));
}


void servidor_inserir_palavras_chave_site(SERVIDOR *servidor, SITE *site){

    int codigo = site_obter_codigo(site);
    int qtPalavras = site_obter_qt_palavras(site);
    char **palavras = site_obter_palavras_chave(site);

    for(int i = 0; i < qtPalavras; i++)
        servidor_inserir_palavra_chave_site(servidor, palavras[i], codigo);
}


NO *servidor_inserir_site_rec(SERVIDOR *servidor, NO *raiz, SITE *site){

    if(raiz == NULL){
        servidor->tamanho += 1;
        return(servidor_criar_no(site));
    }

    if(site_obter_codigo(site) < site_obter_codigo(raiz->site))
        raiz->filhoEsquerda = servidor_inserir_site_rec(servidor, raiz->filhoEsquerda, site);
    else if(site_obter_codigo(site) > site_obter_codigo(raiz->site))
        raiz->filhoDireita = servidor_inserir_site_rec(servidor, raiz->filhoDireita, site);

    raiz->altura = max(servidor_obter_altura_no(raiz->filhoEsquerda), servidor_obter_altura_no(raiz->filhoDireita)) + 1;

    raiz = servidor_corrigir_balanceamento(raiz);

    return(raiz);
}


boolean servidor_inserir_site(SERVIDOR *servidor, SITE *site){

    if(servidor == NULL || site == NULL || servidor_cheio(servidor))
        return(FALSE);
    
    servidor_inserir_palavras_chave_site(servidor, site);

    int tamahoPre = servidor->tamanho;
    servidor->raiz = servidor_inserir_site_rec(servidor, servidor->raiz, site);
    int tamanhoPos = servidor->tamanho;

    return((tamanhoPos - tamahoPre) == 1);
}


void servidor_troca_max_esquerda(NO *raiz, NO *noAnterior, NO *noAtual){

    if(noAtual->filhoDireita == NULL){
        site_apagar(&raiz->site);
        raiz->site = noAtual->site;
        if(noAnterior == raiz)
            raiz->filhoEsquerda = noAtual->filhoEsquerda;
        else
            noAnterior->filhoDireita = noAtual->filhoEsquerda;
        free(noAtual);
        noAtual = NULL;
        return;
    }
    
    servidor_troca_max_esquerda(raiz, noAtual, noAtual->filhoDireita);
}


void servidor_remover_palavras_chave_site(SERVIDOR *servidor, int codigo){

    SITE *siteRemovido = servidor_obter_site(servidor, codigo);
    int qtPalavras = site_obter_qt_palavras(siteRemovido);
    printf("Qt palavras face = %d\n", qtPalavras);
    char **palavras = site_obter_palavras_chave(siteRemovido);

    for(int i = 0; i < qtPalavras; i++)
        printf("%d\n", palavras_chave_remover(servidor->palavasChave, palavras[i], codigo) == TRUE ? 1 : 0);
}


NO *servidor_remover_site_rec(SERVIDOR *servidor, NO *raiz, int codigo){

    if(raiz == NULL)
        return(NULL);
    
    int codigoAtual = site_obter_codigo(raiz->site);

    if(codigo > codigoAtual) 
        raiz->filhoDireita = servidor_remover_site_rec(servidor, raiz->filhoDireita, codigo);
    else if(codigo < codigoAtual) 
        raiz->filhoEsquerda = servidor_remover_site_rec(servidor, raiz->filhoEsquerda, codigo);
    else{ 
        servidor_remover_palavras_chave_site(servidor, codigoAtual);
        if(raiz->filhoEsquerda == NULL || raiz->filhoDireita == NULL){
            NO *noRemovido = raiz;
            if(raiz->filhoEsquerda == NULL)
                raiz = raiz->filhoDireita;
            else
                raiz = raiz->filhoEsquerda;
            site_apagar(&noRemovido->site);
            free(noRemovido);
            noRemovido = NULL;
        }
        else{
            servidor_troca_max_esquerda(raiz, raiz, raiz->filhoEsquerda);
            if(raiz->filhoEsquerda != NULL)
                raiz->filhoEsquerda = servidor_corrigir_balanceamento(raiz->filhoEsquerda);
        }
        servidor->tamanho -= 1;
    }

    if(raiz != NULL){
        raiz->altura = max(servidor_obter_altura_no(raiz->filhoEsquerda), servidor_obter_altura_no(raiz->filhoDireita)) + 1;
        raiz = servidor_corrigir_balanceamento(raiz);
    }

    return(raiz);
}


boolean servidor_remover_site(SERVIDOR *servidor, int codigo){

    if(servidor != NULL){
        int tamanhoPre = servidor->tamanho;
        servidor->raiz = servidor_remover_site_rec(servidor, servidor->raiz, codigo);
        int tamanhoPos = servidor->tamanho;
        return((tamanhoPre - tamanhoPos) == 1);
    }

    return(FALSE);
}


void servidor_listar_sites_rec(NO *raiz){

    if(raiz == NULL)
        return;

    servidor_listar_sites_rec(raiz->filhoEsquerda);
    site_imprimir(raiz->site);
    printf("\n");
    servidor_listar_sites_rec(raiz->filhoDireita);
}


boolean servidor_listar_sites(SERVIDOR *servidor){

    if(servidor == NULL)
        return(FALSE);

    servidor_listar_sites_rec(servidor->raiz);
    printf("\n");

    return(TRUE);
}


SITE **servidor_ordenar_sites_buscados(BUFFER *bufferSites){

    int tamBuffer = buffer_tamanho(bufferSites); 

    SITE **sitesBuscados = malloc(tamBuffer * sizeof(SITE *));

    for(int i = 0; i < tamBuffer; i++){
        SITE *siteAtual = buffer_inicio(bufferSites);
        buffer_remover_inicio(bufferSites);
        sitesBuscados[i] = siteAtual;
    }

    return(sitesBuscados);
}


boolean servidor_buscar_sites(SERVIDOR *servidor, char *palavraChave){

    CODIGOS *codigosRelacionados = palavras_chave_buscar_codigos_relacionados(servidor->palavasChave, palavraChave);

    if(codigosRelacionados != NULL){
        int totalRelacionados = codigosRelacionados->quantidade;
        BUFFER *bufferSites = buffer_criar(); 
        for(int i = 0; i < totalRelacionados; i++){
            SITE *siteRelacionado = servidor_obter_site(servidor, codigosRelacionados->codigos[i]);
            buffer_inserir_site(bufferSites, siteRelacionado);
        }
        printf("\nForam obtidos %d sites cadastrados com a palavra: %s. Sao eles:\n\n", totalRelacionados, palavraChave);
        SITE **sitesRelacionados = servidor_ordenar_sites_buscados(bufferSites);
        buffer_apagar(&bufferSites);
        for(int i = 0; i < totalRelacionados; i++){
            site_imprimir(sitesRelacionados[i]);
            printf("\n");
        }
        free(sitesRelacionados);
        return(TRUE);
    }
    
    return(FALSE);
}


SITE **servidor_ordenar_sites_sugeridos(BUFFER *bufferSites, int quantidadeSites){

    SITE **sitesBuscados = malloc(quantidadeSites * sizeof(SITE *));

    for(int i = 0; i < quantidadeSites; i++){
        SITE *siteAtual = buffer_inicio(bufferSites);
        buffer_remover_inicio(bufferSites);
        sitesBuscados[i] = siteAtual;
    }

    return(sitesBuscados);
}


boolean servidor_sugerir_sites(SERVIDOR *servidor, char *palavraChave){

    CODIGOS *codigosRelacionados = palavras_chave_buscar_codigos_relacionados(servidor->palavasChave, palavraChave);

    if(codigosRelacionados != NULL){
        int totalRelacionados = codigosRelacionados->quantidade;
        BUFFER *bufferSites = buffer_criar(); 
        for(int i = 0; i < totalRelacionados; i++){
            SITE *siteRelacionado = servidor_obter_site(servidor, codigosRelacionados->codigos[i]);
            if(buffer_obter_site(bufferSites, codigosRelacionados->codigos[i]) == NULL)
                buffer_inserir_site(bufferSites, siteRelacionado);
            int qtPalavrasSiteRelacionado = site_obter_qt_palavras(siteRelacionado);
            for(int i = 0; i < qtPalavrasSiteRelacionado; i++){
                char **palavrasSiteRelacionado = site_obter_palavras_chave(siteRelacionado);
                CODIGOS *codigosAssociados = palavras_chave_buscar_codigos_relacionados(servidor->palavasChave,
                                                                                        palavrasSiteRelacionado[i]);
                int totalAssociados = codigosAssociados->quantidade;
                for(int i = 0; i < totalAssociados; i++){
                    SITE *siteAssociado = servidor_obter_site(servidor, codigosAssociados->codigos[i]);
                    if(buffer_obter_site(bufferSites, codigosAssociados->codigos[i]) == NULL)
                        buffer_inserir_site(bufferSites, siteAssociado);
                }
            } 
        }
        printf("\nSites sugeridos para a palavra: %s:\n\n", palavraChave);
        int quantidadeSites = min(buffer_tamanho(bufferSites), 5);
        SITE **sitesRelacionados = servidor_ordenar_sites_sugeridos(bufferSites, quantidadeSites);
        buffer_apagar(&bufferSites);
        for(int i = 0; i < quantidadeSites; i++){
            site_imprimir(sitesRelacionados[i]);
            printf("\n");
        }
        free(sitesRelacionados);
        return(TRUE);
    }

    return(FALSE);
}


boolean servidor_cheio(SERVIDOR *servidor){

    NO *noTeste = servidor_criar_no(NULL);

    if(noTeste == NULL)
        return(TRUE);
    
    free(noTeste);

    return(FALSE);
}


int servidor_tamanho(SERVIDOR *servidor){
    return((servidor != NULL) ? servidor->tamanho : -1);
}


boolean servidor_vazio(SERVIDOR *servidor){
    return(servidor_tamanho(servidor) == 0);
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


void servidor_descarregar_sites_finais_rec(NO *raiz, FILE *fp){

    if(raiz == NULL)
        return;
    
    servidor_descarregar_sites_finais_rec(raiz->filhoEsquerda, fp);

    SITE *siteAtual = raiz->site;

    line_ *line = malloc(sizeof(line_));
    line->code = site_obter_codigo(siteAtual);
    line->name = site_obter_nome(siteAtual);
    line->relevance = site_obter_relevancia(siteAtual);
    line->link = site_obter_link(siteAtual);
    line->keyWords = malloc(sizeof(key_words));
    line->keyWords->size = site_obter_qt_palavras(siteAtual);
    line->keyWords->words = site_obter_palavras_chave(siteAtual);

    writeLineToCsvFile(line, fp);

    free(line->keyWords);
    free(line);
    
    servidor_descarregar_sites_finais_rec(raiz->filhoDireita, fp);
}


boolean servidor_descarregar_sites_finais(SERVIDOR *servidor){

    FILE *fp = fopen(CSV_FILE_NAME, "w");
    
    if(servidor == NULL || fp == NULL)
        return(FALSE);

    servidor_descarregar_sites_finais_rec(servidor->raiz, fp);

    fclose(fp);

    return(TRUE);
}