#ifndef SITES_H 
	#define SITES_H

	#ifndef BOOLEAN_TYPE
		#define BOOLEAN_TYPE

		#define boolean int
		#define TRUE 1
		#define FALSE 0
	#endif

	typedef struct site_ SITE;

	SITE *site_criar(void);
	void site_apagar(SITE **site); 
	boolean site_inserir_dados(SITE *site, int codigo, char *nome, int relevancia, 
							   char *link, int qtPalavrasChave, char **palavrasChave);
	void site_imprimir(SITE *site);
	int site_obter_codigo(SITE *site);
	char *site_obter_nome(SITE *site);
	int site_obter_relevancia(SITE *site);
	char *site_obter_link(SITE *site);
	int site_obter_qt_palavras(SITE *site);
	char **site_obter_palavras_chave(SITE *site);
	void site_ativar(SITE *site);
	void site_desativar(SITE *site);
	boolean site_ativo(SITE *site);
	boolean site_acrescentar_palavrachave(SITE *site, char *palavraChave);
	boolean site_atualizar_relevancia(SITE *site, int relevancia);
	
#endif
