#include "arvoreBinaria.h"
#include "item.h"

#include <stdio.h>

void testarImpressao(AB *arvore){
    printf("\n-> Atualmente, esse é o estado da arvore: ");    
    arvore_imprimir(arvore);
    printf("TOTAL = %d itens.\n", arvore_tamanho(arvore));    
}

void testarInsercao(AB *arvore, ITEM *item, int chavePai, char lado){
    printf("\nInserindo item na arvore...\n");
    if(arvore_inserir(arvore, item, chavePai, lado) == True)
        printf("Item de chave %.2d inserido na arvore!\n", item_obter_chave(item));
    else
        printf("Erro na inserção do item de chave %d\n", item_obter_chave(item));
    testarImpressao(arvore);
}

void testarRemocao(AB *arvore, int chavePai, char lado){
    printf("\nRemovendo item da arvore...\n");
    if(arvore_remover(arvore, chavePai, lado) == True)
        printf("Filho do item de chave %d foi removido!\n", chavePai);
    else 
        printf("Filho do item de cahve %d NAO foi removido!\n", chavePai);    
    testarImpressao(arvore);
}

void testarBusca(AB *arvore, int chave){
    printf("\nBuscando item...\n");
    if(arvore_buscar(arvore, chave) != NULL)
        printf("O item de chave %d foi retornado pela função \"arvore_buscar()\"!\n", chave);
    else 
        printf("A função \"arvore_buscar()\" retornou NULO. O item de chave %d não foi encontrado!\n", chave);
}

int main(int argc, char *argv[]){

    printf("\nCriando arvore...\n");
    AB *arvore = arvore_criar();
    printf("%s!\n", (arvore != NULL) ? "Arvore criada" : "Arvore NAO criada");

    testarInsercao(arvore, item_criar(20), RAIZ, RAIZ);
    testarInsercao(arvore, item_criar(9), 20, ESQUERDA);
    testarInsercao(arvore, item_criar(13), 20, DIREITA);
    testarInsercao(arvore, item_criar(17), 9, DIREITA);
    testarInsercao(arvore, item_criar(4), 13, ESQUERDA);

    testarRemocao(arvore, 1, DIREITA);
    testarRemocao(arvore, 9, DIREITA);
    testarRemocao(arvore, 13, ESQUERDA);

    testarInsercao(arvore, item_criar(11), 9, ESQUERDA);

    testarBusca(arvore, -1);
    testarBusca(arvore, 1000);
    testarBusca(arvore, 4);
    testarBusca(arvore, 9);
    testarBusca(arvore, 13);
    testarBusca(arvore, 17);
    testarBusca(arvore, 20);
    testarBusca(arvore, 11);

    printf("\nApagando arvore...\n");
    printf("\n%s!\n", (arvore_apagar(&arvore) == True) ? "Arvore apagada" : "Arvore NAO apagada");

    return(0);
}