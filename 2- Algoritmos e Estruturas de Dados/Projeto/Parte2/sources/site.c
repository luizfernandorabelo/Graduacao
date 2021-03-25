#include <stdlib.h>
#include <stdio.h>
#include "site.h"


struct site_{
	int codigo;
	char *nome;
	int relevancia;
	char *link;
	int qtPalavrasChave;
	char **palavrasChave;
};


SITE *site_criar(void){

	SITE *site = malloc(sizeof(SITE));

	if(site != NULL){
		site->codigo = -1;
		site->nome = NULL;
		site->relevancia = -1; 
		site->link = NULL;
		site->qtPalavrasChave = 0;
		site->palavrasChave = NULL;
	}

	return(site);
}


void site_apagar(SITE **site){

	if(*site != NULL){
		if((*site)->nome != NULL)
			free((*site)->nome);
		if((*site)->link != NULL)
			free((*site)->link);
		if((*site)->palavrasChave != NULL){
			for(int i = 0; i < (*site)->qtPalavrasChave; i++){
				if((*site)->palavrasChave[i] != NULL)
					free((*site)->palavrasChave[i]);
			}
			free((*site)->palavrasChave);
		}
		free(*site);
	}
	*site = NULL;
}


boolean site_inserir_dados(SITE *site, int codigo, char *nome, int relevancia, 
							   char *link, int qtPalavrasChave, char **palavrasChave){
	if(site != NULL){
		site->codigo = codigo;
		site->nome = nome;
		site->relevancia = relevancia;
		site->link = link;
		site->qtPalavrasChave = qtPalavrasChave;
		site->palavrasChave = palavrasChave;
		return(TRUE);
	}

	return(FALSE);
}


void site_imprimir_palavras_chave(SITE *site){	

	if(site->palavrasChave == NULL)
		return;

	printf("PALAVRAS CHAVE:\n");
	
	for(int i = 0; i < site->qtPalavrasChave; i++)
		printf("- %s\n", site->palavrasChave[i]);	
}


void site_imprimir(SITE *site){

	if(site == NULL)
		return;

	printf("NOME: %s; LINK: %s\n", site->nome, site->link);
	printf("CODIGO: %.4d; RELEVANCIA: %.4d\n", site->codigo, site->relevancia);
	site_imprimir_palavras_chave(site);
}


int site_obter_codigo(SITE *site){

	if(site != NULL)
		return(site->codigo);
	
	return(-1);
}


char *site_obter_nome(SITE *site){

	if(site != NULL)
		return site->nome;
	
	return(NULL);
}


int site_obter_relevancia(SITE *site){

	if(site != NULL)
		return(site->relevancia);
	
	return(-1);
}


char *site_obter_link(SITE *site){

	if(site != NULL)
		return(site->link);
	
	return(NULL);
}


int site_obter_qt_palavras(SITE *site){

	if(site != NULL)
		return(site->qtPalavrasChave);
	
	return (-1);
}


char **site_obter_palavras_chave(SITE *site){

	if(site != NULL)
		return(site->palavrasChave);
	
	return(NULL);
}


boolean site_acrescentar_palavrachave(SITE *site, char *palavraChave){

	if(site == NULL || palavraChave == NULL || site->qtPalavrasChave >= 10)
		return(FALSE);	

	site->palavrasChave = realloc(site->palavrasChave, (site->qtPalavrasChave + 1) * sizeof(char *));
	site->palavrasChave[site->qtPalavrasChave] = palavraChave;
	site->qtPalavrasChave += 1;
	
	return(TRUE);
}


boolean site_atualizar_relevancia(SITE *site, int relevancia){

	if(site != NULL){
		site -> relevancia = relevancia;
		return (TRUE);
	}

	return FALSE;
}