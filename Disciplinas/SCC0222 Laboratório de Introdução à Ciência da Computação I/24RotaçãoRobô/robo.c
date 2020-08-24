#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_MOVES 200

int main(int argc, char *argv[]){

    //Alocação Dinâmica de Memória:
    char *moves = calloc(MAX_MOVES + 1, sizeof(char)); 

    //Leitura e Armazenamento dos Movimentos:
    scanf("%s", moves);

    //Realocação Dinâmica de Memória (libereação das células nulas):
    short int lenght = strlen(moves) + 1; 
    moves = (char *) realloc(moves, lenght * sizeof(char)); 
    
    //Declaração e Iicialização de Variáveis:
    char orientation[7]; 
    short int posCounter = 0; 
    short int i = 0; 
    
    //Determinação da Orientação do Robô Móvel:
    while(moves[i] != 0){ 
        switch(moves[i]){
            case 'D': 
                posCounter += 1; 
                break; 
            case 'E': 
                posCounter -= 1;
                break; 
            default:  
                break; 
        }   
  
        if(posCounter == 4 || posCounter == -4){
            posCounter = 0; //sua posição volta a ser zero (como se ele não tivesse girado)
        }

        i++; 
    }

    //Liberação de Memória Alocada:
    free(moves); 

    if(posCounter == 0){ 
        strcpy(orientation, "Norte"); //(posição 0 nos sentidos horário e antiorário)
    }
    else if(posCounter == 1 || posCounter == -3){
        strcpy(orientation, "Leste"); //(posição 1 no sentido horário e -3 no sentido anti-horário)
    }
    else if(posCounter == 2 || posCounter == -2){ 
        strcpy(orientation, "Sul"); //(posição 2 no sentido horário e -2 no sentido anti-horário)
    }
    else{ 
        strcpy(orientation, "Oeste"); //(posição 3 no sentido horário e -1 no sentido anti-horário)
    }

    //Impressão da Orientação Final do Robô:
    printf("%s\n", orientation); 
    
    return 0;
}