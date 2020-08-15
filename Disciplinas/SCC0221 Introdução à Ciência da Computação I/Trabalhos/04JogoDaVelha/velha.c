#include <stdio.h> 
#include <stdlib.h>

#define bool char
#define TRUE 1
#define FALSE 0

char **allocateMatrix(); 
/*Função que aloca na heap os bytes necessários para armazenamento da matriz do jogo. Retorna
o endereço da matriz alocada*/

void freeMatrix(char **matrix);
/*Função que libera os bytes alocados na heap necessários para armazenamento da matriz do jogo. 
Tem como parâmetro o endereço da matriz alocada.*/

void initializePositions(char **matrix);
/*Função que inicializa as posições de cada índice da matriz com os caracteres correspndentes
de 0 a 9. Imprime na tela a matriz, pela função printMatrix, e a mensagem "Jogo da Velha". Tem 
como parâmetro o endereço da matriz.*/

void printMatrix(char **m); 
/*Função que imprime na tela a matriz já formatada com as posições disponíveis (1-9) e as
casas já escolhidas (X e Y). Tem como parâmetro o endereço da matriz*/

void playTheGame(char **m); 
/*Função que tem em seu escopo. Tem como parâmetro o endereço da matriz*/

char setPlayer(int c);
/*Função que estabelece qual jogador fará a jogada. Escreve na tela a mensagem "Escolha um número
para jogar, jogador <letra>". Tem como parâmetro c, que é o contador de jogadas*/

char readPosition(char **m);
/*Função que lê na entrada padrão a posição que o jogador quer jogar até que o jogador digite uma
posição válida. Se o mesmo digitar uma posição inválida, imprime na tela "Jogada inválida. Escolha
outra casa!"" Retorna o caractere correspondente à posição lida*/

void writePosition(char pl, char po, char **m);
/*Função que escreve na matriz m do jogo, na posição po(1-9), o caractere correspondente ao jogador
pl (X ou O)*/

bool checkWinners(char **m);
/*Função que verifica se, na configuração da matriz m, o jogo acabou. Caso isso aconteça, retorna 1, 
caso não retorna 0. Se existir um vencedor, imprime na tela "Fim do jogo!" O jogador <letra> venceu.
Se o jogo empatar, imprime na tela "Deu velha!"*/


int main(int argc, char *argv[]){

    char **matrix = allocateMatrix(); 
    
    initializePositions(matrix); 
    
    playTheGame(matrix); 
    
    freeMatrix(matrix);

    return 0;
}


char **allocateMatrix(){
    char **matrix = (char **) calloc (3, sizeof(char*));
    for(int i = 0; i < 3; i++){
        matrix[i] = (char *) calloc (3, sizeof(char));
    }
    return(matrix);
}

void freeMatrix(char **matrix){
    for(int i = 0; i < 3; i++){
        free(matrix[i]); //liberação ponteiros simples
    }
    free(matrix); //liberação ponteiro duplo
    return;
}

void initializePositions(char **matrix){
    for(int i = 0, counter = 1; i < 3; i ++){
        for(int j = 0; j < 3; j++){
            matrix[i][j] = counter + '0';
            counter++;
        }
    }
    printMatrix(matrix);
    printf("Jogo da velha!\n");    
    return;
}

void printMatrix(char **matrix){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%c   |", matrix[i][j]);
        }
        printf("\n----+----+-----\n");
    }
    return;
}

void playTheGame(char **m){
    bool gameover = FALSE;
    short int counter = 0;
    char player, position;

    while(gameover == FALSE){
        player = setPlayer(counter);
        position = readPosition(m);
        writePosition(player, position, m);
        printMatrix(m);
        gameover =  checkWinners(m);   
        counter++;
    }
}

char setPlayer(int c){
    char player;
    printf("Escolha um número para jogar, jogador ");
    if(c % 2 == 0){ 
        printf("X!\n"); 
        player = 'X';
    }
    else{
        printf("O!\n"); 
        player = 'O';
    }
    return player; 
}

char readPosition(char **matrix){
    bool availablePositions[9];
    short int counter = 0;
    //Determinação do Número das Posições disponíveis
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++, counter++){
            availablePositions[counter] = (matrix[i][j] == 'X' || matrix[i][j] == 'O') ? FALSE : TRUE;
        }
    }        
    //Leitura da Posição com Tratamento para Possíveis Entradas Inválidas:
    short int intPos = 0;
    /*A posição é lida como um número inteiro para evitar caracteres como '\n' e '\r'*/
    while(TRUE){
        scanf("%hd", &intPos);
        if(intPos > 0 && intPos < 10 && availablePositions[(intPos - 1)] == TRUE){
            break;
        }
        else{
            printf("Jogada inválida! Escolha outra casa.\n");
        }
    }
    char charPos = intPos + '0'; //charPos = intPos + 48
    return charPos; 
}

void writePosition(char player, char position, char **matrix){
    short int counter = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++, counter++){
            if(counter == ((int) position - 48)){ 
                matrix[i][j] = player; 
            }            
        }
    }
    return; 
}

bool checkWinners(char **m){
    char winner = 0;
    short int i, j = 0; 
    short int counter = 0;
    //Verificação da Existência de Vencedor(linhas e colunas):
    while(j < 3 && winner == 0){
        if(m[j][0] == m[j][1] && m[j][1] == m[j][2]){
            winner = m[j][0];
        }
        if(m[0][j] == m[1][j] && m[1][j] == m[2][j]){
            winner = m[0][j];
        }
        j++;
    }
    //Verificação da Existência de Vencedor(diagonais)
    if((m[0][0] == m[1][1] && m[1][1] == m[2][2]) || (m[2][0] == m[1][1] && m[1][1] == m[0][2])){
        winner = m[1][1];
    }
    //Verificação se Deu Velha:
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(m[i][j] == 'X' || m[i][j] == 'O'){
                counter++;
            }
        }
    }
    //Impressão de Mensagem na Tela se o Jogo tiver terminado:
    if(winner != 0){
        printf("Fim do jogo! O jogador %c venceu!\n", winner);
        return TRUE;
    }
    if(counter == 9){
        printf("Deu velha!\n");
        return TRUE;
    }
    return FALSE;  
}