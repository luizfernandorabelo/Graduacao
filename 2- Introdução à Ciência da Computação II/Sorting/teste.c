#include "vetor.h"
#include "sorting.h"

#include <stdio.h>
#include <stdlib.h>

#define N_ARGS 4


int main(int argc, char *argv[]){

    if(argc < 4){
        printf("You must define the range of the array!\n");
        printf("Usage: ./progname minValue maxValue lenght\n");
        exit(EXIT_FAILURE);
    }

    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    int tamanho = atoi(argv[3]);

    // Bubble Sort:
    VETOR *vetorBubble = gerar_vetor(min, max, tamanho);
    FILE *arquivoBubble = fopen("./OutputTestes/bubble.txt", "w");
    fprintf(arquivoBubble, "Entrada:\n");
    imprimir_vetor(vetorBubble, arquivoBubble);
    bubble_sort(vetorBubble);
    fprintf(arquivoBubble, "Saída:\n");
    imprimir_vetor(vetorBubble, arquivoBubble);
    fclose(arquivoBubble);
    liberar_vetor(&vetorBubble);

    // Selection Sort:
    VETOR *vetorSelection = gerar_vetor(min, max, tamanho);
    FILE *arquivoSelection = fopen("./OutputTestes/selection.txt", "w");
    fprintf(arquivoSelection, "Entrada:\n");
    imprimir_vetor(vetorSelection, arquivoSelection);
    selection_sort(vetorSelection);
    fprintf(arquivoSelection, "Saída:\n");
    imprimir_vetor(vetorSelection, arquivoSelection);
    fclose(arquivoSelection);
    liberar_vetor(&vetorSelection);

    // Insertion Sort:
    VETOR *vetorInsertion = gerar_vetor(min, max, tamanho);
    FILE *arquivoInsertion = fopen("./OutputTestes/insertion.txt", "w");
    fprintf(arquivoInsertion, "Entrada:\n");
    imprimir_vetor(vetorInsertion, arquivoInsertion);
    insertion_sort(vetorInsertion);
    fprintf(arquivoInsertion, "Saída:\n");
    imprimir_vetor(vetorInsertion, arquivoInsertion);
    fclose(arquivoInsertion);
    liberar_vetor(&vetorInsertion);

    // Merge Sort:
    VETOR *vetorMerge = gerar_vetor(min, max, tamanho);
    FILE *arquivoMerge = fopen("./OutputTestes/merge.txt", "w");
    fprintf(arquivoMerge, "Entrada:\n");
    imprimir_vetor(vetorMerge , arquivoMerge);
    merge_sort(vetorMerge);
    fprintf(arquivoMerge, "Saída:\n");
    imprimir_vetor(vetorMerge, arquivoMerge);
    fclose(arquivoMerge);
    liberar_vetor(&vetorMerge);

    // Quick Sort:
    VETOR *vetorQuick = gerar_vetor(min, max, tamanho);
    FILE *arquivoQuick = fopen("./OutputTestes/quick.txt", "w");
    fprintf(arquivoQuick, "Entrada:\n");
    imprimir_vetor(vetorQuick, arquivoQuick);
    quick_sort(vetorQuick);
    fprintf(arquivoQuick, "Saída:\n");
    imprimir_vetor(vetorQuick, arquivoQuick);
    fclose(arquivoQuick);
    liberar_vetor(&vetorQuick);

    // Heap Sort:
    VETOR *vetorHeap = gerar_vetor(min, max, tamanho);
    FILE *arquivoHeap = fopen("./OutputTestes/heap.txt", "w");
    fprintf(arquivoHeap, "Entrada:\n");
    imprimir_vetor(vetorHeap, arquivoHeap);
    heap_sort(vetorHeap);
    fprintf(arquivoHeap, "Saída:\n");
    imprimir_vetor(vetorHeap, arquivoHeap);
    fclose(arquivoHeap);
    liberar_vetor(&vetorHeap);

    // Counting Sort
    VETOR *vetorCounting = gerar_vetor(min, max, tamanho);
    FILE *arquivoCounting = fopen("./OutputTestes/counting.txt", "w");
    fprintf(arquivoCounting, "Entrada:\n");
    imprimir_vetor(vetorCounting, arquivoCounting);
    counting_sort(vetorCounting);
    fprintf(arquivoCounting, "Saída:\n");
    imprimir_vetor(vetorCounting, arquivoCounting);
    fclose(arquivoCounting);
    liberar_vetor(&vetorCounting);

    // Bucket Sort
    VETOR *vetorBucket = gerar_vetor(min, max, tamanho);
    FILE *arquivoBucket = fopen("./OutputTestes/bucket.txt", "w");
    fprintf(arquivoBucket, "Entrada:\n");
    imprimir_vetor(vetorBucket, arquivoBucket);
    bucket_sort(vetorBucket);
    fprintf(arquivoBucket, "Saída:\n");
    imprimir_vetor(vetorBucket, arquivoBucket);
    fclose(arquivoBucket);
    liberar_vetor(&vetorBucket);

    // Radix Sort 10 
    VETOR *vetorRadix10 = gerar_vetor(min, max, tamanho);
    FILE *arquivoRadix10 = fopen("./OutputTestes/radix10.txt", "w");
    fprintf(arquivoRadix10, "Entrada:\n");
    imprimir_vetor(vetorRadix10, arquivoRadix10);
    radix_sort_10(vetorRadix10);
    fprintf(arquivoRadix10, "Saída:\n");
    imprimir_vetor(vetorRadix10, arquivoRadix10);
    fclose(arquivoRadix10);
    liberar_vetor(&vetorRadix10);

    // Radix Sort 256
    VETOR *vetorRadix256 = gerar_vetor(min, max, tamanho);
    FILE *arquivoRadix256 = fopen("./OutputTestes/radix256.txt", "w");
    fprintf(arquivoRadix256, "Entrada:\n");
    imprimir_vetor(vetorRadix256, arquivoRadix256);
    radix_sort_256(vetorRadix256);
    fprintf(arquivoRadix256, "Saída:\n");
    imprimir_vetor(vetorRadix256, arquivoRadix256);
    fclose(arquivoRadix256);
    liberar_vetor(&vetorRadix256);

    return(0);
}