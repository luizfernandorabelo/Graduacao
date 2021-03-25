#include "Sorting.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) (a <= b) ? a : b

#define RUN 32


int pkdexNumberCompare(pokemon_t *pkmn1, pokemon_t *pkmn2){
    return(pkmn1->dexNumber - pkmn2->dexNumber);
}


int attackCompare(pokemon_t *pkmn1, pokemon_t *pkmn2){
    return(pkmn1->atk - pkmn2->atk);
}


int mainTypeCompare(pokemon_t *pkmn1, pokemon_t *pkmn2){
    return(pkmn1->mainType - pkmn2->mainType);
}


void swap(pokemon_t **pkdex, int pkmn1Index, int pkmn2Index){
    pokemon_t *temp = pkdex[pkmn1Index];
    pkdex[pkmn1Index] = pkdex[pkmn2Index];
    pkdex[pkmn2Index] = temp;
}


int partition(pokemon_t **pkdex, int startPos, int endPos, int (*compare) (pokemon_t *, pokemon_t *)){

    pokemon_t *pivot = pkdex[endPos]; int i = startPos-1;

    for(int j = startPos; j < endPos; j++){
        if(compare(pkdex[j], pivot) <= 0){
            swap(pkdex, i + 1, j);
            i++;
        }
    }

    swap(pkdex, i+1, endPos);

    return(i+1);
}


void quickSort(pokemon_t **pkdex, int startPos, int endPos, int (*compare) (pokemon_t *, pokemon_t *)){
    
    if(endPos <= startPos) return;
    
    int pivotPos = partition(pkdex, startPos, endPos, compare);
    
    quickSort(pkdex, startPos, pivotPos - 1, compare);
    quickSort(pkdex, pivotPos + 1, endPos, compare);
}


void preQuickSort(pokemon_t **pkdex, int totalPkmn, char *attribute){

    if(strcmp(attribute, PKDEX_NUMBER) == 0)
        return(quickSort(pkdex, 0, totalPkmn-1, &pkdexNumberCompare));
    if(strcmp(attribute, ATTACK) == 0)
        return(quickSort(pkdex, 0, totalPkmn-1, &attackCompare));
    if(strcmp(attribute, MAIN_TYPE) == 0)
        return(quickSort(pkdex, 0, totalPkmn-1, &mainTypeCompare));

    printf("O atributo %s não está definido\n", attribute);
}


void maxHeapify(pokemon_t **pkdex, int totalUnsorted, int index, int (*compare) (pokemon_t *, pokemon_t *)){

    int largest = index;
    int left = 3 * index + 1;
    int middle = 3 * index + 2;
    int right = 3 * index + 3;

    if(left < totalUnsorted && compare(pkdex[left], pkdex[largest]) > 0)
        largest = left;
    if(middle < totalUnsorted && compare(pkdex[middle], pkdex[largest]) > 0)
        largest = middle;
    if(right < totalUnsorted && compare(pkdex[right], pkdex[largest]) > 0)
        largest = right;

    if(largest != index){
        swap(pkdex, largest, index);
        maxHeapify(pkdex, totalUnsorted, largest, compare);
    }
}


void buildMaxHeap(pokemon_t **pkdex, int totalPkmns, int (*compare) (pokemon_t *, pokemon_t *)){
    for(int i = (totalPkmns - 2) / 3; i >= 0; i--)
        maxHeapify(pkdex, totalPkmns, i, compare);
}


void heapSort(pokemon_t **pkdex, int totalPkmns, int (*compare) (pokemon_t *, pokemon_t *)){

    buildMaxHeap(pkdex, totalPkmns, compare);

    int totalUnsorted = totalPkmns;

    while(totalUnsorted > 1){
        swap(pkdex, 0, totalUnsorted - 1);
        totalUnsorted --;
        maxHeapify(pkdex, totalUnsorted, 0, compare);
    }
}


void preHeapSort(pokemon_t **pkdex, int totalPkmn, char *attribute){

    if(strcmp(attribute, PKDEX_NUMBER) == 0)
        return(heapSort(pkdex, totalPkmn, &pkdexNumberCompare));
    if(strcmp(attribute, ATTACK) == 0)
        return(heapSort(pkdex, totalPkmn, &attackCompare));
    if(strcmp(attribute, MAIN_TYPE) == 0)
        return(heapSort(pkdex, totalPkmn, &mainTypeCompare));

    printf("O atributo %s não está definido\n", attribute);
}


void intsertionSort(pokemon_t **pkdex, int startPos, int endPos, int (*compare) (pokemon_t *, pokemon_t *)){

    for(int i = startPos + 1; i <= endPos; i++){
        pokemon_t *temp = pkdex[i];
        int j = i - 1;

        while(j >= startPos && compare(pkdex[j], temp) > 0){ 
            pkdex[j+1] = pkdex[j];
            j--;
        }
        pkdex[j+1] = temp;
    }
}


void merge(pokemon_t **pkdex, int startPos, int middlePos, int endPos, int (*compare) (pokemon_t *, pokemon_t *)){

    int firstHalfSize = middlePos - startPos + 1;
    int secondHalfSize = endPos - middlePos;
    
    pokemon_t **leftArray = malloc(firstHalfSize * sizeof(pokemon_t));
    pokemon_t **rightArray = malloc(secondHalfSize * sizeof(pokemon_t));
    
    for(int i = 0; i < firstHalfSize; i++)
        leftArray[i] = pkdex[startPos + i];
    
    for(int i = 0; i < secondHalfSize; i++)
        rightArray[i] = pkdex[middlePos + 1 + i];
    
    int i = 0, j = 0, k = startPos;

    while(i < firstHalfSize && j < secondHalfSize){
        if(compare(leftArray[i], rightArray[j]) <= 0)
            pkdex[k++] = leftArray[i++];
        else 
            pkdex[k++] = rightArray[j++];
    }

    while(i < firstHalfSize)
        pkdex[k++] = leftArray[i++];
    
    while(j < secondHalfSize)
        pkdex[k++] = rightArray[j++];
}


void timSort(pokemon_t **pkdex, int totalPkmn, int (*compare) (pokemon_t *, pokemon_t *)){

    for(int i = 0; i < totalPkmn; i+= RUN)
        intsertionSort(pkdex, i, min(i + 31, totalPkmn - 1), compare);
    
    for(int size = RUN; size < totalPkmn; size *= 2){
        for(int start = 0; start < totalPkmn; start += 2 * size){
            int middle = start + size - 1;
            int end = min(start + 2 * size - 1, totalPkmn - 1);
            merge(pkdex, start, middle, end, compare);
        }
    }
}


void preTimSort(pokemon_t **pkdex, int totalPkmn, char *attribute){

    if(strcmp(attribute, PKDEX_NUMBER) == 0)
        return(timSort(pkdex, totalPkmn, &pkdexNumberCompare));
    if(strcmp(attribute, ATTACK) == 0)
        return(timSort(pkdex, totalPkmn, &attackCompare));
    if(strcmp(attribute, MAIN_TYPE) == 0)
        return(timSort(pkdex, totalPkmn, &mainTypeCompare));

    printf("O atributo %s não está definido\n", attribute);
}


void sortPkdexByAttribute(pokemon_t **pkdex, int totalPkmn, int sortingType, char *attribute){

    switch(sortingType){
        case QUICK_SORT:
            return(preQuickSort(pkdex, totalPkmn, attribute));
        case HEAP_SORT:
            return(preHeapSort(pkdex, totalPkmn, attribute));
        case TIM_SORT:
            return(preTimSort(pkdex, totalPkmn, attribute));
        
        default:
            printf("O Método de Ordenação do tipo %d não está definido\n", sortingType);
    }   
}   