#include <stdio.h>
#include <stdlib.h>

int *readData(int *key, int *len);
int binarySearch(int *array, int len, int key);
int compar(const void *a, const void *b);

int main(int argc, char *argv[]){
    
    //Declaração e Inicialização de Variáveis:
    int *array = NULL, key = 0, len = 0, pos = 0; 
    
    //Leitura e Armazenamento de Dados:
    array = readData(&key, &len);
    
    //Busca Binária:
    pos = binarySearch(array, len, key);
    
    //Saída de Dados:
    switch(pos){
        case -1: //se a posição retornada for -1 (chave não encontrada)
            printf("Chave inexistente\n");
            break;
        default:
            printf("%d\n", pos);
            break;
    }

    //Libereação de Memória Alocada:
    free(array);

    return 0;
}

int *readData(int *key, int *len){
    //Leitura e Armazenamento do Tamanho do Array e da Chave:
    scanf("%d %d", len, key);
    //Alocação Dinâmica de Memória:
    int *array = malloc(*len * sizeof(int));
    //Leitura e Armazenamento dos Elementos do Array:
    for(int i = 0; i < *len; i++){
        scanf("%d", &array[i]);
    }
    //Ordenação do Array:
    qsort(array, *len, sizeof(int), compar);
    //Retorno do Endereço dos Bytes Alocados para o Array:
    return array;
}

int binarySearch(int *array, int len, int key){
    //Declaração e Iniciialização de Variáveis:
    int min = 0, max = len-1, middle;
    //Procura pela Chave:
    while(min <= max){ 
        middle = (min + max) / 2;
        if(array[middle] == key){ 
            return middle;
        }
        else if(array[middle] < key){ 
            min = middle + 1;
        }
        else if(array[middle] > key){ 
            max = middle - 1;
        }
    }
    return -1; //se a chave não for encontrada
}

int compar(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}