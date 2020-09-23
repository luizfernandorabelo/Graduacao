#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FILE_PREFIX "numberList"
#define BINARY_FILE_EXTENSION ".dat"
#define TEXT_FILE_EXTENSION ".txt"


void checkMemoryAlocation(void *pointer);
/*Função que checa o sucesso de alocações de memória e aberturas de 
arquivos. Se o ponteiro for nulo, aborta o programa.*/

char *createFileName(char *fileExtension, int listSize);
/*Função que cria e retorna um nome de arquivo na forma "prefixo" + 
"tamanho da lista" + "extensão".*/

void writeNumberListToBinaryFile(int *numberList, int listSize);
/*Função que cria um novo arquivo binário e salva nele a lista de 
números aleatórios.*/

void writeNumberListToTextFile(int *numberList, int listSize);
/*Função que cria um novo arquivo textual e salva nele a lista de 
números aleatórios.:*/


int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Usage: ./progname listSize maxValue\n");
        exit(0);
    }
    
    srand(time(NULL));

    int listSize = atoi(argv[1]);
    int maxValue = atoi(argv[2]);
    
    int *numberList = malloc(listSize * sizeof(int));
    checkMemoryAlocation(numberList);

    for(int i = 0; i < listSize; i++){
        numberList[i] = rand() % maxValue + 1;
    }

    writeNumberListToBinaryFile(numberList, listSize);
    writeNumberListToTextFile(numberList, listSize);

    free(numberList);
}


void checkMemoryAlocation(void *pointer){
    if(pointer == NULL) exit(0);
}


char *createFileName(char *fileExtension, int listSize){

    char digitsBuffer[11] = {'\0'};
    sprintf(digitsBuffer, "%d", listSize);

    char *fileName = calloc(strlen(FILE_PREFIX) + strlen(digitsBuffer) + strlen(fileExtension) + 1, sizeof(char));
    
    strcat(fileName, FILE_PREFIX);
    strcat(fileName, digitsBuffer);
    strcat(fileName, fileExtension);
    
    return(fileName);
}


void writeNumberListToBinaryFile(int *numberList, int listSize){
    
    char *fileName = createFileName(BINARY_FILE_EXTENSION, listSize);

    FILE *filePointer = fopen(fileName, "wb");
    checkMemoryAlocation(filePointer);
    
    fwrite(numberList, sizeof(int), listSize, filePointer);
    
    fclose(filePointer);
    free(fileName);
}


void writeNumberListToTextFile(int *numberList, int listSize){
    
    char *fileName = createFileName(TEXT_FILE_EXTENSION, listSize);

    FILE *filePointer = fopen(fileName, "w");
    checkMemoryAlocation(filePointer);

    for(int i = 0; i < listSize; i++){
        fprintf(filePointer, "%d\n", numberList[i]);
    }

    fclose(filePointer);
    free(fileName);
}
