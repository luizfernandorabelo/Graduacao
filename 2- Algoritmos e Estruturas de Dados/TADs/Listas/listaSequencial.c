#include "lista.h"

#include <stdio.h>
#include <stdlib.h>


#define TAM_MAX 1000
#define NOT_FOUND -1


struct lista_{
    ITEM *itens[TAM_MAX];
    int tamanho;
};


LISTA *lista_criar(void){ // Complexidade tempo: O(1)

    LISTA *novaLista = malloc(sizeof(LISTA));
    
    if(novaLista != NULL) novaLista->tamanho = 0;
    
    return(novaLista);
}


bool lista_inserir_ordenado(LISTA *lista, ITEM *item){ // Complexidade tempo: O(n)

    int chaveNovoItem = item_obter_chave(item);
    int tamanhoLista = lista_tamanho(lista);
    int indiceLivre = 0;
    
    while(indiceLivre < tamanhoLista && chaveNovoItem >= item_obter_chave(lista->itens[indiceLivre]))
        indiceLivre += 1;

    for(int i = lista_tamanho(lista); i > indiceLivre; i--)
        lista->itens[i] = lista->itens[i-1];

    lista->itens[indiceLivre] = item;
    lista->tamanho += 1;

    return(True);
}


bool lista_inserir_nao_ordenado(LISTA *lista, ITEM *item){ // Complexidade tempo: O(1)

    int indiceLivre = lista_tamanho(lista); 

    lista->itens[indiceLivre] = item;
    lista->tamanho += 1;

    return(True);
}


bool lista_inserir(LISTA *lista, ITEM *item){

    if(lista != NULL && item != NULL){
        #ifdef LISTA_ORDENADA
            return(lista_inserir_ordenado(lista, item));
        #endif
        #ifdef LISTA_NAO_ORDENADA
            return(lista_inserir_nao_ordenado(lista, item));
        #endif
        fprintf(stderr, "Falha na inserção de item na lista! Não foi definido no arquivo .h se a lista é ou não ordenada\n");
    }

    return(False);
}


int lista_buscar_posicao_ordenado(LISTA *lista, int chaveBuscada, int inicio, int fim){ // Complexidade tempo: O(log(n))

    if(inicio > fim)
        return (NOT_FOUND);

    int metade = (inicio + fim) / 2;
    
    if(chaveBuscada < item_obter_chave(lista->itens[metade])) 
        return(lista_buscar_posicao_ordenado(lista, chaveBuscada, inicio, metade - 1));

    if(chaveBuscada > item_obter_chave(lista->itens[metade])) 
        return(lista_buscar_posicao_ordenado(lista, chaveBuscada, metade + 1, fim));

    return(metade); // retorna quando a chave buscada é igual à lista->itens[metade]
}


int lista_buscar_posicao_nao_ordenado(LISTA *lista, int chaveBuscada){ // Complexidade tempo: O(n)

    for(int i = 0; i < lista->tamanho; i++)
        if(item_obter_chave(lista->itens[i]) == chaveBuscada) return(i);

    return(NOT_FOUND);
}


int lista_buscar_posicao_item(LISTA *lista, int chaveBuscada){

    #ifdef LISTA_ORDENADA
        return(lista_buscar_posicao_ordenado(lista, chaveBuscada, 0, lista_tamanho(lista)- 1));
    #endif
    #ifdef LISTA_NAO_ORDENADA
        return(lista_buscar_posicao_nao_ordenado(lista, chaveBuscada));
    #endif
    
    fprintf(stderr, "Falha na busca de item na lista! Não foi definido no arquivo .h se a lista é ou não ordenada\n");
    
    return(NOT_FOUND);
}


ITEM *lista_buscar_item(LISTA *lista, int chave){

    if(lista != NULL){
        int posItem = lista_buscar_posicao_item(lista, chave);
        if(posItem != NOT_FOUND)
            return(lista->itens[posItem]);
    }
    
    return(NULL);
}


bool lista_remover_item(LISTA *lista, int chave){  // Complexidade tempo: O(n)

    if(lista != NULL){
        int posItem = lista_buscar_posicao_item(lista, chave);
        if(posItem != NOT_FOUND){
            item_apagar(&lista->itens[posItem]);
            for(int i = posItem; i < lista->tamanho - 1; i++)
                lista->itens[i] = lista->itens[i+1];
            lista->tamanho -= 1;
            return(True);
        }
    }
    
    return(False);   
}


bool lista_apagar(LISTA **lista){ // Complexidade tempo: O(n)

    if(*lista != NULL){
        for(int i = 0; i < (*lista)->tamanho; i++)
            item_apagar(&(*lista)->itens[i]);
        free(*lista); *lista = NULL;
        return(True);
    }

    return(False);
}


void lista_imprimir(LISTA *lista){ 
    if(lista != NULL){
        for(int i = 0; i < lista->tamanho; i++)
            item_imprimir(lista->itens[i]);
    }
}

int lista_tamanho(LISTA *lista){
    return((lista != NULL) ? lista->tamanho : 0);
}

bool lista_vazia(LISTA *lista){
    return((lista_tamanho(lista) == 0) ? True : False);
}

bool lista_cheia(LISTA *lista){
    return((lista_tamanho(lista) == TAM_MAX) ? True : False);
}