#include <stdio.h>

int funcao(int x){
    int primo = 1;
    int soma = 0;
    for(int y = x-1; y > 1; y--){
        if(x % y == 0){
            primo = 0;
        }
        for(int a = 0; a <= 10000; a++){
            if(a % y == 0)soma+= a;
        }
    }
    return primo;
}

int main(int argc, char *argv[]){
    
    int x, n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        int p = funcao(x); 
        if(p == 1) printf("%d Primo\n", x); 
        else printf("%d Nao primo\n", x);
    } 
    
    return 0;
}
