#include "servidor.h"
#include "googleBotIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){

    SERVIDOR* servidor = servidor_criar();
    servidor_carregar_sites_iniciais(servidor);

    while(TRUE){        

        imprimir_menu(stdout);        
        
        int operacao = ler_operacao(stdin); 

        if(operacao == INSERIR_SITE){
            SITE *novoSite = ler_conteudo_site(stdin, servidor);
            if(novoSite == NULL) continue;
            boolean statusOperacao = servidor_inserir_site(servidor, novoSite);
            imprimir_termino_operacao(stdout, statusOperacao);
        }
        
        else if(operacao == REMOVER_SITE){
            int codigoSite = ler_codigo_site_existente(stdin, servidor);
            if(codigoSite == CANCELAR_OPERACAO) continue;
            boolean statusOperacao = servidor_remover_site(servidor, codigoSite);
            imprimir_termino_operacao(stdout, statusOperacao);
        }
        
        else if(operacao == INSERIR_PALAVRA_CHAVE){
            int codigoSite = ler_codigo_site_existente(stdin, servidor);
            if(codigoSite == CANCELAR_OPERACAO) continue;
            SITE *site = servidor_obter_site(servidor, codigoSite);
            char *novaPalavra = ler_palavra_chave_site(stdin);
            boolean statusOperacao = site_acrescentar_palavrachave(site, novaPalavra);
            imprimir_termino_operacao(stdout, statusOperacao);
        }
        
        else if(operacao == ATUALIZAR_RELEVANCIA){
            int codigoSite = ler_codigo_site_existente(stdin, servidor);
            if(codigoSite == CANCELAR_OPERACAO) continue;
            SITE *site = servidor_obter_site(servidor, codigoSite);
            int novaRelevancia = ler_relevancia_site(stdin);
            boolean statusOperacao = site_atualizar_relevancia(site, novaRelevancia);
            imprimir_termino_operacao(stdout, statusOperacao);
        }

        else if(operacao == LISTAR_SITES){
            boolean statusOperacao = servidor_listar_sites(servidor);
            imprimir_termino_operacao(stdout, statusOperacao);
        }
        
        else if(operacao == SAIR){
            imprimir_mensagem_final(stdout);
            break;
        }
        
        else{
            imprimir_mensagem_operacao_invalida(stdout);
        }
    }

    servidor_descarregar_sites_finais(servidor);    
    servidor_apagar_sites(servidor);
    servidor_apagar(&servidor);

    return(0);
}