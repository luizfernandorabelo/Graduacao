#include "heap.h"
#include "item.h"

#include <stdio.h>

void testarImpressao(HEAP *heap){
    printf("\n-> Atualmente, esse é o estado da heap: ");    
    heap_imprimir(heap);
    printf("TOTAL = %d itens.\n", heap_tamanho(heap));    
}

void testarInsercao(HEAP *heap, ITEM *item){
    printf("\nInserindo item na heap...\n");
    if(heap_inserir(heap, item) == True)
        printf("Item de chave %.2d inserido na heap!\n", item_obter_chave(item));
    else
        printf("Erro na inserção do item de chave %d\n", item_obter_chave(item));
    testarImpressao(heap);
}

void testarRemocao(HEAP *heap){
    printf("\nRemovendo item da heap...\n");
    if(heap_remover_inicio(heap) == True)
        printf("O item do inicio da Heap foi removido!\n");
    else 
        printf("O item do inicio da Heap NAO foi removido!\n");    
    testarImpressao(heap);
}

int main(int argc, char *argv[]){

    printf("\nCriando heap...\n");
    HEAP *heap = heap_criar();
    printf("%s!\n", (heap != NULL) ? "Heap criada" : "Heap NAO criada");

    testarInsercao(heap, item_criar(10));
    testarInsercao(heap, item_criar(9));
    testarInsercao(heap, item_criar(13));
    testarInsercao(heap, item_criar(17));
    testarInsercao(heap, item_criar(4));
    testarInsercao(heap, item_criar(5));
    testarInsercao(heap, item_criar(12));

    testarRemocao(heap);
    testarRemocao(heap);
    testarRemocao(heap);
    testarRemocao(heap);

    testarInsercao(heap, item_criar(11));

    printf("\nApagando heap...\n");
    printf("\n%s!\n", (heap_apagar(&heap) == True) ? "Heap apagada" : "Heap NAO apagada");

    return(0);
}