#include "deque.h"
#include "item.h"

#include <stdio.h>

void testarImpressao(DEQUE *deque){
    printf("\n-> Atualmente, esse é o estado da deque: ");    
    deque_imprimir(deque);
    printf("TOTAL = %d itens.\n", deque_tamanho(deque));    
}

void testarInsercaoInicio(DEQUE *deque, int chave){
    ITEM *buffer = item_criar(chave);
    printf("\nInserindo item no início da deque...\n");
    if(buffer != NULL && deque_inserir_inicio(deque, buffer) == True)
        printf("Item de chave %.2d inserido na deque!\n", item_obter_chave(buffer));
    else
        printf("Erro na inserção do item de chave %d\n", item_obter_chave(buffer));
    testarImpressao(deque);
}

void testarInsercaoFim(DEQUE *deque, int chave){
    ITEM *buffer = item_criar(chave);
    printf("\nInserindo item no fim da deque...\n");
    if(buffer != NULL && deque_inserir_fim(deque, buffer) == True)
        printf("Item de chave %.2d inserido na deque!\n", item_obter_chave(buffer));
    else
        printf("Erro na inserção do item de chave %d\n", item_obter_chave(buffer));
    testarImpressao(deque);
}

void testarRemocaoInicio(DEQUE *deque){
    printf("\nRemovendo item do início da deque...\n");
    if(deque_remover_inicio(deque) == True)
        printf("O item do início da deque foi removido!\n");
    else 
        printf("O item do início da deque NAO foi removido!\n");    
    testarImpressao(deque);
}

void testarRemocaoFim(DEQUE *deque){
    printf("\nRemovendo item da deque...\n");
    if(deque_remover_fim(deque) == True)
        printf("O item do fim da deque foi removido!\n");
    else 
        printf("O item do fim da deque NAO foi removido!\n");    
    testarImpressao(deque);
}

int main(int argc, char *argv[]){

    printf("\nCriando deque...\n");
    DEQUE *deque = deque_criar();
    printf("%s!\n", (deque != NULL) ? "Deque criada" : "Deque NAO criada");

    testarInsercaoFim(deque, 20);
    testarInsercaoInicio(deque, 9);
    testarInsercaoFim(deque, 13);
    testarInsercaoInicio(deque, 17);
    testarInsercaoFim(deque, 4);
    testarInsercaoInicio(deque, 6);

    testarRemocaoInicio(deque);
    testarRemocaoFim(deque);
    testarRemocaoInicio(deque);
    testarRemocaoFim(deque);

    testarInsercaoFim(deque, 11);
    testarInsercaoInicio(deque, 22);

    printf("\nApagando deque...\n");
    printf("\n%s!\n", (deque_apagar(&deque) == True) ? "Deque apagada" : "Deque NAO apagada");
    
    return(0);
}