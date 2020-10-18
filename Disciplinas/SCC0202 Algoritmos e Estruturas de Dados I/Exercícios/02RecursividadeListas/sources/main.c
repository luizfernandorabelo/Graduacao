#include <stdio.h>
#include "lista.h"
#include "item.h"

int main(int argc, char *argv[]){
    
    LISTA *lista1 = lista_criar();
    lista_inserir(lista1, item_criar(111));
    lista_inserir(lista1, item_criar(2));
    lista_inserir(lista1, item_criar(310));
    lista_inserir(lista1, item_criar(12));
    lista_inserir(lista1, item_criar(13));
    
    LISTA *lista2 = lista_criar();
    lista_inserir(lista2, item_criar(111));
    lista_inserir(lista2, item_criar(2));
    lista_inserir(lista2, item_criar(310));
    lista_inserir(lista2, item_criar(12));
    lista_inserir(lista2, item_criar(13));

    printf("As listas:\n");
    lista_imprimir(lista1);
    lista_imprimir(lista2);
    
    if(listas_iguais(lista1, lista2)) printf("São iguais\n");
    else printf("São diferentes\n");

    lista_inverter(lista2);
    printf("\nAs listas:\n");
    lista_imprimir(lista1);
    lista_imprimir(lista2);
    
    if(listas_iguais(lista1, lista2)) printf("São iguais\n");
    else printf("São diferentes\n");

    lista_apagar(&lista1);
    lista_apagar(&lista2);

    return 0;
}