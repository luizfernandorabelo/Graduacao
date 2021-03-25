#include "googleBotIO.h"

#include <stdlib.h>
#include <string.h>


int ler_inteiro(FILE *fp){

    int inteiro = 0;

    fscanf(fp, "%d", &inteiro);

    return(inteiro);
}


char *ler_string(FILE *fp){

    char *string = calloc(101, sizeof(char));

    if(string != NULL){
        fscanf(fp, " %[^\n]s", string);
        string = (char *) realloc(string, strlen(string) + 1);
    }

    return(string);
}


int ler_operacao(FILE *fp){

    printf("\nDigite o código da operacao: ");

    int operacao = ler_inteiro(fp);

    while(operacao < 0 || operacao > SAIR){
        printf("Opcao invalida!\n");
        printf("Digite a operacao: ");
        operacao = ler_inteiro(fp);
    }

    printf("\n");
    
    return(operacao);
}


int ler_codigo_site_novo(FILE *fp, SERVIDOR *servidor){

    printf("Digite o codigo do site (ou -1 para cancelar a operacao): ");

    int codigo = ler_inteiro(fp);

    while(codigo < 0 || codigo >= TAM_MAX || servidor_obter_site(servidor, codigo) != NULL){
        if(codigo == CANCELAR_OPERACAO){
            imprimir_operacao_cancelada(stdout);
            return(CANCELAR_OPERACAO);
        }
        printf("Codigo invalido! O codigo deve estar no intervalo [0-9999] e codigos de sites ja inseridos nao sao aceitos.\n\n");
        printf("Digite um valor valido caso queira prosseguir ou -1 para cancelar a operacao: ");
        codigo = ler_inteiro(fp);
    }

    return(codigo);
}


int ler_codigo_site_existente(FILE *fp, SERVIDOR *servidor){

    printf("Digite o codigo do site (ou -1 para cancelar a operacao): ");    

    int codigo = ler_inteiro(fp);

    while(codigo < 0 || codigo >= TAM_MAX || servidor_obter_site(servidor, codigo) == NULL){
        if(codigo == CANCELAR_OPERACAO){
            imprimir_operacao_cancelada(stdout);
            return(CANCELAR_OPERACAO);
        }
        printf("Codigo invalido! O codigo deve estar no intervalo [0-9999] e um site deve possui-lo.\n\n");
        printf("Digite um valor valido caso queira prosseguir ou -1 para cancelar a operacao: ");
        codigo = ler_inteiro(fp);
    }

    return(codigo);
}


int ler_relevancia_site(FILE *fp){

    printf("Digite um valor para a relevancia: ");

    int relevancia = ler_inteiro(fp); 
    
    while(relevancia < 0 || relevancia > 1000){
        printf("Valor invalido! O valor da relevancia deve estar no intervalo [0-1000]\n");
        printf("Digite um valor valido: ");
        relevancia = ler_inteiro(fp);
    }

    return(relevancia);
}


int ler_qt_palavras_chave_site(FILE *fp){

    printf("O site tera quantas palavras chave? ");

    int qtpalavras = ler_inteiro(fp);

    while(qtpalavras < 0 || qtpalavras > 10){
        printf("Valor invalido! Um site deve ter no minimo 0 e no maximo 10 palavras chave\n");
        printf("Digite um valor valido: ");
        qtpalavras = ler_inteiro(fp);
    }

    return(qtpalavras);
}


char *ler_nome_site(FILE *fp){

    printf("Digite o nome do site: ");

    char *nome = ler_string(fp);

    if(nome == NULL)
        printf("Erro de alocacao de memoria na leitura do nome do site!\n");

    return(nome);
}


char *ler_link_site(FILE *fp){

    printf("Digite o link do site: ");

    char *link = ler_string(fp);
    
    if(link == NULL)
        printf("Erro de alocacao de memoria na leitura do link do site!\n");

    return(link);
}


char *ler_palavra_chave_site(FILE *fp){

    printf("Digite palavra chave: ");

    char *pchave = ler_string(fp);

    if(pchave == NULL)
        printf("Erro de alocacao de memoria na leitura da palavra chave!\n");

    return(pchave);
}


char **ler_palavras_chave_site(FILE *fp, int qtPalavras){

    char **palavrasChave = malloc(qtPalavras * sizeof(char *));
    
    if(palavrasChave != NULL){
        for(int i = 0; i < qtPalavras; i++)
            palavrasChave[i] = ler_palavra_chave_site(fp);    
    }
    else
        printf("Erro de alocacao de memoria na leitura do conjunto de palavras chave!\n");

    printf("\n");

    return(palavrasChave);
}


SITE *ler_conteudo_site(FILE *fp, SERVIDOR *servidor){

    int codigo = ler_codigo_site_novo(fp, servidor);

    if(codigo == CANCELAR_OPERACAO)
        return(NULL);

    int relevancia = ler_relevancia_site(fp);
    char *nome = ler_nome_site(fp);
    char *link = ler_link_site(fp);
    int qtpalavras = ler_qt_palavras_chave_site(fp);
    char **palavraschave = ler_palavras_chave_site(fp, qtpalavras);

    SITE *site = site_criar();
    
    boolean dadosInseridos = site_inserir_dados(site, codigo, nome, relevancia, link, qtpalavras, palavraschave);
    
    if(dadosInseridos == FALSE){
        fprintf(stdout, "Erro ao inserir dados no site! Cheque suas entradas e tente novamente\n");
        return(NULL);
    }
    
    return(site);
}


void imprimir_menu(FILE *fp){
    printf("\n           MENU DE OPERACOES\n");
    printf("----------------------------------------\n");
    printf("[%d] Inserir um site\n", INSERIR_SITE);
    printf("[%d] Remover um site\n", REMOVER_SITE);
    printf("[%d] Inserir uma palavra chave em um site\n", INSERIR_PALAVRA_CHAVE);
    printf("[%d] Atualizar a relevancia de um site\n", ATUALIZAR_RELEVANCIA);
    printf("[%d] Listar todos os sites\n", LISTAR_SITES);
    printf("[%d] Buscar site por palavra chave\n", BUSCAR_SITES);
    printf("[%d] Sugerir site por palavra chave\n", SUGERIR_SITES);
    printf("[%d] Sair\n", SAIR);
}


void imprimir_mensagem_operacao_invalida(FILE *fp){
    fprintf(fp, "\nOperação inválida!\n");
}


void imprimir_operacao_cancelada(FILE *fp){
    fprintf(fp, "\nA operacao foi cancelada. Voltando para o menu de operacoes...\n");
}


void imprimir_termino_operacao(FILE *fp, boolean status){
    fprintf(fp, "%s\n", (status ? "Operacao realizada com sucesso!" : "Operacao NAO concluida!"));
}


void imprimir_site_invalido(FILE *fp, int codigo){
    fprintf(fp, "O site de codigo %d eh invalido ou inexistente\n", codigo);
}


void imprimir_mensagem_final(FILE *fp){
    fprintf(fp, "Fim da execucao! Suas alteracoes foram salvas da base de dados (arquivo csv).\n");
}