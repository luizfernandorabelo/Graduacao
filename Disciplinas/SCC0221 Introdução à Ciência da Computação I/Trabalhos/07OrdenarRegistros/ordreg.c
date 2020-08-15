#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define bool char
#define True 1
#define False 0

//Estrutura para Dados do Registro:
typedef struct{
    char *textdata;
    int numericdata;
} data;

int readOption();
/*Função que lê a opção de ordenação digitada pelo usuário e a retorna.*/

data **loadInfo(int *elementsnumber);
/*Função que lê e armazena dinamicamente o registro até o fim do arquivo de entrada. Tem como 
parâmetro o endereço do número de elementos (elementsnumber). Retorna o  endereço  em  que  o 
registro foi armazenado*/

void unloadInfo(data **myregister, int elementsnumber);
/*Função que libera os bytes reservados para o armazenamento do registro. Tem como parâmetros 
o endereço do registro (myregister) e seu número de elementos (elementsnumber).*/

data **addElement(data **r, int *index, bool *end);
/*Função auxiliar da loadInfo. Operando sobre uma linha, separa sua parte alfabética  de  sua 
parte numérica e atribui um novo elemento ao registro. Tem  como  parâmetros  o  endereço  do 
registo (r), o endereço de seu índice (incex) e a variável booleana de parada (end).  Retorna 
o endereço do registro realocado com o novo elemento.*/

char *readLine(bool *end);
/*Função que lê uma linha inteira da entrada padrão  stdine  a  armazena  dinamicamente.  Tem 
como parâmetro a variável de parada end, a qual será  atribuído True caso o  fim  do  arquivo
tenha sido encontrado. Retorna o endereço em que a linha foi armazenada.*/

int lastValidChar(char *line);
/*Função que procura pelo último caractere alfabético em uma  linha.  Tem  como  parâmetro  o
endereço da linha (line). Retorna a posiçã em que o último alfabético foi encontrado.*/

int myAtoi(char *line, int pos);
/*Função que converte uma parte de uma cadeia de caracteres para um número inteiro. Tem  como 
parâmetros o endereço da cadeia de caracteres (line) e a posição inicial do  primeiro  número 
(pos). Retorna o número convertido.*/

int *mySort(data **myregister, int elementsnumber, int option);
/*Função que cria um array de inteiros com  as  posições  do  registro  ordenadas.  Tem  como 
parâmetros o endereço do registro  (myregister), o seu número de elementos (elementsnumber) e
a opção de ordenação (option). Retorna o endereço do array já ordenado.*/

void printRegister(data **myregister, int elementsnumber, int *indexarray);
/*Função que imprime na tela os elementos do registro na forma "textdata\tnumericdata". Tem 
como parâmetros o endereço do registro (myregister), o número de eleentos (elementsnumber)
e o array de índices do registro ordenado (indexarray).*/

int main(int argc, char *argv[]){    

    int elementsnumber = 0;

    int option = readOption();

    data **myregister = loadInfo(&elementsnumber);    

    int *indexarray = mySort(myregister, elementsnumber, option);

    printRegister(myregister, elementsnumber, indexarray);

    unloadInfo(myregister, elementsnumber);

    free(indexarray);   

    return 0;
}

int readOption(){
    int o;
    scanf("%d", &o);
    return o;
}

data **loadInfo(int *elementsnumber){
    data **r = NULL; 
    bool end = False;
    int index = 0;
    while(end != True){
        r = addElement(r, &index, &end);
    }
    *elementsnumber = index; //número de elementos = valor final do índice
    return r;
}

data **addElement(data **r, int *index, bool *end){
    char *textdata = NULL;
    int numericdata, lastc;
    //Armazenamento da linha:
    char *line = readLine(end);
    //Definição do último caractere válido:
    lastc = lastValidChar(line);
    //Estabelecimento da parte textual:
    textdata = (char *) realloc(textdata, (lastc+1) * sizeof(char));
    memcpy(textdata, line, lastc);
    textdata[lastc] = '\0';
    //Estabelecimento da parte inteira:
    numericdata = myAtoi(line, lastc+1);
    //Armazenamento das partes textual e inteira no registro:  
    r = (data **) realloc(r, (*index+1) * sizeof(data *));
    r[*index] = (data *) malloc(1 * sizeof(data));
    r[*index]->textdata = textdata;
    r[*index]->numericdata = numericdata;
    //Incremento do índice para próximo armazenamento:
    *index = *index + 1;
    //Liberação da linha:
    free(line);
    //Retorno do endereço do registro:  
    return r;
}

char *readLine(bool *end){
    int counter = 0, character = 0;
    char *string = NULL;
    //Limpeza do Buffer para evitar caracteres indesejados:
    while(counter == 0 && character < 30) { character = fgetc(stdin); }
    //Armazenamento da Linha:
    do{
        string = (char *) realloc(string, (counter+1) * sizeof(char));
        string[counter++] = (char) character; 
        character = fgetc(stdin);
    }while(character != '\n' && character != EOF);
    //Terminador de String:
    string = (char *) realloc(string, (counter+1) * sizeof(char));
    string[counter] = '\0';
    //Verificação de Fim de Arquivo:
    *end = character == EOF ? True : False;
    //Retorno do endereço da Linha:
    return string;
}

int lastValidChar(char *line){
    int i, last = 0;
    //Verificação do último caractere válido:
    for(i = 0; i < strlen(line); i++){
        if(isdigit(line[i])){ 
            last = i - 1; 
            break; 
        }
    }
    //Desconsideração de '-' pertencente ao número (caso exista)
    last = line[last] == '-' ? (last - 1) : last; 
    return last;
}

int myAtoi(char *line, int pos){
    int number = 0;
    bool negative = False;
    //Desconsideração de espaço no último caractere:
    line[strlen(line)-1] = line[strlen(line)-1] == ' ' ? '\0' : line[strlen(line)-1];
    //Consideração de número negativo (caso houver '-'):
    if(line[pos] == '-'){
        negative = True;
        pos += 1;
    }
    //Conversão de caracter para inteiro
    for(int i = pos; i < strlen(line) && isdigit(line[i]); i++){
            number += (line[i] - 48) * (int) pow(10, strlen(line) - (i + 1));
    }
    //Operação caso o número for negativo:
    number = negative ? -number : number;
    //Retrono do número convertido:
    return number;
}

int *mySort(data **myregister, int elementsnumber, int option){
    int *indexarray, aux;
    //Alocação Dinâmica do Array com elementsnumber posições:
    indexarray = (int *) malloc(elementsnumber * sizeof(int));
    //Inicialização do array:
    for(int i = 0; i < elementsnumber; i ++){
        indexarray[i] = i;
    }
    //Ordenação do Array:
    switch(option){
        case 1: //opção de ordenação alfabética:
            for(int i = 0; i < elementsnumber - 1; i++){
                for(int j = i + 1; j < elementsnumber; j++){
                    if(strcmp(myregister[indexarray[j]]->textdata, myregister[indexarray[i]]->textdata) < 0){
                        //Se o texto da posição j do array vier antes da i, são trocadas as posições i e j :
                        aux = indexarray[i];
                        indexarray[i] = indexarray[j];
                        indexarray[j] = aux;
                    }
                }
            }
            break;
        case 2: //opção de ordenação numérica:
            for(int i = 0; i < elementsnumber - 1; i++){
                for(int j = i + 1; j < elementsnumber; j++){
                    if(myregister[indexarray[j]]->numericdata < myregister[indexarray[i]]->numericdata){
                        //Se o número da posição j do array vier antes do i, são trocadas as posições i e j:
                        aux = indexarray[i];
                        indexarray[i] = indexarray[j];
                        indexarray[j] = aux;
                    }
                }
            }
            break;
        default:
            break;
    }
    //Retorno do Arry Ordenado:
    return indexarray;
}

void printRegister(data **myregister, int elementsnumber, int *indexarray){
    for(int i = 0; i < elementsnumber; i++){
        printf("%d\t", myregister[indexarray[i]]->numericdata);
        printf("%s\n", myregister[indexarray[i]]->textdata);
    }
    return;
}

void unloadInfo(data **myregister, int elementsnumber){
    for(int i = 0; i < elementsnumber; i++){
        free(myregister[i]->textdata);
        free(myregister[i]);
    }
    free(myregister);
    return;
}
