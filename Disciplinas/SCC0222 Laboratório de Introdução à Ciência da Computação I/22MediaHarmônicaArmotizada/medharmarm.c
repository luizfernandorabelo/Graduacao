#include <stdio.h> 
#include <stdlib.h> 

int readInt(); 
/*Função que lê um número inteiro na entrada padrão e o retorna */

double readDouble(); 
/*Função que lê um número real na entrada padrão e o retorna */

void printDouble(double n); 
/*Função que recebe um número real como parâmetro e o imprime na saída padrão */

int main(int argc, char *argv[]){

    //Leitura do Número de Trabalhos:
    int gradesNumber = readInt();

    //Alocação Dinâmica de Memória para as Notas:
    double *grades = malloc(gradesNumber * sizeof(double)); 

    //Leitura e Armazenamento das Notas:
    for(int i = 0; i < gradesNumber; i++){ 
        grades[i] = readDouble(); 
    }

    //Cálculo da Média Harmônica Armotizada:
    double quotientSum = 0; 
    for(int i = 0; i < gradesNumber; i++){ 
        quotientSum = quotientSum + 1 / (grades[i] + 1); 
    }
    double average = gradesNumber / quotientSum - 1;
    
    //Liberação de Memória Alocada:
    free(grades); 

    //Impressão da Média Calculada:    
    printDouble(average); 

    return 0;
}

int readInt(){
    int n; 
    scanf("%d", &n); 
    return n;
}

double readDouble(){
    double n; 
    scanf("%lf", &n);
    return n;
}

void printDouble(double n){
    printf("%.2lf\n", n);
}