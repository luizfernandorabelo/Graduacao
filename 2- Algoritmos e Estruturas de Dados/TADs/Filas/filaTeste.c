#include "fila.h"
#include "item.h"

#include <stdio.h>

void testarImpressao(FILA *fila){
    printf("\n-> Atualmente, esse é o estado da fila: ");    
    fila_imprimir(fila);
    printf("TOTAL = %d itens.\n", fila_tamanho(fila));    
}

void testarInsercao(FILA *fila, int chave){
    ITEM *buffer = item_criar(chave);
    printf("\nInserindo item na fila...\n");
    if(buffer != NULL && fila_entrar(fila, buffer) == True)
        printf("Item de chave %.2d inserido na fila!\n", item_obter_chave(buffer));
    else
        printf("Erro na inserção do item de chave %d\n", item_obter_chave(buffer));
    testarImpressao(fila);
}

void testarRemocao(FILA *fila){
    printf("\nRemovendo item da fila...\n");
    if(fila_sair(fila) == True)
        printf("O item do início da fila foi removido!\n");
    else 
        printf("O item do início da fila NAO foi removido!\n");    
    testarImpressao(fila);
}

int main(int argc, char *argv[]){

    printf("\nCriando fila...\n");
    FILA *fila = fila_criar();
    printf("%s!\n", (fila != NULL) ? "Fila criada" : "Fila NAO criada");

    testarInsercao(fila, 20);
    testarInsercao(fila, 9);
    testarInsercao(fila, 13);
    testarInsercao(fila, 17);
    testarInsercao(fila, 4);
    testarInsercao(fila, 6);

    testarRemocao(fila);
    testarRemocao(fila);
    testarRemocao(fila);
    testarRemocao(fila);

    testarInsercao(fila, 11);
    testarInsercao(fila, 22);

    printf("\nApagando fila...\n");
    printf("\n%s!\n", (fila_apagar(&fila) == True) ? "Fila apagada" : "Fila NAO apagada");
    
    return(0);
}