#include "sorting.h"

#include <stdlib.h>

#define bool char
#define True 1
#define False 0


typedef struct no_ NO;

struct no_{
    int chave;
    NO *proximo;
};

typedef struct{
    NO *inicio;
    NO *fim;
}BUCKET;


void swap(int *chave1, int *chave2){
    int aux = *chave1;
    *chave1 = *chave2;
    *chave2 = aux;
}


void bubble_sort(VETOR *vetor){
    
    int *chaves = vetor->chaves;
    int ultimo = vetor->tamanho - 1;
    bool ordenado = False;
    
    while(!ordenado){
        ordenado = True;
        for(int i = 0; i < ultimo; i++){
            if(chaves[i] > chaves[i+1]){
                ordenado = False;
                swap(&chaves[i], &chaves[i+1]);
            }
        }
        ultimo--;
    }
}


void selection_sort(VETOR *vetor){

    int *chaves = vetor->chaves;
    int tamanho = vetor->tamanho;

    for(int i = 0; i < tamanho - 1; i++){
        int chaveMin = i;
        for(int j = i + 1; j < tamanho; j++){
            if(chaves[j] < chaves[chaveMin])
                chaveMin = j;
        }
        swap(&chaves[i], &chaves[chaveMin]);
    }
}


void insertion_sort(VETOR *vetor){

    int *chaves = vetor->chaves;
    int tamanho = vetor->tamanho;

    if(tamanho <= 1)
        return;

    for(int j = 1; j < tamanho; j++){
        int menorChave = chaves[j];
        int i = j - 1;
        while(i >= 0 && menorChave < chaves[i]){
            chaves[i+1] = chaves[i];
            i--;
        }
        chaves[i+1] = menorChave;
    }
}


void merge(int *chaves, int inicio, int centro, int fim){

    int *aux = calloc(fim - inicio + 1, sizeof(int));

    int i = inicio, j = centro + 1, k = 0;

    while(i <= centro && j <= fim){
        if(chaves[i] < chaves[j])
            aux[k++] = chaves[i++];
        else
            aux[k++] = chaves[j++];
    }

    while(i <= centro)
        aux[k++] = chaves[i++]; 
 
    while(j <= fim)
        aux[k++] = chaves[j++]; 
    
    for(int i = inicio, k = 0; i <= fim; i++, k++)
        chaves[i] = aux[k];

    free(aux);
}


void merge_sort_rec(int *chaves, int inicio, int fim){

    if(inicio >= fim)
        return;
    
    int centro = (inicio + fim) / 2;

    merge_sort_rec(chaves, inicio, centro);
    merge_sort_rec(chaves, centro + 1, fim);

    merge(chaves, inicio, centro, fim);
}


void merge_sort(VETOR *vetor){
    return(merge_sort_rec(vetor->chaves, 0, vetor->tamanho-1));
}


int partition(int *chaves, int inicio, int fim){

    int pivo = chaves[fim];
    int i = inicio - 1;

    for(int j = inicio; j <= fim; j++){
        if(chaves[j] <= pivo){
            swap(&chaves[j], &chaves[i+1]);
            i++;
        }
    }

    return(i);
}


void quick_sort_rec(int *chaves, int inicio, int fim){

    if(inicio >= fim)
        return;
    
    int indicePivo = partition(chaves, inicio, fim);

    quick_sort_rec(chaves, inicio, indicePivo - 1);
    quick_sort_rec(chaves, indicePivo + 1, fim);
}


void quick_sort(VETOR *vetor){
    return(quick_sort_rec(vetor->chaves, 0, vetor->tamanho-1));
}


void max_heapfy(int *chaves, int pai, int fim){

    int filhoEsquerda = 2 * pai + 1;
    int filhoDireita = 2 * pai + 2;

    if(filhoEsquerda > fim)
        return;
    
    int maiorFilho = (filhoDireita <= fim && chaves[filhoDireita] > chaves[filhoEsquerda]) ? filhoDireita : filhoEsquerda;

    if(chaves[maiorFilho] > chaves[pai])
        swap(&chaves[maiorFilho], &chaves[pai]);
    
    max_heapfy(chaves, maiorFilho, fim);
}


void construir_max_heap(int *chaves, int fim){

    int ultimoPai = (fim - 1) / 2;

    for(int i = ultimoPai; i >= 0; i--)
        max_heapfy(chaves, i, fim);
}


void heap_sort(VETOR *vetor){

    int fim = vetor->tamanho - 1;
    int *chaves = vetor->chaves;

    construir_max_heap(chaves, fim);

    while(fim > 0){
        swap(&chaves[0], &chaves[fim]);
        fim--;
        max_heapfy(chaves, 0, fim);
    }
}


void counting_sort(VETOR *vetor){

    int *chaves = vetor->chaves;
    int tamanhoVetor = vetor->tamanho;

    int *copia = malloc(tamanhoVetor * sizeof(int));

    int menorChave = chaves[0], maiorChave = chaves[0];

    for(int i = 0; i < tamanhoVetor; i++){
        int chaveAtual = chaves[i];
        if(chaveAtual > maiorChave)
            maiorChave = chaveAtual;
        else if(chaveAtual < menorChave)
            menorChave = chaveAtual;
        copia[i] = chaveAtual;
    }

    int rangeContagem = maiorChave - menorChave + 1;

    int *contagem = calloc(rangeContagem, sizeof(int));
    int *indices = calloc(rangeContagem, sizeof(int));

    for(int i = 0; i < tamanhoVetor; i++)
        contagem[ chaves[i] - menorChave ] += 1;

    for(int i = 0, indiceInicio = 0; i < rangeContagem; i++){
        indices[i] = indiceInicio;
        indiceInicio += contagem[i];
    }
    
    for(int i = 0; i < tamanhoVetor; i++){
        int indice = indices[ copia[i] - menorChave ];
        chaves[indice] = copia[i];
        indices[ copia[i] - menorChave ] += 1;
    }

    free(copia);
    free(contagem);
    free(indices);
}


void bucket_sort(VETOR *vetor){

    int *chaves = vetor->chaves;
    int tamanhoVetor = vetor->tamanho;

    int menorChave = chaves[0], maiorChave = chaves[0];

    for(int i = 1; i < tamanhoVetor; i++){
        int chaveAtual = chaves[i];
        if(chaveAtual < menorChave)
            menorChave = chaveAtual;
        else if(chaveAtual > maiorChave)
            maiorChave = chaveAtual;
    }

    int rangeBuckets = maiorChave - menorChave + 1;

    BUCKET *buckets = calloc(rangeBuckets, sizeof(BUCKET));

    for(int i = 0; i < tamanhoVetor; i++){
        NO *noAtual = malloc(sizeof(NO));
        noAtual->chave = chaves[i];
        noAtual->proximo = NULL;
        int indiceBucket = chaves[i] - menorChave;
        if(buckets[indiceBucket].inicio == NULL)
            buckets[indiceBucket].inicio = noAtual;
        else
            buckets[indiceBucket].fim->proximo = noAtual;
        buckets[indiceBucket].fim = noAtual;
    }

    for(int i = 0, j = 0; i < rangeBuckets; i++){
        NO *noAtual = buckets[i].inicio;
        while(noAtual != NULL){
            NO *proximo = noAtual->proximo;
            chaves[j++] = noAtual->chave;
            free(noAtual);
            noAtual = proximo;
        }
    }

    free(buckets);
}


void radix_sort_10(VETOR *vetor){

    int *chaves = vetor->chaves;
    int tamanhoVetor = vetor->tamanho;
    int maiorChave = chaves[0];

    for(int i = 1; i < tamanhoVetor; i++){
        int chaveAtual = chaves[i];
        if(chaveAtual > maiorChave)
            maiorChave = chaveAtual;
    }

    int *copia = malloc(tamanhoVetor * sizeof(int));

    for(int divisor = 1; (maiorChave / divisor) > 0; divisor *= 10){
        int contagem[10] = {0}, indices[10] = {0};
        for(int i = 0; i < tamanhoVetor; i++){
            int indice = (chaves[i] / divisor) % 10;
            contagem[indice] += 1;
            copia[i] = chaves[i];
        }
        for(int i = 1; i < 10; i++){
            indices[i] = indices[i-1] + contagem[i-1];
        }
        for(int i = 0; i < tamanhoVetor; i++){
            int indice = (copia[i] / divisor) % 10;
            chaves[ indices[indice] ] = copia[i];
            indices[indice] += 1;
        } 
    }

    free(copia);
}


void radix_sort_256(VETOR *vetor){

    int *chaves = vetor->chaves;
    int tamanhoVetor = vetor->tamanho;

    int *copia = malloc(tamanhoVetor * sizeof(int));

    for(int shift = 0; shift < 32; shift += 8){
        int contagem[256] = {0}, indices[256] = {0};
        for(int i = 0; i < tamanhoVetor; i++){
            int indice = (chaves[i] >> shift) & 255;
            contagem[indice] += 1;
            copia[i] = chaves[i];
        }
        for(int i = 1; i < 256; i++){
            indices[i] = indices[i-1] + contagem[i-1];
        }
        for(int i = 0; i < tamanhoVetor; i++){
            int indice = (copia[i] >> shift) & 255;
            chaves[ indices[indice] ] = copia[i];
            indices[indice] += 1;
        }
    }

    free(copia);
}