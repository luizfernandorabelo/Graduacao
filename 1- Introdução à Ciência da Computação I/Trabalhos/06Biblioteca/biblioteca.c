#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define LIMIT 10 //limite de livros que o usuário pode acumular nos empréstimos

//Estrutura para Informações dos Livros:
typedef struct{
    char *bookname; 
    int availabletime; 
}booksinfo;

void firstOperation(booksinfo **cdata, int csize, booksinfo **pdata, int *bnumber);
/*Função que fará as operações necessárias para que o usuário alugue um  novo  livro. 
Tem como parâmetros o endereco da coleção (cdata), o tamanho da  coleção  (csize),  o
endereço do pacote do usuário (pdata) e o endereço do número  de  livros  emprestados
(bnumber)*/

void secondOperation(booksinfo **pdata, int bnumber);
/*Função que fará as operações necessárias  para  que  o  usuário  veja  seus  livros 
atualmente alugados,  bem  como  o  prazo  para  a  devolução  dos  mesmos. Tem  como 
parâmetros o endereço do pacote (pdata) e o número de livros  emprestados  (bnumber)*/

void thirdOperation(booksinfo **pdata, int *bnumber);
/*Função que fará as operações necessárias  para  que  o  usuário  devolva  um  livro 
alugado.  Tem  como parâmetros o endereço do pacote (pdata) e o endereço do número de 
livros emprestados (bnumber).*/

int readNumber(); 
/*Função que lê um número inteiro da entrada padrão e o retorna.*/

char *readString(); 
/*Função que lê uma cadeia de caracteres da  entrada  padrão,  alocando  seu  tamanho 
dinamicamente. Retorna o endereço em que a cadeia de caracteres foi armazenada.*/

booksinfo **loadLibraryCollection(int csize);
/*Função que carrega a coleção de livros da biblioteca, lendo e armazenando o nome  e 
o número de dias que cada livro pode ser armazenado. Tem  como  parâmetro  o  tamanho
da coleção (csize). Retona o endereço em que as informações foram armazenadas.*/

booksinfo **loadUserPack(int psize);
/*Função que inicializa o pacote de livros emprestados ao usuário. Retorna o endereço
em que o pacote foi alocado.*/

void unloadLibraryCollection(booksinfo **cdata, int csize);
/*Função que libera os bytes reservados para a coleção de livros da  biblioteca.  Tem
como parâmetros o endereço da coleção (cdata) e seu tamanho (csize).*/

int searchBook(char *bookname, booksinfo **source, int sizeofsource);
/*Função que procura o nome de  determinado  livro  em  uma  fonte. Se  o  livro  for 
encontrado, retorna o número de seu índice na fonte. Se não for  encontrado,  retorna 
-1. Tem como parâmetros o endereço do nome do livro (bookname), o endereço  da  fonte
(source) e o tamanho da fonte (sizeofsource).*/

void borrow(booksinfo *cdata, booksinfo *pdata);
/*Função que adiciona um livro ao pacote do usuário. Tem como parâmetros a origem  da
informação do livro na coleção (cdata) e o destino do livro (pdata).*/

void userInteraction(booksinfo **cdata, int csize);
/*Função para interação com o usuário. Lê na  entrada  padrão o  número  da  operação 
requisitada pelo usuário e direciona  o  programa  para  as  funções  firstOperation,
secondOperation ou  thirdOperation  até que o usuário  requisiste a  opção 4 (sair do 
programa). Tem como parâmetros  o  endereço  da  coleção  da  biblioteca  (cdata) e o
tamanho da coleção (csize)*/


int main(int argc, char *argv[]){

    int collectionSize = readNumber(); 

    booksinfo **collectionData = loadLibraryCollection(collectionSize);

    userInteraction(collectionData, collectionSize);

    unloadLibraryCollection(collectionData, collectionSize);    

    printf("Programa finalizado\n");    
    return 0;
}


int readNumber(){
    int number;
    scanf("%d", &number);
    return number;
}

char *readString(){
    int character;
    int counter = 0;
    char *string = NULL;
    do{
        character = fgetc(stdin);
        //"Limpeza" do buffer para tratar caracteres indesejados quando counter for igual a zero
        while(counter == 0 && ((char) character == '\n' || (char) character == '\r')){
            character = fgetc(stdin);
        }
        string = (char *) realloc (string, (counter+1) * sizeof(char));
        string[counter++] = (char) character;
    }while(character != '\n' && character != '\r' && character != EOF);
    string[--counter] = '\0'; //terminador de string
    return string;
}

booksinfo **loadLibraryCollection(int csize){
    booksinfo **collectionData;
    collectionData = (booksinfo **) malloc(csize * sizeof(booksinfo *));
    for(int i = 0; i < csize; i++){
        collectionData[i] = (booksinfo *) malloc(sizeof(booksinfo));
        collectionData[i]->bookname = readString();
        collectionData[i]->availabletime = readNumber();
    }
    return collectionData;
}

booksinfo **loadUserPack(int psize){
    booksinfo **userpackdata;
    userpackdata = (booksinfo **) malloc(psize * sizeof(booksinfo *));
    for(int i = 0; i < psize; i++){
        userpackdata[i] = (booksinfo *) malloc(sizeof(booksinfo));
        userpackdata[i]->bookname = NULL;
        userpackdata[i]->availabletime = 0;
    }
    return userpackdata;
}

void unloadLibraryCollection(booksinfo **cdata, int csize){
    for(int i = 0; i < csize; i++){
            free(cdata[i]->bookname);
            free(cdata[i]);
    }
    free(cdata);
    return;
}

void userInteraction(booksinfo **cdata, int csize){
    booksinfo **userpackdata = loadUserPack(LIMIT);
    int borrowednumber = 0;
    int option = readNumber();
    
    while(option != 4){
        switch(option){
            case 1: 
                firstOperation(cdata, csize, userpackdata, &borrowednumber);
                break;
            case 2:
                secondOperation(userpackdata, borrowednumber);
                break;
            case 3:
                thirdOperation(userpackdata, &borrowednumber);
                break;
            default:
                break;
        }
        option = readNumber();
    }

    //Liberação de Memória Alocada:
    for(int i = 0; i < LIMIT; i++){
        free(userpackdata[i]);
    }
    free(userpackdata);
    return;
}

void firstOperation(booksinfo **cdata, int csize, booksinfo **pdata, int *bnumber){
    printf("Digite o livro que voce procura:\n");
    char *bookname = readString();
    int position = searchBook(bookname, cdata, csize);
    if(position == -1){ //se o livro não existir
        printf("Livro nao encontrado na biblioteca\n");
    }
    else{ //senão, o livro existe
        if(*bnumber == LIMIT){ //se o usuário já tiver atingido 10 empréstimos
            printf("Voce ja tem 10 livros alugados\n");
        }
        else{ //senão, o usuário ainda não atingiu 10 empréstimos
            int bookfound = searchBook(bookname, pdata, LIMIT);    
            if(bookfound != -1){ //se o livro já estiver alugado
                printf("Livro ja alugado\n");
            }
            else{ //senão, o livro ainda não está alugado
                borrow(cdata[position], pdata[*bnumber]);
                *bnumber = *bnumber + 1;
            }
        }
    }
    
    free(bookname);
    return;
}

void secondOperation(booksinfo **pdata, int bnumber){
    if(bnumber == 0){ //se o número de livros emprestados for zero
        printf("Voce nao tem livros alugados\n");
    }
    else{ //senão, o número de livros emprestados é diferente de zero
        printf("Voce tem %d livro(s) alugado(s)\n", bnumber);
        for(int i = 0; i < LIMIT; i++){
            if(pdata[i]->bookname != NULL){
                printf("Livro nome: %s\n", pdata[i]->bookname);
                printf("Devolve-lo daqui %d dias\n", pdata[i]->availabletime);
            }
        }
    }
    return;
    }


void thirdOperation(booksinfo **pdata, int *bnumber){
    printf("Digite o livro que deseja devolver: \n");
    char *bookname = readString();
    int position = searchBook(bookname, pdata, LIMIT);
    if(position == -1){ //se o livro não foi encontrado no pacote
        printf("Voce nao possui esse livro\n");
    }
    else{ //senão, o livro foi encontrado no pacote
        for(int i = position; i < (LIMIT-1); i++){
            pdata[i]->bookname = pdata[i+1]->bookname;
            if(i < 9) { pdata[i+1]->bookname = NULL; } //"reatribuição" para o nome do livro
            pdata[i]->availabletime = pdata[i+1]->availabletime;
            if (i < 9) { pdata[i+1]->availabletime = 0; } //"reatribuição" para o tempo do livro
        }
        *bnumber = *bnumber - 1;
        printf("Livro %s foi devolvido com sucesso\n", bookname);
    }
    free(bookname);
    return;
}

int searchBook(char *bookname, booksinfo **source, int sizeofsource){
    for(int i = 0; i < sizeofsource; i++){
        if(source[i]->bookname != NULL){
            int lenght = (strlen(source[i]->bookname) > strlen(bookname)) ? strlen(source[i]->bookname):strlen(bookname);
            if(memcmp(source[i]->bookname, bookname, lenght)== 0){
                return i;
            }
        }
    }
    return -1;
}

void borrow(booksinfo *cdata, booksinfo *pdata){
    pdata->bookname = cdata->bookname;
    pdata->availabletime = cdata->availabletime; 
    printf("%s alugado com sucesso\n", pdata->bookname);
    return;
}
