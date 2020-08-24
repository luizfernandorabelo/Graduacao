#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_LEN 30

#define ADD_MUSIC 1
#define PRINT_ALL 2
#define ARTIST_SEARCH 3
#define GENDER_SEARCH 4
#define EXIT 5

//Estrutura Global para as Músicas:
typedef struct{
    char *name;
    char *artist;
    char *gender;
}musics;

char *readLine(void);
int readNumber(void);
musics **createList(void);
musics **addNewMusic(musics **list, int *top);
void printAllMusics(musics **list, int top);
void printArtistMusics(musics **list, int top);
void printGenderMusics(musics **list, int top);
void freeMusicsData(musics **list);

int main(int argc, char *argv[]){

    //Declaração e Inicialização de Variáveis:
    musics **list = createList();
    int top = -1, option = 0;    
   
   //Direcionamento para o Menu de Funções:
    while(option != EXIT){
        switch(option){
            case ADD_MUSIC:
                list = addNewMusic(list, &top);
                break;
            case PRINT_ALL:
                printAllMusics(list, top);
                break;
            case ARTIST_SEARCH:
                printArtistMusics(list, top);
                break;
            case GENDER_SEARCH:
                printGenderMusics(list, top);
                break;
            default:
                break;
        }
        printf("\nDigite sua opção: ");
        option = readNumber();
    }

    //Liberação de Memória Alocada:
    freeMusicsData(list);

    return 0;
}

char *readLine(){
    int counter = 0, character = 0;
    char *line = NULL;
    while(counter == 0 && character < 30) { character = fgetc(stdin); }
    do{
        line = (char *) realloc(line, (counter + 1) * sizeof(char));
        line[counter++] = (char) character;
        character = fgetc(stdin);
    }while(character != '\n' && character != '\r' && character != EOF);
    line = (char *) realloc(line, (counter + 1) * sizeof(char));
    line[counter] = '\0';
    return line;
}

int readNumber(){
    int number = 0;
    scanf("%d", &number);
    return number;
}

musics **createList(){
    musics **list = malloc(LIST_LEN * sizeof(musics *));
    for(int i = 0; i < LIST_LEN; i++){
        list[i] = malloc(1 * sizeof(musics));
    }
    return list;
}

musics **addNewMusic(musics **list, int *top){
    if(*top < (LIST_LEN - 1)){
        printf("\nNome: ");
        list[*top+1]->name = readLine();
        printf("Artista: ");
        list[*top+1]->artist = readLine();
        printf("Gênero: ");
        list[*top+1]->gender = readLine();
        *top = *top + 1;   
    }
    return list;
}

void printAllMusics(musics **list, int top){
    if(top == -1){
        printf("\nLista vazia\n");
        return;
    }
    printf("\nMusicas na sua lista:\n");
    for(int i = top; i >= 0; i--){
        printf("\nNome: %s\n", list[i]->name);
        printf("Artista: %s\n", list[i]->artist);
        printf("Genero: %s\n", list[i]->gender);
    }
    return;
}

void printArtistMusics(musics **list, int top){
    if(top == -1){
        printf("\nLista vazia\n");
        return;
    }
    printf("Nome do artista: ");
    char *artistName = readLine();
    printf("\nMusicas do artista %s\n", artistName);
    for(int i = top; i >= 0; i--){
        if(strcmp(artistName, list[i]->artist) == 0){
            printf("\nNome: %s\n", list[i]->name);
            printf("Artista: %s\n", list[i]->artist);
            printf("Genero: %s\n", list[i]->gender);
        }
    }
    free(artistName);
    return;
}

void printGenderMusics(musics **list, int top){
    if(top == -1){
        printf("\nLista vazia\n");
        return;
    }
    printf("Nome do gênero: ");
    char *genderName = readLine();
    printf("\nMusicas do genero %s\n", genderName);
    for(int i = top; i >= 0; i--){
        if(strcmp(genderName, list[i]->gender) == 0){
            printf("\nNome: %s\n", list[i]->name);
            printf("Artista: %s\n", list[i]->artist);
            printf("Genero: %s\n", list[i]->gender);
        }
    }
    free(genderName);
    return;
}

void freeMusicsData(musics **list){
    for(int i = 0; i < LIST_LEN; i++){
        free(list[i]);
    }
    free(list);
}
