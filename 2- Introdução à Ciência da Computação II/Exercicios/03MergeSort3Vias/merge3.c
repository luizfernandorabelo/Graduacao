#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char *name;
    double price;
}BOOK;

typedef struct{
    BOOK **books;
    int size;
}LIBRARY;


int readIntegerNumber(FILE *stream);
/*Função que lê um número inteiro de um fluxo e o retorna.*/

double readDoubleNumber(FILE *stream);
/*Função que lê um número double de um fluxo e o retorna.*/

char *readString(FILE *stream);
/*Função que lê uma cadeeia de caracteres de um fluxo e a retorna o endereço em
que a mesma foi alocada.*/

LIBRARY *loadLibraryBooks(FILE *stream);
/*Função que aloca toda a memória necessária para o armazenamento da biblioteca
e dos livros. Lê o número de livros do fluxo stream e lê também os dados (nome e
preço) de cada um dos livros. Retorna o endereço em que a biblioteca foi alocada.*/

void unloadLibraryBooks(LIBRARY *library);
/*Função que libera o espaço de memória alocado para o armazenamento da biblioteca, 
dos livros e de suas informações. Tem como parâmetro um ponteiro para a biblioteca 
a ser "excluída".*/

void mergeSort3(BOOK **books, int startPos, int endPos);
/*Função que ordena os livros com base em seus preços. Tem como parâmetros um ponteiro
para o conjunto de livros a ser ordenado, sua posição inicial e sua posição final.*/

void sortLibraryBooksByPrice(LIBRARY *library);
/*Função que direciona os livros para a ordenação (que é feita pelo merge sort de 3
vias). Tem como parâmetro um ponteiro para a biblioteca a ser ordenada.*/

void printLibraryBooks(LIBRARY *library, FILE *stream);
/*Função que escreve os dados de todos os livros de uma biblioteca em um fluxo stream.*/


int main(int argc, char *argv[]){

    //Criação da Biblioteca e Leitura dos Livros:
    LIBRARY *myLibrary = loadLibraryBooks(stdin);
    
    //Ordenação dos Livros por Preço:
    sortLibraryBooksByPrice(myLibrary);

    //Impressão dos Dados dos Livros:
    printLibraryBooks(myLibrary, stdout);

    //Liberação de Memória Alocada:
    unloadLibraryBooks(myLibrary);
    
    return(0);
}


int readIntegerNumber(FILE *stream){

    int integerNumber = 0;

    fscanf(stream, "%d", &integerNumber);

    return integerNumber;
}


double readDoubleNumber(FILE *stream){

    double doubleNumber = 0;

    fscanf(stream, "%lf", &doubleNumber);

    return(doubleNumber);
}


char *readString(FILE *stream){

    char *string = NULL, character = 0;
    int charCounter = 0;
    
    while(character < 33)
        character = fgetc(stream);

    do{
        string = (char *) realloc(string, (charCounter+2));
        string[charCounter++] = character;
        character = fgetc(stream);
    }while(character != ',' && character != '\n' && character != '\r' && character != EOF);

    string[charCounter] = '\0';
    
    return(string);
}


LIBRARY *loadLibraryBooks(FILE *stream){

    LIBRARY *library = malloc(sizeof(LIBRARY));
    library->size = readIntegerNumber(stream);
    library->books = malloc(library->size * sizeof(BOOK *));
    
    for(int i = 0; i < library->size; i++){
        library->books[i] = malloc(sizeof(BOOK));
        library->books[i]->name = readString(stream);
        library->books[i]->price = readDoubleNumber(stream);
    }

    return(library);
}


void unloadLibraryBooks(LIBRARY *library){

    for(int i = 0; i < library->size; i++){
        free(library->books[i]->name);
        free(library->books[i]);
    }
    
    free(library->books);
    free(library);
}


void mergeSort3(BOOK **books, int startPos, int endPos){

    if(endPos >= startPos){
        for(int i = startPos; i <= endPos; i++)
            printf("%.2lf ", books[i]->price);
        printf("\n");
    }
    
    if(endPos <= startPos) return;

    int thirdPart = (endPos - startPos) / 3;

    int newStart1 = startPos; 
    int newEnd1 = startPos + thirdPart;
    int newStart2 = newEnd1 + 1;
    int remaining = endPos - newEnd1;
    int newEnd2 = (remaining % 2 == 0) ? newStart2 + remaining / 2 - 1 : newStart2 + thirdPart;
    int newStart3 = newEnd2 + 1, newEnd3 = endPos;

    mergeSort3(books, newStart1, newEnd1);
    mergeSort3(books, newStart2, newEnd2);
    mergeSort3(books, newStart3, newEnd3);
    
    BOOK **aux = malloc((endPos - startPos + 1) * sizeof(BOOK *));

    int i = newStart1, j = newStart2, k = newStart3, l = 0;

    while(i <= newEnd1 && j <= newEnd2 && k <= newEnd3){
        if(books[i]->price <= books[j]->price && books[i]->price <= books[k]->price)
            aux[l++] = books[i++];
        else if(books[j]->price <= books[i]->price && books[j]->price <= books[k]->price)
            aux[l++] = books[j++];
        else
            aux[l++] = books[k++];
    }    

    while(i <= newEnd1 && j <= newEnd2){
        if(books[i]->price <= books[j]->price) aux[l++] = books[i++];
        else aux[l++] = books[j++];
    }
    while(i <= newEnd1 && k <= newEnd3){
        if(books[i]->price <= books[k]->price) aux[l++] = books[i++];
        else aux[l++] = books[k++];
    }
    while(j <= newEnd2 && k <= newEnd3){
        if(books[j]->price <= books[k]->price) aux[l++] = books[j++];
        else aux[l++] = books[k++];
    }
    
    while(i <= newEnd1)
        aux[l++] = books[i++];
    while(j <= newEnd2)
        aux[l++] = books[j++];
    while(k <= newEnd3)
        aux[l++] = books[k++];

    for(int m = startPos, l = 0; m <= endPos; l++, m++)
        books[m] = aux[l];

    free(aux);
}


void sortLibraryBooksByPrice(LIBRARY *library){
    mergeSort3(library->books, 0, library->size-1);
}


void printLibraryBooks(LIBRARY *library, FILE *stream){

    printf("\n");
    
    for(int i = 0; i < library->size; i++)
        fprintf(stream, "%s, R$%.2lf\n", library->books[i]->name, library->books[i]->price);
}