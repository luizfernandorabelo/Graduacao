/* >>>>>>>>>>>>> CIFRA DE CÉSAR <<<<<<<<<<<<<< *
 * Autor: Luiz Fernando Rabelo - ICMC USP 2020 *
 * Descrição: Programa que faz a  criptografia *
 * e  descriptografia  simples  de  mensagens. *
 * Para isso, lê na entrada padrão  um inteiro *
 * correspondente  à  opção  desejada     (1 = *   
 * criptografar / 2 = descriptografar),  outro *
 * inteiro correspondente à chave do  processo *
 * e a mensagem propriamente dita. Escreve  na *  
 * saída padrão a nova cadeia de caracteres.   */

//Inclusão de Bibliotecas
#include <stdio.h> //usada nesse programa para funções de entrada e saída padrão
#include <stdlib.h> //usada nesse progrma para funçõees de alocação dinâmica de memória
#include <string.h> //usada nesse programa para funções de tratamento de strings

//Cabeçalho de Função Complementar
char rewrite(char c, int min, int max, int o, int k);
/*função  que  altera  um caratere.  Tem  como  parâmetros o caractere a ser  alterado, o seu  mínimo e  máximo
(valores correspondentes à 'a' e 'z' ou 'A' e 'Z' na tabela ASCII), a opção o (criptografar ou descriptografar)
e a chave k da mensagem */

//Função Principal do Programa
int main(int argc, char **argv){
	
	//Declaração de Variáveis:
	int option, key, i; //option armazenará a opção, key a chave e i será índice em laços de repetição
	char *message; //message apontará para as células de memória em que a mensagem ficará armazenada

	//Alocação Dinâmica de Memória:
	message = (char *) calloc(101, sizeof(char));

	//Entrada de dados pelo Usuário:
	scanf("%d", &option); //número da opção é lido e passado para o endereço de option
	scanf("%d", &key); //valor da chave é lido e armazenado no endereço de key
	scanf(" %[^\n]", message); //leitura e armazenamento da mensagem


	//Análise de cada caractere da mensagem:
	for(i = 0; i < strlen(message); i++){ //laço de repetição em que i vai de 0 ao tamanho da mensagem
		if(message[i] > 64 && message[i] < 91){ //Se o caractere for uma letra maiúscula		
			message[i] = rewrite(message[i], 64, 91, option, key); //message[i] é reescrito no limite de 'A'(65) a 'Z'(90)				
		}
		else if(message[i] > 96 && message[i] < 123){ //Se o caracrere for uma letra minúscula
			message[i] = rewrite(message[i], 96, 123, option, key); //message[i] é reescrito no limite de 'a'(97) a 'z'(122)
		}	
	}
	
	//Impressão da Mensagem:
	printf("%s", message);

	free(message);

	//Retorno Exit Success:
	return(0); 
}

//Função Complementar:
char rewrite(char c, int min, int max, int o, int k){
	if(o == 1){ //Se a opção for 1(encriptar)
		c += k; //caractere é acrescido da chave
	}
	else{ //Se a opção for 2(desencriptar)
		c -= k; //caractere é decrescido da chave
	} 
	if(c >= max){ //Se o caractere estrapolar o limite do alfabeto (para mais)
		c -= 26; //c é decrescido em 26 unidades
	}
	else if(c <= min){ //Se o caractere estrapolar o limite do alfabeto (para menos)
		c += 26; //c é acrescido em 26 unidades
	}

	//Retorno da Função:
	return(c);
}





