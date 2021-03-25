#include "bufferSites.h"

#include <stdio.h>
#include <stdlib.h>


struct buffer_sites_{
    SITE **sites;
    int capacidade;
    int tamanho;
};


BUFFER *buffer_criar(void){

    BUFFER *novoBuffer = malloc(sizeof(BUFFER));

    if(novoBuffer != NULL){
        novoBuffer->sites = calloc(1, sizeof(SITE *));
        novoBuffer->capacidade = 1;
        novoBuffer->tamanho = 0;
    }

    return(novoBuffer);
}


boolean buffer_apagar(BUFFER **buffer){

    if(*buffer == NULL)
        return(FALSE);
    
    free((*buffer)->sites);
    free(*buffer);
    *buffer = NULL;

    return(TRUE);
}


int buffer_tamanho(BUFFER *buffer){
    return((buffer != NULL) ? buffer->tamanho : -1);
}


boolean buffer_cheio(BUFFER *buffer){
    return((buffer_tamanho(buffer) == buffer->capacidade));
}


boolean buffer_vazio(BUFFER *buffer){
    return(buffer_tamanho(buffer) == 0);
}


void buffer_trocar(BUFFER *buffer, int indice1, int indice2){

    SITE *temp = buffer->sites[indice1];
    buffer->sites[indice1] = buffer->sites[indice2];
    buffer->sites[indice2] = temp;
}


void buffer_fix_up(BUFFER *buffer, int noAtual){

    if(noAtual <= 0)
        return;

    int noPai = (noAtual - 1) / 2;

    if(site_obter_relevancia(buffer->sites[noPai]) < site_obter_relevancia(buffer->sites[noAtual])){
        buffer_trocar(buffer, noAtual, noPai);
        buffer_fix_up(buffer, noPai);
    }
}


boolean buffer_inserir_site(BUFFER *buffer, SITE *site){

    if(buffer == NULL || site == NULL)
        return(FALSE);
    
    if(buffer_cheio(buffer)){
        buffer->sites = realloc(buffer->sites, buffer->capacidade * 2 * sizeof(SITE *));
        buffer->capacidade *= 2;
        for(int i = buffer->tamanho; i < buffer->capacidade; i++)
            buffer->sites[i] = NULL;
    }

    buffer->sites[buffer->tamanho] = site;
    buffer->tamanho += 1;

    buffer_fix_up(buffer, buffer->tamanho - 1);

    return(TRUE);
}


boolean buffer_tem_filho(BUFFER *buffer, int pai){

    int filhoEsquerda = pai * 2 + 1;

    if(filhoEsquerda < buffer->tamanho && buffer->sites[filhoEsquerda] != NULL)
        return(TRUE);
    
    return(FALSE);
}


int buffer_obter_maior_filho(BUFFER *buffer, int pai){

    int filhoEsquerda = pai * 2 + 1;
    int filhoDireita = pai * 2 + 2;

    if(buffer->sites[filhoDireita] == NULL)
        return(filhoEsquerda);

    int chaveFilhoEsquerda = site_obter_relevancia(buffer->sites[filhoEsquerda]);
    int chaveFilhoDireita = site_obter_relevancia(buffer->sites[filhoDireita]);

    return((chaveFilhoEsquerda >= chaveFilhoDireita) ? filhoEsquerda : filhoDireita);
}


int buffer_obter_menor_filho(BUFFER *buffer, int pai){

    int filhoEsquerda = pai * 2 + 1;
    int filhoDireita = pai * 2 + 2;

    if(buffer->sites[filhoDireita] == NULL)
        return(filhoEsquerda);

    int chaveFilhoEsquerda = site_obter_relevancia(buffer->sites[filhoEsquerda]);
    int chaveFilhoDireita = site_obter_relevancia(buffer->sites[filhoDireita]);

    return((chaveFilhoEsquerda <= chaveFilhoDireita) ? filhoEsquerda : filhoDireita);
}


void buffer_fix_down(BUFFER *buffer, int noAtual){

    if(!buffer_tem_filho(buffer, noAtual))
        return;

    int maiorFilho = buffer_obter_maior_filho(buffer, noAtual);

    if(site_obter_relevancia(buffer->sites[maiorFilho]) > site_obter_relevancia(buffer->sites[noAtual])){
        buffer_trocar(buffer, noAtual, maiorFilho);
        buffer_fix_down(buffer, maiorFilho);
    }
}


boolean buffer_remover_inicio(BUFFER *buffer){

    if(buffer == NULL || buffer_vazio(buffer))
        return(FALSE);

    buffer->sites[0] = buffer->sites[buffer->tamanho - 1]; 
    buffer->sites[buffer->tamanho - 1] = NULL;
    buffer->tamanho -= 1;

    buffer_fix_down(buffer, 0);

    return(TRUE);
}


SITE *buffer_inicio(BUFFER *buffer){

    if(buffer != NULL && !buffer_vazio(buffer))
        return(buffer->sites[0]);

    return(NULL); 
}


SITE *buffer_obter_site(BUFFER *buffer, int codigo){

    if(buffer == NULL)
        return(NULL);

    for(int i = 0; i < buffer->tamanho; i++){
        if(site_obter_codigo(buffer->sites[i]) == codigo)
            return(buffer->sites[i]);
    }
    
    return(NULL);
}