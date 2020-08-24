#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *readName(void);
char *getLastName(char *name);

int main(int argc, char *argv[]){

    //Leitura e Armazenamento do Nome:
    char *name = readName();

    //Determinação do Último Sobrenome:
    char *last = getLastName(name);

    //Saída com o Nome na Forma Bibliográfica:
    printf("%s, %s", last, name);

    //Liberação de Memória Alocada:
    free(name);
    free(last);

    return 0;   
}

char *readName(){
    //Declaração e Inicialização de Variáveis:
    char *name = NULL;
    int counter = 0, character = 0;
    //Leitura do Nome:
    do{
        character = fgetc(stdin);
        name = (char *) realloc(name, (counter+1) * sizeof(char));
        name[counter++] = (char) character;
    }while(character != '\n' && character != '\r');
    //Adição do Terminador de Strings '\0':
    name[--counter] = '\0';
    //Eliminação de Possíveis Espaços Desnecessários Apos o Nome:
    while(name[counter] == '\0' && name[counter-1] == ' '){
        name = (char *) realloc(name, counter);
        name[counter-1] = '\0';
        counter -= 1;
    }
    //Retorno do Endereço em que o Nome foi Alocado:
    return name;
}

char *getLastName(char *name){
    //Declaração e Inicialização de Variáveis:
    char *last = NULL;
    int lenname = strlen(name);
    //Determinação do Sobrenome:
    for(int i = lenname - 1; i > 0; i--){ 
        if(name[i] == ' '){ 
            //Armazenamento do Último Sobrenome(que vai do espaço até o '\0')
            for(int j = ++i; j <= lenname; j++){ 
                //Realocação de Memória seguida de Atribuição do Nome, caractere a caractere
                last = (char *) realloc(last, (j-i+1) * sizeof(char));
                last[j-i] = toupper(name[j]);
            }
            //Novo Terminador de String para o Nome:
            name[--i] = '\0'; //isso desconsiderará o último sobrenome
            break;
        }
    }
    //Retorno do Endereço em que o Sobrenome foi Alocado:
    return last;
}