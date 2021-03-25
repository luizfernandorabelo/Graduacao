#include "Sorting.h"

#include <stdio.h>
#include <stdlib.h>

//Macro que define o máximo entre dois valores a,b
#define max(a,b) (a >= b) ? a : b

typedef struct node_ NODE;

struct node_{
    pokemon_t *pkmn;
    NODE *next;
};

typedef struct{
    NODE *start;
    NODE *end;
}BUCKET;


void countingSortPkdex(pokemon_t **pkdex, int totalPkmn){

    //Alocação de memória para cópia da pokedex:
    pokemon_t **pkdexCopy = malloc(totalPkmn * sizeof(pokemon_t *));

    //Inicialização do menor e maior ataque como o da primeira posição:
    int minAttack = pkdex[0]->atk, maxAttak = pkdex[0]->atk;
    
    //Determinação do menor e maior ataque e cópia dos pokemons:
    for(int i = 0; i < totalPkmn; i++){
        if(pkdex[i]->atk < minAttack) minAttack = pkdex[i]->atk;
        else if(pkdex[i]->atk > maxAttak) maxAttak = pkdex[i]->atk;
        pkdexCopy[i] = pkdex[i];
    }
    
    //Alocação do vetor de contagem:
    int countingSize = maxAttak - minAttack + 1;
    int *counting = calloc(countingSize, sizeof(int));
    
    //Atribuição das ocorrências no vetor de contagem:
    for(int i = 0; i < totalPkmn; i++)
        counting[ pkdex[i]->atk - minAttack ] += 1; 
    
    //Contagem acumulada das posições dos ataques:
    int previousPos = 0, currentPos = 0;
    for(int i = 0; i < countingSize; i++){
        currentPos = counting[i];
        counting[i] = previousPos;
        previousPos += currentPos;
    }   
    
    //Atribuição dos pokemons às suas posições oredenadas por ataque:
    for(int i = 0; i < totalPkmn; i++){
        int pos = counting[ pkdexCopy[i]->atk - minAttack ];
        pkdex[pos] = pkdexCopy[i];
        counting[ pkdexCopy[i]->atk - minAttack ] += 1;
    }

    //Liberação de memória auxiliar alocada:
    free(counting); free(pkdexCopy);
}


void radixSortPkdex(pokemon_t **pkdex, int totalPkmn){

    //Determinação do maior valor para ataques:
    int maxAttack = pkdex[0]->atk;
    for(int i = 1; i < totalPkmn; i++)
        maxAttack = max(pkdex[i]->atk, maxAttack);

    //Counting Sort de cada digito:
    for(int exp = 1; (maxAttack / exp) > 0; exp *= 10){

        //Alocação de memória para a cópida ordenada da pokedex e vetor de contaem:
        pokemon_t **sorted = calloc(totalPkmn, sizeof(pokemon_t *));
        int *counting = calloc(10, sizeof(int));
        
        //Atribuição das ocorrências no vetor de contagem:
        for(int i = 0; i < totalPkmn; i++)
            counting[ (pkdex[i]->atk / exp) % 10 ] += 1;
        
        //Contagem acumulada dos elementos:
        for(int i = 1; i < 10; i++)
            counting[i] += counting[i-1];

        //Atribuição dos valores ordenados na cópia da pokedex:
        for(int i = totalPkmn - 1; i >= 0; i--){
            sorted[ counting[pkdex[i]->atk / exp % 10] - 1 ] = pkdex[i];
            counting[ pkdex[i]->atk / exp % 10] -= 1;
        }

        //Atribuição dos valores da cópia para a pokedex original:
        for(int i = 0; i < totalPkmn; i++)
            pkdex[i] = sorted[i];
        
        //Liberação de memória auxiliar para contagem:
        free(counting); free(sorted);
    }        
} 


void bucketSortPkdex(pokemon_t **pkdex, int totalPkmn){

    //Determinação dos maiores e menores ataques: 
    int maxAttack = pkdex[0]->atk, minAttack = pkdex[0]->atk;
    for(int i = 1; i < totalPkmn; i++){
        if(pkdex[i]->atk < minAttack) minAttack = pkdex[i]->atk;
        else if(pkdex[i]->atk > maxAttack) maxAttack = pkdex[i]->atk;
    }

    //Alocação de memória para os buckets:
    int bucketsSize = maxAttack - minAttack + 1;
    BUCKET *buckets = calloc(bucketsSize, sizeof(BUCKET));

    //Encadeamento dos nos nas devidas posições:
    for(int i = 0; i < totalPkmn; i++){

        //Criação de um novo nó para a posição atual:
        NODE *newNode = malloc(sizeof(NODE));
        newNode->pkmn = pkdex[i];
        newNode->next = NULL;

        //Determinação da posição atual do bucket:
        int currentBucketPos = pkdex[i]->atk - minAttack;

        //Encadeamento do no:
        if(buckets[currentBucketPos].start == NULL) 
            buckets[currentBucketPos].start = newNode;
        else 
            buckets[currentBucketPos].end->next = newNode;
        buckets[currentBucketPos].end = newNode;
    }

    //Atribuição dos pokemons na pokedex ordenados por ataque pelo desencadeamento dos nos:
    for(int i = 0, pkdexPos = 0; i < bucketsSize; i++){
        NODE *currentNode = buckets[i].start;
        while(currentNode != NULL){
            pkdex[pkdexPos++] = currentNode->pkmn;
            NODE *del = currentNode;
            currentNode = currentNode->next;
            buckets[i].start = currentNode;
            free(del);
        }
    }

    //Liberação de memória auxiliar:
    free(buckets);
}


void sortPkdexByAttack(pokemon_t **pkdex, int totalPkmn, int sortingType){

    switch(sortingType){
        case COUNTING_SORT:
            return(countingSortPkdex(pkdex, totalPkmn));
        case RADIX_SORT:
            return(radixSortPkdex(pkdex, totalPkmn));
        case BUCKET_SORT:
            return(bucketSortPkdex(pkdex, totalPkmn));
 
        default:
            printf("O método de ordenação do tipo %d não está definido\n", sortingType);
    }
}