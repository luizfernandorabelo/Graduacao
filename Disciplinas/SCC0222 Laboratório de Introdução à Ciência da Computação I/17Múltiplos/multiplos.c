#include <stdio.h> 

int main(int argc, char *argv[]){

    //Declaração de Variáveis na Stack:
    int n1, n2, n3; 
    int i = 0;
    int j = 0; 
    
    //Leitura e Armazenamento das Entradas:
    scanf("%d %d %d", &n1, &n2, &n3); 

    //Cálculo e Impressão dos n1 primeiros números de n2 e n3:
    while((i + j) < n1){ 
        if(i * n2 < j * n3){ 
            printf("%d\n", i * n2);
            i++; 
        }
        else if(j * n3 < i * n2){ 
            printf("%d\n", j * n3); 
            j++; 
        }
        else{
            printf("%d\n", i * n2); 
            i++; 
            j++; 
            n1 ++; 
        }
    }   

    return 0;
}
