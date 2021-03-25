#include <stdio.h> 
#include <string.h>
#include <math.h> 

int main(int argc, char **argv){
	
	//Declaração de Variáveis:
	char binario[31]; 
	long long int decimal = 0; 
	
	//Leitura do "número" binário:
	scanf("%s", binario);
	
	//Preparação para conversão(eliminação de possíveis zeros à esquerda e posições vazias):
	int i; 
	while(binario[0] == '0'){
		for(i = 0; i < strlen(binario); i++){
			binario[i] = binario[i+1];
		}
		binario[i+1] = '\0'; //terminador de caractere
	}
	
	//Conversão para Forma Decimal:
	int j;
	decimal = 0;
	for(i = 0; i < strlen(binario); i++){  
		j = strlen(binario) - (1 + i); //Expoente = tamanho do binário - o índice i - 1
		switch(binario[i]){
			case '1': 
				decimal += pow(2, j); 
				break;
			default: 
				break; 
		}	
	}
	
	//Impressão do Número na Forma Decimal:
	printf("%lld\n", decimal);
	
	return(0);
}
