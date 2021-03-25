#include "lista.h"
#include "item.h"

#include <stdio.h>

void testarImpressao(LISTA *lista){
    printf("\n-> Atualmente, esse é o estado da lista: ");    
    lista_imprimir(lista);
    printf("TOTAL = %d itens.\n", lista_tamanho(lista));    
}

void testarInsercao(LISTA *lista, int chave){
    ITEM *buffer = item_criar(chave);
    printf("\nInserindo item na lista...\n");
    if(buffer != NULL && lista_inserir(lista, buffer) == True)
        printf("Item de chave %.2d inserido na lista!\n", item_obter_chave(buffer));
    else
        printf("Erro na inserção do item de chave %d\n", item_obter_chave(buffer));
    testarImpressao(lista);
}

void testarRemocao(LISTA *lista, int chave){
    printf("\nRemovendo item da lista...\n");
    if(lista_remover_item(lista, chave) == True)
        printf("O item de chave %d foi removido!\n", chave);
    else 
        printf("O elemento de chve %d NAO foi removido!\n", chave);    
    testarImpressao(lista);
}

void testarBusca(LISTA *lista, int chave){
    printf("\nBuscando item...\n");
    if(lista_buscar_item(lista, chave) != NULL)
        printf("O item de chave %d foi retornado pela função \"lista_buscar_item()\"!\n", chave);
    else 
        printf("A função \"lista_obter_item()\" retornou NULO. O item de chave %d não foi encontrado!\n", chave);
}

int main(int argc, char *argv[]){

    printf("\nCriando lista...\n");
    LISTA *lista = lista_criar();
    printf("%s!\n", (lista != NULL) ? "Lista criada" : "Lista NAO criada");

    testarInsercao(lista, 20);
    testarInsercao(lista, 9);
    testarInsercao(lista, 13);
    testarInsercao(lista, 17);
    testarInsercao(lista, 4);

    testarRemocao(lista, 1);
    testarRemocao(lista, 4);
    testarRemocao(lista, 13);
    testarRemocao(lista, 20);

    testarInsercao(lista, 11);

    testarBusca(lista, -1);
    testarBusca(lista, 1000);
    testarBusca(lista, 4);
    testarBusca(lista, 9);
    testarBusca(lista, 13);
    testarBusca(lista, 17);
    testarBusca(lista, 20);
    testarBusca(lista, 11);
    
    printf("\nApagando lista...\n");
    printf("\n%s!\n", (lista_apagar(&lista) == True) ? "Lista apagada" : "Lista NAO apagada");
    
    return(0);
}