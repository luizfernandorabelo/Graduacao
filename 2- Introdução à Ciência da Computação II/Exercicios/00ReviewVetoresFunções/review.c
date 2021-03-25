#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { False, True } bool;


int *readNumberList(int *lenList);
/*Função que lê e armazena uma lista de números até o fim do arquivo. Tem como parâmetro o 
endereço do tamanho dessa lista. Retorna o endereço em que a lista foi alocada. */

bool isElementInArray(int element, int *array, int lenArray);
/*Função que verifica se um inteiro está presente em um array. Tem como parâmetros o inteiro a
ser verificado, o array e o tamanho do array. Retorna verdadeiro, se encontrado ou falso se não. */

int getOccurrenceNumber(int number, int *numberList, int lenList);
/*Função que retorna o número de ocorrências de um número em uma lista. Tem como parâmetros o
número, a lista de números e o tamanho da lista de números. */

void printNumbersAndOccurrences(int *numberList, int lenList);
/*Função que imprime os números e suas respectivas quantidades de ocorrências em uma lista. Tem
como parâmetros a lista de números e o tamanho da lista de números. */


int main(int argc, char *argv[]){

    int lenNumberList = 0;

    int *numberList = readNumberList(&lenNumberList);

    printNumbersAndOccurrences(numberList, lenNumberList);

    free(numberList);

    return 0;
}


int *readNumberList(int *lenList){

    int *list = NULL, numCounter = 0;
    
    while (!feof(stdin)){
        list = (int *) realloc(list, (numCounter+1) * sizeof(int));
        scanf("%d", &list[numCounter++]);
    }
    
    *lenList = numCounter;
    
    return list;
}


bool isElementInArray(int element, int *array, int lenArray){

    for(int i = 0; i < lenArray; i++){
        if(array[i] == element)
            return True;
    }

    return False;
}


int getOccurrenceNumber(int number, int *numberList, int lenList){

    int occurrences = 0;
    
    for(int i = 0; i < lenList; i++)
        occurrences = (numberList[i] == number) ? occurrences + 1 : occurrences;
    
    return occurrences;
}


void printNumbersAndOccurrences(int *numberList, int lenList){

    int *printedNumbers = NULL, lenPrintedNumbers = 0;
    
    for(int i = 0, occurrence = 0; i < lenList; i++){
        if(isElementInArray(numberList[i], printedNumbers, lenPrintedNumbers) == False){
            occurrence = getOccurrenceNumber(numberList[i], numberList, lenList);
            printf("%d (%d)\n", numberList[i], occurrence);
            printedNumbers = realloc(printedNumbers, (lenPrintedNumbers+1) * sizeof(int));
            printedNumbers[lenPrintedNumbers++] = numberList[i];    
        }
    }
    
    free(printedNumbers);
}