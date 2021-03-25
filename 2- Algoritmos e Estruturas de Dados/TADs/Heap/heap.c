#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 1024


struct heap_{
    ITEM *itens[TAM_MAX];
    int tamanho;
};


HEAP *heap_criar(void){

    HEAP *novaHeap = malloc(sizeof(HEAP));

    if(novaHeap != NULL){
        for(int i = 0; i < TAM_MAX; i++)
            novaHeap->itens[i] = NULL;
        novaHeap->tamanho = 0;
    }

    return(novaHeap);
}


bool heap_apagar(HEAP **heap){

    if(*heap == NULL)
        return(False);
    
    int tamHeap = (*heap)->tamanho;

    for(int i = 0; i < tamHeap; i++)
        item_apagar(&(*heap)->itens[i]);    
    
    free(*heap);
    *heap = NULL;

    return(True);
}


void heap_trocar(HEAP *heap, int indice1, int indice2){

    ITEM *temp = heap->itens[indice1];
    heap->itens[indice1] = heap->itens[indice2];
    heap->itens[indice2] = temp;
}


void heap_max_fix_up(HEAP *heap, int noAtual){

    if(noAtual <= 0)
        return;

    int noPai = (noAtual - 1) / 2;

    if(item_obter_chave(heap->itens[noPai]) < item_obter_chave(heap->itens[noAtual])){
        heap_trocar(heap, noAtual, noPai);
        heap_max_fix_up(heap, noPai);
    }
}


void heap_min_fix_up(HEAP *heap, int noAtual){

    if(noAtual <= 0)
        return;
        
    int noPai = (noAtual - 1) / 2;

    if(item_obter_chave(heap->itens[noPai]) > item_obter_chave(heap->itens[noAtual])){
        heap_trocar(heap, noAtual, noPai);
        heap_min_fix_up(heap, noPai);
    }
}


bool heap_max_inserir(HEAP *heap, ITEM *item){
    
    heap->itens[heap->tamanho] = item;
    heap->tamanho += 1;

    heap_max_fix_up(heap, heap->tamanho - 1);

    return(True);
}


bool heap_min_inserir(HEAP *heap, ITEM *item){

    heap->itens[heap->tamanho] = item;
    heap->tamanho += 1;

    heap_min_fix_up(heap, heap->tamanho - 1);
    
    return(True);
}


bool heap_inserir(HEAP *heap, ITEM *item){

    if(heap != NULL && item != NULL && !heap_cheia(heap)){
        #ifdef MAX_HEAP
            return(heap_max_inserir(heap, item));
        #endif
        #ifdef MIN_HEAP
            return(heap_min_inserir(heap, item));
        #endif
        fprintf(stderr, "Erro na inserção de item na heap! Não foi definido no arquivo .h se a heap é máxima ou mínima.\n");
    }

    return(False);
}


bool heap_tem_filho(HEAP *heap, int pai){

    /* é verificado apenas o filho da esquerda, tendo em vista que, se 
    o filho da esquerda for nulo, o filho da direita também será, pois
    a heap é uma árvore completa cheia. */

    int filhoEsquerda = pai * 2 + 1;

    if(filhoEsquerda < TAM_MAX && heap->itens[filhoEsquerda] != NULL)
        return(True);
    
    return(False);
}


int heap_obter_maior_filho(HEAP *heap, int pai){

    int filhoEsquerda = pai * 2 + 1;
    int filhoDireita = pai * 2 + 2;

    if(heap->itens[filhoDireita] == NULL)
        return(filhoEsquerda);

    int chaveFilhoEsquerda = item_obter_chave(heap->itens[filhoEsquerda]);
    int chaveFilhoDireita = item_obter_chave(heap->itens[filhoDireita]);

    return((chaveFilhoEsquerda >= chaveFilhoDireita) ? filhoEsquerda : filhoDireita);
}


int heap_obter_menor_filho(HEAP *heap, int pai){

    int filhoEsquerda = pai * 2 + 1;
    int filhoDireita = pai * 2 + 2;

    if(heap->itens[filhoDireita] == NULL)
        return(filhoEsquerda);

    int chaveFilhoEsquerda = item_obter_chave(heap->itens[filhoEsquerda]);
    int chaveFilhoDireita = item_obter_chave(heap->itens[filhoDireita]);

    return((chaveFilhoEsquerda <= chaveFilhoDireita) ? filhoEsquerda : filhoDireita);
}


void heap_max_fix_down(HEAP *heap, int noAtual){

    if(!heap_tem_filho(heap, noAtual))
        return;

    int maiorFilho = heap_obter_maior_filho(heap, noAtual);

    if(item_obter_chave(heap->itens[maiorFilho]) > item_obter_chave(heap->itens[noAtual])){
        heap_trocar(heap, noAtual, maiorFilho);
        heap_max_fix_down(heap, maiorFilho);
    }
}


void heap_min_fix_down(HEAP *heap, int noAtual){

    if(!heap_tem_filho(heap, noAtual))
        return;
    
    int menorFilho = heap_obter_menor_filho(heap, noAtual);

    if(item_obter_chave(heap->itens[menorFilho]) < item_obter_chave(heap->itens[noAtual])){
        heap_trocar(heap, noAtual, menorFilho);
        heap_min_fix_down(heap, menorFilho);
    }
}


bool heap_max_remover_inicio(HEAP *heap){

    item_apagar(&heap->itens[0]); 

    heap->itens[0] = heap->itens[heap->tamanho - 1]; 
    heap->itens[heap->tamanho - 1] = NULL;
    heap->tamanho -= 1;

    heap_max_fix_down(heap, 0);

    return(True);
}


bool heap_min_remover_inicio(HEAP *heap){

    item_apagar(&heap->itens[0]); 

    heap->itens[0] = heap->itens[heap->tamanho - 1]; 
    heap->itens[heap->tamanho - 1] = NULL;
    heap->tamanho -= 1;

    heap_min_fix_down(heap, 0);

    return(True);
}


bool heap_remover_inicio(HEAP *heap){

    if(heap != NULL && !heap_vazia(heap)){
        #ifdef MAX_HEAP
            return(heap_max_remover_inicio(heap));
        #endif
        #ifdef MIN_HEAP
            return(heap_min_remover_inicio(heap));
        #endif
        fprintf(stderr, "Erro na remoção de item na heap! Não foi definido no arquivo .h se a heap é máxima ou mínima.\n");
    }

    return(False);
}


ITEM *heap_inicio(HEAP *heap){

    if(heap != NULL && !heap_vazia(heap))
        return(heap->itens[0]);

    return(NULL); 
}


ITEM *heap_fim(HEAP *heap){

    if(heap != NULL && !heap_vazia(heap))
        return(heap->itens[heap->tamanho - 1]);

    return(NULL); 
}


void heap_imprimir(HEAP *heap){

    if(heap != NULL){
        for(int i = 0; heap->itens[i] != NULL; i++)
            item_imprimir(heap->itens[i]);
    }
}


int heap_tamanho(HEAP *heap){
    return((heap != NULL) ? heap->tamanho : -1);
}


bool heap_cheia(HEAP *heap){
    return((heap_tamanho(heap) == TAM_MAX));
}


bool heap_vazia(HEAP *heap){
    return(heap_tamanho(heap) == 0);
}