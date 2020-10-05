#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILE_OPEN_FAILURE 1

typedef enum { False, True } bool;

//Estrutura Global com Dados do Labirinto:
typedef struct{
    int rows;
    int columns;
    int XStart;
    int YStart;
    int Xknot;
    int Yknot;
    char **map;
}MAZE_DATA;


FILE *mazeFileOpen(char *fileName, char *mode);
/*Função que abre o arquivo com as informações do labirinto. Se ele não existir, aborta o programa. Tem
como parâmetros o nome do arquivo a ser aberto e o modo de abertura. Retorna o ponteiro para o arquivo.*/

MAZE_DATA *loadMazeData(FILE *filePointer);
/*Função que carrega os dados lidos do arquivo em uma estrutura alocada dinamicamente. Tem como parâmetro
um ponteiro para o arquivo. Retorna o endereço da estrutura alocada.*/

int countCharInMaze(MAZE_DATA *maze, char character);
/*Função que conta quantas vezes determinado caractere aparece no labirinto. Tem como parâmetros um ponteiro
para os dados do labirinto e o caractere a ser contado. Retorna o número de ocorrências.*/

void run(MAZE_DATA **maze, int Xpos, int Ypos, bool *endOfMaze);
/*Função que encontra, recursivamente, a saída do labirinto, traçando o caminho da personagem. Tem como 
parâmetros um ponteiro duplo para os dados do labirinto, as cordenadas x e y para onde a personagem irá e
um ponteiro para uma flag de fim do labirinto.*/

void printFinalMessage(MAZE_DATA *maze, int peopleNumber, int totalPaths, int takenPaths);
/*Função que imprime a mensagem final do programa com dados sobre o percurso. */

void printMazeMap(MAZE_DATA *maze);
/*Função que imprime o labirinto.*/

void freeMazeData(MAZE_DATA *maze);
/*Função que libera todos os bytes alocados dinamicamente para os dados do labirinto.*/


int main(int argc, char *argv[]){

    //Leitura do Nome do Arquivo com os Dados do Labirinto:
    char fileName[20];
    scanf("%s", fileName);

    //Abertura do Arquivo e Carregamento de Dados na Estrutura do Labirinto:
    FILE *filePointer = mazeFileOpen(fileName, "r");    
    MAZE_DATA *maze = loadMazeData(filePointer);

    //Determinação do Número de Pessoas e Caminhos Possíveis Iniciais:
    int peopleNumber = countCharInMaze(maze, '#');
    int totalPaths = countCharInMaze(maze, '.'); 

    //Processo de Saída do Labirinto:
    bool endOfMaze = False;
    run(&maze, maze->XStart, maze->YStart, &endOfMaze);

    //Determinação de quantos caminhos foram tomados:
    int takenPaths = countCharInMaze(maze, '*');

    //Impressão da Mensagem Final:
    printFinalMessage(maze, peopleNumber, totalPaths, takenPaths);

    //Fechamento do Arquivo e Liberação de Memória Alocada:
    fclose(filePointer);
    freeMazeData(maze);

    return 0;
}


FILE *mazeFileOpen(char *fileName, char *mode){

    FILE *filePointer = NULL;
    filePointer = fopen(fileName, mode);

    if(filePointer == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(FILE_OPEN_FAILURE);
    }

    return filePointer;
}

MAZE_DATA *loadMazeData(FILE *filePointer){
    
    MAZE_DATA *maze = calloc(1, sizeof(MAZE_DATA));
    
    fscanf(filePointer, "%d ", &maze->rows);
    fscanf(filePointer, "%d ", &maze->columns);
    fscanf(filePointer, "%d ", &maze->XStart);
    fscanf(filePointer, "%d ", &maze->YStart);
    
    maze->map = (char **) calloc(maze->rows, sizeof(char *));
    for(int i = 0; i < maze->rows; i++){
        maze->map[i] = (char *) calloc(maze->columns, sizeof(char));
        for(int j = 0; j < maze->columns; j++){
            fscanf(filePointer, "%c ", &maze->map[i][j]);
        }
    }
    
    return maze;
}

int countCharInMaze(MAZE_DATA *maze, char character){
    
    int charCounter = 0;
    
    for(int i = 0; i < maze->rows; i++){
        for(int j = 0; j < maze->columns; j++){
            charCounter = (maze->map[i][j] == character) ? charCounter + 1 : charCounter;
        }
    }
    
    return charCounter;
}

void run(MAZE_DATA **maze, int Xpos, int Ypos, bool *endOfMaze){

    int rows = (*maze)->rows, columns = (*maze)->columns;
    
    if(*endOfMaze == False) (*maze)->map[Xpos][Ypos] = '*';
    else return;

    if(Xpos == 0 || Xpos == rows-1 || Ypos == 0 || Ypos == columns-1){
        *endOfMaze = True;
        return;
    }
    
    if((*maze)->map[Xpos-1][Ypos] == '.') run(maze, Xpos-1, Ypos, endOfMaze);
    if((*maze)->map[Xpos][Ypos+1] == '.') run(maze, Xpos, Ypos+1, endOfMaze);
    if((*maze)->map[Xpos+1][Ypos] == '.') run(maze, Xpos+1, Ypos, endOfMaze);
    if((*maze)->map[Xpos][Ypos-1] == '.') run(maze, Xpos, Ypos-1, endOfMaze);
}

void printFinalMessage(MAZE_DATA *maze, int peopleNumber, int totalPaths, int takenPaths){

    printMazeMap(maze);

    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", peopleNumber);
    printf("----Numero total de caminhos validos:   %d\n", totalPaths);
    printf("----Numero total de caminhos visitados: %d\n", takenPaths);
    printf("----Exploracao total do labirinto: %.1lf%%\n", floor((double) takenPaths / totalPaths * 100));
}

void printMazeMap(MAZE_DATA *maze){
    for(int i = 0; i < maze->rows; i++){
        for(int j = 0; j < maze->columns; j++){
            printf("%c", maze->map[i][j]);
        }
        printf("\n");
    }
}

void freeMazeData(MAZE_DATA *maze){
    for(int i = 0; i < maze->rows; i++){
        free(maze->map[i]);
    }
    free(maze->map);
    free(maze);
}