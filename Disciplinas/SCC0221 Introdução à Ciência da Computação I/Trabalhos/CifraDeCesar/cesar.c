#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>

#define ENCRYPT 1
#define DECRYPT 2

char changeCharacter(char character, int option, int key);
/*Função que criptografa um caratere, alterando seu valor. Tem como parâmetros o caractere a ser alterado, 
a opção de alteração (criptografar[1] ou descriptografar[2]) e a chave de alteração da mensagem. */

int main(int argc, char **argv){
	
	//Declaração e Inicialização de Variáveis:
	int option = 0, key = 0; 
	char *message = calloc(101, sizeof(char));

	//Leitura e Armazenamento de dados da Entrada Padrão:
	scanf("%d", &option); 
	scanf("%d", &key); 
	scanf(" %[^\n]", message);

	//Troca de cada caractere alfabético da mensagem:
	for(int i = 0; i < strlen(message); i++){ 
		if((message[i] >= 'A' && message[i] <= 'Z') || (message[i] >= 'a' && message[i] <= 'z')){
			message[i] = changeCharacter(message[i], option, key);
		}
	}
	
	//Impressão da Mensagem Final:
	printf("%s\n", message);

	//Liberação de Memória Alocada:
	free(message);

	//Retorno Exit Success:
	return(0); 
}

char changeCharacter(char character, int option, int key){
	if(option == DECRYPT) key *= -1;	
	
	//Verificação se o caractere permanecerá alfabético:
	if(tolower(character) + key > 'z'){ //se o caractere for estrapolar o limite do alfabeto (para mais)
		character -= 26; 
	}
	else if(tolower(character) + key < 'a'){ //se o caractere for estrapolar o limite do alfabeto (para menos)
		character += 26;
	}

	character += key;

	return(character);
}





