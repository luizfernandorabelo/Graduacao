#include <stdio.h>  
#include <stdlib.h> 

int main(int argc, char *argv[]){

    //Declaração e Inicialização de Variáveis:
    int barNumer = 0, dataNumber = 0; 
    int *data = NULL, *repetitions = NULL; 
    
    //Leitura e Armazenamento do Número de Barras e do Número de Dados:
    scanf("%d", &barNumer); 
    scanf("%d", &dataNumber);

    //Alocação Dinâmica de Memória:
    data = (int *) malloc ((dataNumber + 1) * sizeof(int)); 
    repetitions = (int *) calloc (barNumer, sizeof(int));

    //Leitura e Armazenamento dos Dados:     
    for(int i = 0; i < dataNumber; i++){
        scanf("%d", &data[i]); 
        repetitions[(data[i])] += 1;     
    }
    
    //Saída de Dados: 
    for(int i = 0; i < barNumer; i++){
        printf("%d - ", i);  
        while(repetitions[i] != 0){ 
            printf("#");
            repetitions[i] -= 1;     
        }
        printf("\n");
    }
    
    //Liberação de Memória ALocada:
    free(data);
    free(repetitions);

    return 0;
}