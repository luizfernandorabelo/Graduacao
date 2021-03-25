#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_FOUND -1  //macro para elementos não encontrados em arrays

#define MIN_VALID_CHAR 32 //mínimo caractere válido na leitura de strigs


typedef struct{
    char **studentNames;
    int numberOfStudents;
    int numberOfChairs;
}LINE;


//Função que lê e aloca dinamicamente o nome de um estudante
char *readStudentName(FILE *stream);

//Função que cria uma fileira de alunos lendo seus nomes na entrada padrão
LINE *createLine(int numberOfChairs, int numberOfStudents);

//Função que libera o espaço de memória alocado para o armazenamento de uma fileira
void freeLine(LINE *line);

//Função que Imprime os nomes dos alunos de uma fileira
void printLine(LINE *line);

//Função que calcula o valor positivo do resto da divisão de m por n
int getMod(int m, int n);

//Função que soma os valores ASCII dos caracteres de uma palavra e retorna o valor somado
int getCharactersSum(char *string);

//Função que retorna o valor da posição da cadeira mais próxima disponível
int getAvailableChairNumber(LINE *line, int charSum);

//Função que insere o nome de um estudante na fileira
void insertNewStudent(LINE *line, char *studentName);

//Função que encontra a posição de determinado estudante na fileira
int findStudentPos(LINE *line, char *studentName);

//Função que remove um estudante da fileira
void removeStudent(LINE *line, char *studentName);


int main(int argc, char *argv[]){

    //Leitura do Número de Cadeiras e de Alunos:
    int numberOfChairs, numberOfStudents;
    scanf("%d %d", &numberOfChairs, &numberOfStudents);

    //Criação da Fileira com Inserção de Alunos:
    LINE *line = createLine(numberOfChairs, numberOfStudents);

    //Impressão da Situação Atual da Fileira:
    printLine(line); printf("\n");

    //Leitura do Número de Remoções:
    int numberOfRemovals; scanf("%d", &numberOfRemovals);

    //Remoção dos Alunos da Fileira com base nos nomes passados:
    for(int i = 0; i < numberOfRemovals; i++){
        char *removedStudent = readStudentName(stdin);
        removeStudent(line, removedStudent);
        free(removedStudent);
    }

    //Leitura do Número de Buscas:
    int numberOfSearches; scanf("%d", &numberOfSearches);

    //Buscas das Posições com base nos nomes passados:
    for(int i = 0; i < numberOfSearches; i++){
        char *searchedStudent = readStudentName(stdin);
        int pos = findStudentPos(line, searchedStudent);
        if(pos == NOT_FOUND)
            printf("%s nao esta presente\n", searchedStudent);
        else
            printf("%s esta presente no lugar %d\n", searchedStudent, pos);
        free(searchedStudent);
    }

    //Liberação de Memória Alocada:
    freeLine(line);

    return(0);
}


char *readStudentName(FILE *stream){

    char *name = NULL, character = fgetc(stream);
    int charCounter = 0;

    while(character < MIN_VALID_CHAR && character != EOF) character = fgetc(stream);

    do{
        name = realloc(name, (charCounter + 2) * sizeof(char));
        name[charCounter++] = character;
        character = fgetc(stream);
    }while(character != '\n' && character != '\r' && character != EOF);

    name[charCounter] = '\0';

    return(name);
}


LINE *createLine(int numberOfChairs, int numberOfStudents){

    LINE *line = malloc(sizeof(LINE));
    
    line->numberOfStudents = 0;
    line->numberOfChairs = numberOfChairs;
    
    line->studentNames = malloc(numberOfChairs * sizeof(char *));

    for(int i = 0; i < numberOfChairs; i++)
        line->studentNames[i] = NULL;

    for(int i = 0; i < numberOfStudents; i++){
        char *newName = readStudentName(stdin);
        insertNewStudent(line, newName);
    }

    return(line);
}


void freeLine(LINE *line){

    for(int i = 0; i < line->numberOfChairs; i++){
        if(line->studentNames[i] != NULL)
            free(line->studentNames[i]);
    }
    
    free(line->studentNames); free(line);
}


void printLine(LINE *line){
    for(int i = 0; i < line->numberOfChairs; i++)
        printf("%d: %s\n", i, line->studentNames[i] != NULL ? line->studentNames[i] : "XXXX");
}


int getMod(int m, int n){

    int mod = m % n;

    return(mod >= 0 ? mod : mod + n);
}


int getCharactersSum(char *string){

    int charSum = 0;

    for(int i = 0; i < strlen(string); i++)
        charSum += (string[i]); 

    return(charSum);
}


int getAvailableChairNumber(LINE *line, int charSum){

    int pos = getMod(charSum, line->numberOfChairs);

    while(line->studentNames[pos] != NULL)
        pos = getMod(pos + 1, line->numberOfChairs);

    return(pos);
}


void insertNewStudent(LINE *line, char *studentName){

    int charSum = getCharactersSum(studentName);
    int pos = getAvailableChairNumber(line, charSum);

    line->studentNames[pos] = studentName;
}


int findStudentPos(LINE *line, char *studentName){

    int charSum = getCharactersSum(studentName);
    int pos = charSum % line->numberOfChairs;
    int breakPoint = getMod(pos - 1, line->numberOfChairs);

    while(pos != breakPoint){
        if(line->studentNames[pos] != NULL && strcmp(line->studentNames[pos], studentName) == 0)
            return(pos);
        pos = getMod(pos + 1, line->numberOfChairs);
    }

    return(NOT_FOUND);
}


void removeStudent(LINE *line, char *studentName){

    int studentPos = findStudentPos(line, studentName);

    if(studentPos != NOT_FOUND){
        free(line->studentNames[studentPos]);
        line->studentNames[studentPos] = NULL;
    }
}