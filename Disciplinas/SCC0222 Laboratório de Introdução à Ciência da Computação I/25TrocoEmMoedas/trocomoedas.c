#include <stdio.h> 

void change(int t, int *r1, int *c50, int *c25, int *c10, int *c5, int *c1); 
/*Função que tem como parâmetros o valor total do troco em centavos e o endereço de cada variável 
que  armazenará  o  número  de  moedas correspondentes ao seu valor. Quando é chamada, escreve em
cada variável(através de seus endereços) o número de moedas equivalentes a cada valor.*/

int main(int argc, char *argv[]){

    //Declaração de Variáveis na Stack:
    int total, r1, c50, c25, c10, c5, c1; 

    //Leitura e Armazenamento do Total do Troco em Centavos:
    scanf("%d", &total);

    //Determinação do Troco:
    change(total, &r1, &c50, &c25, &c10, &c5, &c1); 

    //Impressão do Troco na Tela:
    printf("O valor consiste em %d moedas de 1 real\n", r1);
    printf("O valor consiste em %d moedas de 50 centavos\n", c50); 
    printf("O valor consiste em %d moedas de 25 centavos\n", c25);
    printf("O valor consiste em %d moedas de 10 centavos\n", c10); 
    printf("O valor consiste em %d moedas de 5 centavos\n", c5);
    printf("O valor consiste em %d moedas de 1 centavo\n", c1);
    
    return 0;
}

void change(int t, int *r1, int *c50, int *c25, int *c10, int *c5, int *c1){
    
    *r1 = t / 100;
    t = t % 100;
    *c50 = t / 50;
    t = t % 50;
    *c25 = t / 25;
    t = t  % 25;
    *c10 = t / 10;
    t = t % 10;
    *c5 = t / 5;
    t = t % 5;
    *c1 = t;
    
    return;
}