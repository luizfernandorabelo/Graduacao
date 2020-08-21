#include<stdio.h>
#include<string.h>

int main(){

    int ano;
    char resp[4];

    scanf("%i", &ano);

    if (ano % 4 != 0){
        strcpy(resp, "NAO");
    } 
    else if(ano % 100 == 0){
        if(ano % 400 != 0){
            strcpy(resp, "NAO");
        }
        else{
            strcpy(resp, "SIM");
        }
    }
    else{
        strcpy(resp, "SIM");
    }
    
    printf("%s\n", resp);

    return 0;
}
