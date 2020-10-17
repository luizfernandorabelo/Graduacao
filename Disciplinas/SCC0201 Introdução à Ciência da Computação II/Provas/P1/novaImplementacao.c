#include <stdio.h>

void verificaPrimo(int x, int y, int *primo){
    if(y <= 1 || *primo == 0) return; 
    if(x % y == 0) *primo = 0; 
    verificaPrimo(x, y-1, primo);
}

void funcao(int x, int y, int *primo){
    if(x < 2) *primo = 0; // 0, 1 e números negativos não são considerados primos
    else if(x == 2) *primo = 1; // 2 é o único par primo
    else verificaPrimo(x, y, primo); 
}

int main(int argc, char *argv[]){

    int n; // n = total de números a serem lidos
    scanf("%d", &n);
 
    for(int i = 0, x = 0; i < n; i++){
        scanf("%d", &x);
        int p = 1; // armazena se p é primo (1 -> verdadeiro ou 2 -> falso) 
        funcao(x, x-1, &p); 
        if(p == 1) printf("%d Primo\n", x); 
        else printf("%d Nao primo\n", x);
    } 

    return 0;
}
