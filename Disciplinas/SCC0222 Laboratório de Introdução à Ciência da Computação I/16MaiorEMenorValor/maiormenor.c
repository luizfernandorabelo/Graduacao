#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char *argv[]){

    //Declaração de Variáveis na Stack:
    int elementsNumber = 0; 
    int *sequence = NULL; 

    //Leitura e Armazenamento do Tamanho da Sequência:
    scanf("%d", &elementsNumber);

    //Alocação Dinâmica de Memória:
    sequence = (int *) malloc(elementsNumber * sizeof(int)); 

    //Variáveis Auxiliares Para Verificação do Maior e Menor Valor:
    int biggest, shortest; 

    //Leitura e Armazenamento de Dados no Conjunto:
    for(int i = 0; i < elementsNumber; i++){
        scanf("%d", &sequence[i]); 
    }

    //Determinação do Maior e do Menor Valor:
    biggest = sequence[0]; 
    shortest = sequence[0];
    
    for(int i = 1; i < elementsNumber; i++){
        if(sequence[i] > biggest){ 
            biggest = sequence[i]; 
        }
        else if(sequence[i] < shortest){ 
            shortest = sequence[i]; 
        }
    }

    //Liberação de Memória ALocada:
    free(sequence);

    //Impressão do Maior e do Menor Valor:
    printf("max: %d\nmin: %d\n", biggest, shortest); 

    return 0;
}
