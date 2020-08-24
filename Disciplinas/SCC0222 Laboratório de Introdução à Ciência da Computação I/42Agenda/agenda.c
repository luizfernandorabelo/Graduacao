#include <stdio.h>
#include <stdlib.h>

//Estrutura para Dados da Agenda:
typedef struct{
    char *activity;
    int day;
    int month;
    int year;
    int hour;
    int minutes;
    int seconds;
}schedule;

int readNumber();
char *readLine();
schedule *loadSchedule(int lenght);
void printData(schedule *mySchedule, int lenght);
void unloadSchedule(schedule *mySchedule, int lenght);

int main(int argc, char *argv[]){
    
    //Leitura e Armazenamento do Número de Atividades:
    printf("Digite o número de atividades: ");
    int lenght = readNumber(); 
    
    //Carregamento das Atividades na Agenda:
    schedule *mySchedule = loadSchedule(lenght);
    
    //Impressão de Dados na Tela:
    printf("\n\n-> Atividades Agendadas:\n\n");
    printData(mySchedule, lenght);
    
    //Liberação de Memória Alocada:
    unloadSchedule(mySchedule, lenght);
    
    return 0;
}

int readNumber(){
    int number = 0;
    scanf("%d", &number);
    return number;
}

char *readLine(){
    char *line = NULL, character = 0;
    int counter = 0; 
    while(character < 30) character = fgetc(stdin);
    do{
        line = (char *) realloc(line, (counter+2) * sizeof(char));
        line[counter++] = character;
        character = fgetc(stdin);
    }while(character != '\n' && character != '\r' && character != EOF);
    line[counter] = '\0';
    return line;
}

schedule *loadSchedule(int lenght){
    schedule *mySchedule = malloc(lenght * sizeof(schedule));
    for(int i = 0; i < lenght; i++){
        printf("\n-> Atividade %d\n", i+1);
        printf("Dia: ");
        mySchedule[i].day = readNumber();
        printf("Mês: ");
        mySchedule[i].month = readNumber();
        printf("Ano: ");
        mySchedule[i].year = readNumber();
        printf("Hora: ");
        mySchedule[i].hour = readNumber();
        printf("Minuto: ");
        mySchedule[i].minutes = readNumber();
        printf("Segundo: ");
        mySchedule[i].seconds = readNumber();
        printf("Descrição: ");
        mySchedule[i].activity = readLine();
    }
    return mySchedule;
}

void unloadSchedule(schedule *mySchedule, int lenght){
    for(int i = 0; i < lenght; i++){
        free(mySchedule[i].activity);
    }
    free(mySchedule);
}

void printData(schedule *mySchedule, int lenght){
    for(int i = 0; i < lenght; i++){
        printf("%.2d/%.2d/%.2d", mySchedule[i].day, mySchedule[i].month, mySchedule[i].year);
        printf(" - %.2d:%.2d:%.2d\n", mySchedule[i].hour, mySchedule[i].minutes, mySchedule[i].seconds);
        printf("%s\n\n", mySchedule[i].activity);
    }
    return;
}