#include <stdio.h> 
#include <stdlib.h>

#define ARRAY_SIZE 31 

int main(int argc, char *argv[]){

    //Alocação Dinâmica de Memória:
    int *array = calloc(ARRAY_SIZE, sizeof(int)); 

    //Leitura e Armazenamento de Dados:
    for(int i = 0; i < ARRAY_SIZE; i++){ 
        scanf("%d", &array[i]); 
    }

    //Impressão dos Números Divisíveis pelo Último:
    for(int i = 0; i < ARRAY_SIZE; i++){
        if(array[i] % array[ARRAY_SIZE-1] == 0){ 
            printf("%d\n", array[i]); 
        }
    }

    //Liberação de Memória Alocada:
    free(array); 

    return 0;
}