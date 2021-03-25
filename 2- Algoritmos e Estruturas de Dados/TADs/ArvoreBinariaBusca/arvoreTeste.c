#include "arvoreBinariaBusca.h"
#include "item.h"

#include <stdio.h>

void testarImpressao(ABB *arvore){
    printf("\n-> Atualmente, esse é o estado da arvore: ");    
    arvore_imprimir(arvore);
    printf("TOTAL = %d itens.\n", arvore_tamanho(arvore));    
}

void testarInsercao(ABB *arvore, ITEM *item){
    printf("\nInserindo item na arvore...\n");
    if(arvore_inserir(arvore, item) == True)
        printf("Item de chave %.2d inserido na arvore!\n", item_obter_chave(item));
    else
        printf("Erro na inserção do item de chave %d\n", item_obter_chave(item));
    testarImpressao(arvore);
}

void testarRemocao(ABB *arvore, int chave){
    printf("\nRemovendo item da arvore...\n");
    if(arvore_remover(arvore, chave) == True)
        printf("Item de chave %d foi removido!\n", chave);
    else 
        printf("Item de cahve %d NAO foi removido!\n", chave);    
    testarImpressao(arvore);
}

void testarBusca(ABB *arvore, int chave){
    printf("\nBuscando item...\n");
    if(arvore_buscar(arvore, chave) != NULL)
        printf("O item de chave %d foi retornado pela função \"arvore_buscar()\"!\n", chave);
    else 
        printf("A função \"arvore_buscar()\" retornou NULO. O item de chave %d não foi encontrado!\n", chave);
}

int main(int argc, char *argv[]){

    printf("\nCriando arvore...\n");
    ABB *arvore = arvore_criar();
    printf("%s!\n", (arvore != NULL) ? "Arvore criada" : "Arvore NAO criada");

    testarInsercao(arvore, item_criar(10));
    testarInsercao(arvore, item_criar(9));
    testarInsercao(arvore, item_criar(13));
    testarInsercao(arvore, item_criar(17));
    testarInsercao(arvore, item_criar(4));
    testarInsercao(arvore, item_criar(5));
    testarInsercao(arvore, item_criar(12));

    printf("\nPercursos:\n");
    arvore_percorrer_preordem(arvore);
    arvore_percorrer_emordem(arvore);
    arvore_percorrer_posordem(arvore);

    testarRemocao(arvore, 1);
    testarRemocao(arvore, 9);
    testarRemocao(arvore, 13);
    testarRemocao(arvore, 10);
    
    testarInsercao(arvore, item_criar(11));

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