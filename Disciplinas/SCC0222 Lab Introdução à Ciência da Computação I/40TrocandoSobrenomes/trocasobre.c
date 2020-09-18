#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool char
#define True 1
#define False 0

char **getFullNames(int *namesnumber);
/*Função que armazena todos os nomes digitados na entrada padrão retornados pela função readLine 
até que o fim de leitura (end) seja verdadeiro. Aloca todos os nomes dinamicamente e  retorna  o 
endereço de alocação. Tem como parâmetro o endereço do número de nomes lidos  (namesnumber), que 
será atibuído dentro da função.*/

char *readLine(bool *end);
/*Função auxiliar da getFullNames. Lê uma linha inteira da entrada padrão até encontrar os chars 
'\n' ou '$'. Aloca a linha dinamicamente eretorna seu endereço de alocação. Tem como parâmetro o 
endereço do fim de leitura (end), ao qual será atribuído "True" se '$' for encontrado.*/

char **getLastNames(char **names, int namesnumber);
/*Função que armazena dinamicamente os últimos  sobrenomes  de  cada  nome  digitado.  Tem  como 
parâmetros o endereço dos nomes armazenados (names) e o número  total  de  nomes  (namesnumber). 
Retorna o endereço em que os sobrenomes foram alocados.*/

char **makeMess(char **names, char **lastnames, int namesnumber);
/*Função que atualiza os nomes, trocando os sobrenomes de ordem. Tem como parâmetros o endereço 
dos nomes armazenados (names), o endereço dos sobrenomes armazenados (lastnames) e o total de 
nomes (namesnumber). Retorna o endereço dos nomes com os sobrenomes já trocados.*/ 

void printNames(char **names, int namesnumber);
/*Função que imprime os nomes finais, linha a linha, na  saída  padrão. Tem  como  parâmetros  o 
endereço dos nomes armazenados(names) e o número de nomes armazenados (namesnumber).*/

void freeNames(char **names, char **lastnames, int namesnumber);
/*Função que libera os nomes e os sobrenomes armazenados dinamicamente. Tem  como  parâmetros  o 
endereço dos nomes armazenados (names), o endereço dos sobrenomes armazenados  (lastnames)  e  o 
número de nomes armazenados (namesnumber) */

int main(int argc, char *argv[]){

    int namesnumber = 0;

    char **names = getFullNames(&namesnumber);

    char **lastnames = getLastNames(names, namesnumber);

    names = makeMess(names, lastnames, namesnumber);    

    printNames(names, namesnumber);

    freeNames(names, lastnames, namesnumber);

    return 0;
}

char **getFullNames(int *namesnumber){
    //Declaração e Iicialização de Variáveis:
    bool end = False;
    int counter = 0;
    char **names = NULL, *line = NULL;
    //Armazenamento dos Nomes:
    while(end != True){ //enquanto end for falso (não for encontrado '$')
        //Leitura de Nova Linha e Armazenamento da Mesma em names:
        line = readLine(&end); 
        names = (char **) realloc(names, (counter+1) * sizeof(char *)); //
        names[counter++] = line;
    }
    //Determinação do Total de Nomes Armazenados:
    *namesnumber = counter; 
    //Retorno do Endereço de Alocação dos Nomes Armazenados
    return names;
}

char *readLine(bool *end){
    //Declaração e Inicialização de Variáveis:
    char *line = NULL;
    int character = 0, counter = 0;
    character = fgetc(stdin);
    //Limpeza do Buffer do Teclado:
    while(counter == 0 && character < 30) { character = fgetc(stdin); }
    //Leitura e Armazenamento da linha:
    do{
        line = (char *) realloc(line, (counter+1) * sizeof(char));
        line[counter++] = (char) character;
        character = fgetc(stdin);
    }while(character != '\n' && character != '$');
    //Adição do Terminador de String '\0':
    line = (char *) realloc(line, (counter+1) * sizeof(char));
    line[counter] = '\0';
    //Verificação de Chegada ao Fim de Leitura:
    *end = (char) character == '$' ? True : False;
    //Retorno do Endereço de Alocação da Linha:
    return line;
}

char **getLastNames(char **names, int namesnumber){
    //Declaração e Inicialização de Variável:
    int lastbegin = 0; //variável que armazenará a posição do começo do sobrenome
    char **lastnames = NULL; //variável que armazenará os sobrenomes
    lastnames = (char **) malloc(namesnumber * sizeof(char *));
    //Obtenção dos Sobrenomes:
    for(int i = 0; i < namesnumber; i++){ 
        for(int j = 0; j < strlen(names[i]); j++){ 
            lastbegin = names[i][j] == ' ' ? j : lastbegin;
        }
        //Armazenamento do Último Sobrenome (caractere por caractere):
        lastnames[i] = (char *) calloc(strlen(names[i]) - lastbegin + 1, sizeof(char));
        for(int j = lastbegin; j < strlen(names[i]); j++){ 
            lastnames[i][j-lastbegin] = names[i][j];
        }
    }
    //Retorno do Endereço de Alocação dos Sobrenomes:    
    return lastnames;
}

char **makeMess(char **names, char **lastnames, int namesnumber){
    //Declaração e Inicialização de Variáveis:
    int lenname = 0; //armazenará o tamanho do nome da posição i
    int lenlast = 0; //armazenará o tamanho do sobrenome da posição i
    int pos = 0; //auxiliar para índices
    char *aux = NULL; //auxiliar para substituições de sobrenomes
    //Reordenação dos Sobrenomes:
    for(int i = 0; i < namesnumber / 2; i++){ 
        //Reatribuição dos Endereços dos Sobrenomes com o auxílio de aux:
        aux = lastnames[i];
        lastnames[i] = lastnames[namesnumber-(1+i)];
        lastnames[namesnumber-(1+i)] = aux;
        aux = NULL;
    }
    //Troca dos Sobrenomes:
    for(int i = 0; i < namesnumber; i++){ 
        //Determinação do Comprimento dos Nomes e Sobrenomes na posição i:
        lenname = strlen(names[i]);
        lenlast = strlen(lastnames[i]);
        //Determinação da Última Ocorrência de Espaço:
        for(int j = 0; j < lenname; j++){
            pos = names[i][j] == ' ' ? j : pos;
        }
        //Determinação do Novo Tamanho do Sobrenome:
        lenname = lenname - (lenname - pos) + lenlast + 1;
        //Realocação e Troca do Sobrenome, Byte a Byte:
        names[i] = (char *) realloc(names[i], lenname);
        for(int j = pos; j < (lenname); j++){
            names[i][j] = lastnames[i][j-pos];
        }
        names[i][lenname-1] = '\0'; 
    }
    //Retorno do Endereço de Realocação dos Nomes:
    return names;
}
void printNames(char **names, int namesnumber){
    for(int i = 0; i < namesnumber; i++){
        printf("%s \n", names[i]);
    }
    return;
}

void freeNames(char **names, char **lastnames, int namesnumber){
    for(int i = 0; i < namesnumber; i++){
        free(names[i]);
        free(lastnames[i]);
    }    
    free(names);
    free(lastnames);
    return;
}