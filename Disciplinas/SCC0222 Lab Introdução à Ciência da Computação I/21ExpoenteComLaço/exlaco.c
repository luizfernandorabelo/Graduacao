#include <stdio.h> 

double myPow(double base, int exponent); 
/*Função que eleva a base ao expoente e retorna o resultado*/

int main(int argc, char **argv){

    //Declaração e Inicialização de Variáveis
    double base = 0, answer = 0; 
    int exponent = 0; 

    //Leitura da Base e do Expoente:
    scanf("%lf", &base); 
    scanf("%d", &exponent); 

    //Determinação de Parâmetros Para a Função e Resposta:
    if(exponent > 0){ 
        answer = myPow(base, exponent); 
    }
    else if(exponent < 0){ 
        answer = 1 / myPow(base, -exponent); 
    }
    else{ 
        answer = 1;
    }

    //Impressão da Resposta Calculada:
    printf("%.4lf\n", answer);

    return(0);
}

double myPow(double base, int exponent){ 

    double answer = 1;
    
    for(int i = 0; i < exponent; i++){ 
        answer *= base; 
    }

    return answer;
}