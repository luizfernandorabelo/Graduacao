#include "pilha.h"
#include "item.h"

#include <stdio.h>

void testarImpressao(PILHA *pilha){
    printf("\n-> Atualmente, esse é o estado da pilha:\n");    
    pilha_imprimir(pilha);
    printf("TOTAL = %d itens.\n", pilha_tamanho(pilha));    
}

void testarInsercao(PILHA *pilha, int chave){
    ITEM *buffer = item_criar(chave);
    if(buffer != NULL && pilha_empilhar(pilha, buffer) == True)
        printf("\nItem de chave %.2d inserido na pilha!\n", item_obter_chave(buffer));
    else
        printf("\nErro na inserção do item de chave %d\n", item_obter_chave(buffer));
    testarImpressao(pilha);
}

void testarRemocao(PILHA *pilha){
    if(pilha_desempilhar(pilha) == True) printf("\nO elemento do topo da pilha foi removido!\n");
    else printf("\nO elemento do topo da pilha NAO foi removido!\n");
    testarImpressao(pilha);
}

void testarRetornoTopo(PILHA *pilha){
    ITEM *item = pilha_topo(pilha);
    printf("Elemento de chave %d retornado pela função pilha_topo\n", item_obter_chave(item));
}

int main(int argc, char *argv[]){

    printf("\nCriando pilha...\n");
    PILHA *pilha = pilha_criar();
    printf("%s!\n", (pilha != NULL) ? "Pilha criada" : "Pilha NAO criada");

    testarInsercao(pilha, 20);
    testarInsercao(pilha, 9);
    testarInsercao(pilha, 13);
    testarInsercao(pilha, 17);
    testarInsercao(pilha, 4);

    testarRemocao(pilha);
    testarRemocao(pilha);
    testarRemocao(pilha);
    testarRemocao(pilha);

    testarRetornoTopo(pilha);

    testarInsercao(pilha, 11);

    printf("\nApagando pilha...\n");
    printf("%s!\n", (pilha_apagar(&pilha) == True) ? "Pilha apagada" : "Pilha NAO apagada");
    
    return(0);
}