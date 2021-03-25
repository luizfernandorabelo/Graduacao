#ifndef GOOGLE_BOT_IO_H
    #define GOOGLE_BOT_IO_H

	#ifndef BOOLEAN_TYPE
	    #define BOOLEAN_TYPE

		#define boolean int
		#define TRUE 1
		#define FALSE 0
	#endif

    #define CANCELAR_OPERACAO -1
    #define INSERIR_SITE 1
    #define REMOVER_SITE 2
    #define INSERIR_PALAVRA_CHAVE 3
    #define ATUALIZAR_RELEVANCIA 4
    #define LISTAR_SITES 5
    #define BUSCAR_SITES 6
    #define SUGERIR_SITES 7
    #define SAIR 8

    #include "servidor.h"

    #include <stdio.h>

    int ler_operacao(FILE *fp);
    int ler_codigo_site_novo(FILE *fp, SERVIDOR *servidor);
    int ler_codigo_site_existente(FILE *fp, SERVIDOR *servidor);
    int ler_relevancia_site(FILE *fp);
    char *ler_palavra_chave_site(FILE *fp);
    SITE *ler_conteudo_site(FILE *fp, SERVIDOR *servidor);

    void imprimir_menu(FILE *fp);
    void imprimir_mensagem_operacao_invalida(FILE *fp);
    void imprimir_operacao_cancelada(FILE *fp);
    void imprimir_termino_operacao(FILE *fp, boolean status);
    void imprimir_site_invalido(FILE *fp, int codigo);
    void imprimir_mensagem_final(FILE *fp);

#endif