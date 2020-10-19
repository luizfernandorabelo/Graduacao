#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SAO_CARLENSE 1
#define NAO_SAO_CARLENSE 0

//"Criação" do tipo booleano
#define bool char
#define True 1
#define False 0

typedef struct{
    char *name;
    char *hometown;
}PEOPLE_DATA;

int readInteger();
/*Função que lê um número inteiro da entrada padrão e o retorna.*/

char *readField(void);
/*Função que lê um campo (nome da pessoa ou cidade natal) do tipo
char * e o retorna.*/

PEOPLE_DATA **loadPeopleData(int namesNumber);
/*Função que, carrega os dados passados pela entrada padrão para 
uma estrutura PEOPLE_DATA**, alocada dinamicamente. Tem como parametro
o total de pessoas a serem inseridas.*/

void sortPeopleDataByName(PEOPLE_DATA **peopleData, int peopleNumber);
/*Função que ordena os dados de uma estrutura PEOPLE_DATA** com base
no nome das pessoas. Tem como parâmetros um ponteiro duplo para as 
estruturas e o número de pessoas nela presentes.*/

void printPeopleName(PEOPLE_DATA **peopleData, int peopleNumber);
/*Função que imprime os dados de todas as pessoas de uma estrutura
PEOPLE_DATA**. Tem como parâmetros o ponteiro para a estrutura e
o número de pessoas nela presentes.*/

int isPersonSaoCarlense(PEOPLE_DATA **peopleData, int peopleNumber, char *person);
/*Função que verifica se uma pessoa é de São Carlos ou não. Tem como
parâmetros o ponteiro para a estrutura de pessoas, o número de pessoas
e a pessoa analisada. Retorna verdadeiro ou falso.*/

void unloadPeopleData(PEOPLE_DATA **peopleData, int peopleNumber);
/*Função que libera a memória alocada para uma estrutura PEOPLE_DATA**.
Tem como parâmetros a estrutura e o número total de pessoas.*/


int main(int argc, char *argv[]){

    //Leitura do Total de Pessoas a serem armaenadas:
    int peopleNumber = readInteger();

    //Carregamento dos Dados das Pessoas para a memória:
    PEOPLE_DATA **notablePeople = loadPeopleData(peopleNumber);
    
    //Ordenação das Pessoas por seus nomes:
    sortPeopleDataByName(notablePeople, peopleNumber);

    //Impressão dos Dados das Pessoas:
    printPeopleName(notablePeople, peopleNumber);

    //Leitura do Número de buscas a serem realizadas:
    int searchesNumber = readInteger();

    //Buscas:
    for(int i = 0; i < searchesNumber; i++){
        char *personSearched = readField();
        printf("%d\n", isPersonSaoCarlense(notablePeople, peopleNumber, personSearched));
        free(personSearched);
    }

    //Liberação de Memória Alocada:
    unloadPeopleData(notablePeople, peopleNumber);
    
    return 0;
}

int readInteger(){
    int integer = 0;
    scanf("%d", &integer);
    return integer;
}

char *readField(void){
    char *string = NULL, character = 0;
    int charCounter = 0;
    while(character < 33) character = fgetc(stdin);
    do{
        string = (char *) realloc(string, (charCounter+2));
        string[charCounter++] = character;
        character = fgetc(stdin);
    }while(character != '.' && character != '\n' && character != '\r' && character != EOF);
    string[charCounter] = '\0';
    return string;
}

PEOPLE_DATA **loadPeopleData(int namesNumber){
    PEOPLE_DATA **peopleData = malloc(namesNumber * sizeof(PEOPLE_DATA *));
    for(int i = 0; i < namesNumber; i++){
        peopleData[i] = malloc(sizeof(PEOPLE_DATA));
        peopleData[i]->name = readField();
        peopleData[i]->hometown = readField();
    }
    return peopleData;
}

void sortPeopleDataByName(PEOPLE_DATA **peopleData, int peopleNumber){
    PEOPLE_DATA *swapPivot; bool isSorted;
    for(int min = 0, max = peopleNumber-1; max > min; min++, max--){
        isSorted = True;
        for(int i = min; i < (max-1); i++){
            if(strcasecmp(peopleData[i]->name, peopleData[i+1]->name) > 0){
                swapPivot = peopleData[i];
                peopleData[i] = peopleData[i+1];
                peopleData[i+1] = swapPivot;
                isSorted = False;
            }
        }
        for(int i = max; i > min; i--){
            if(strcasecmp(peopleData[i]->name, peopleData[i-1]->name) < 0){
                swapPivot = peopleData[i];
                peopleData[i] = peopleData[i-1];
                peopleData[i-1] = swapPivot;
                isSorted = False;
            }
        }
        if(isSorted) return;
    }
}

void printPeopleName(PEOPLE_DATA **peopleData, int peopleNumber){
    for(int i = 0; i < peopleNumber; i++){
        printf("%s.\n", peopleData[i]->name);
    }
}

int binarySearchByName(PEOPLE_DATA **peopleData, int peopleNumber, char *person){
    int min = 0, max = peopleNumber-1, half = 0;
    while(min <= max){
        half = (min + max) / 2;
        if(strcasecmp(person, peopleData[half]->name) == 0) return half;
        else if(strcasecmp(person, peopleData[half]->name) < 0) max = half-1;
        else if(strcasecmp(person, peopleData[half]->name) > 0) min = half + 1;
    }
    return -1;
}

int isPersonSaoCarlense(PEOPLE_DATA **peopleData, int peopleNumber, char *person){
    int pos = binarySearchByName(peopleData, peopleNumber, person);
    if(pos != -1){
        if(strcasecmp(peopleData[pos]->hometown, "Sao Carlos") == 0) return SAO_CARLENSE;
        return NAO_SAO_CARLENSE;
    }
    return -1;
}

void unloadPeopleData(PEOPLE_DATA **peopleData, int peopleNumber){
    for(int i = 0; i < peopleNumber; i++){
        free(peopleData[i]->name);
        free(peopleData[i]->hometown);
        free(peopleData[i]);
    }
    free(peopleData);
}