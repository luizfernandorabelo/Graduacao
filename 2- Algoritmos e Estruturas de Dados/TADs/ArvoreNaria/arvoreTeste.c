#include "arvoreNaria.h"
#include "item.h"

#include <stdio.h>

void testarImpressao(AN *arvore){
    printf("\n-> Atualmente, esse é o estado da arvore: ");    
    arvore_imprimir(arvore);
    printf("TOTAL = %d itens.\n", arvore_tamanho(arvore));    
}

void testarInsercao(AN *arvore, ITEM *item, int chavePai){
    printf("\nInserindo item na arvore...\n");
    if(arvore_inserir(arvore, item, chavePai) == True)
        printf("Item de chave %.2d inserido na arvore!\n", item_obter_chave(item));
    else
        printf("Erro na inserção do item de chave %d\n", item_obter_chave(item));
    testarImpressao(arvore);
}

void testarBusca(AN *arvore, int chave){
    printf("\nBuscando item...\n");
    if(arvore_buscar(arvore, chave) != NULL)
        printf("O item de chave %d foi retornado pela função \"arvore_buscar()\"!\n", chave);
    else 
        printf("A função \"arvore_buscar()\" retornou NULO. O item de chave %d não foi encontrado!\n", chave);
}

int main(int argc, char *argv[]){

    printf("\nCriando arvore...\n");
    AN *arvore = arvore_criar(item_criar(10));
    printf("%s!\n", (arvore != NULL) ? "Arvore criada" : "Arvore NAO criada");

    testarImpressao(arvore);

    testarInsercao(arvore, item_criar(9), 10);
    testarInsercao(arvore, item_criar(13), 10);
    testarInsercao(arvore, item_criar(17), 9);
    testarInsercao(arvore, item_criar(4), 9);
    testarInsercao(arvore, item_criar(5), 13);
    testarInsercao(arvore, item_criar(12), 4);

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