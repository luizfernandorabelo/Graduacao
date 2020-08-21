#include <stdio.h>

int main(int argc, char **argv){
	
	double n1 = 0, n2 = 0, answer = 0;
	char option = 0;
	
	scanf("%lf", &n1);
	scanf(" %c", &option);
	scanf("%lf", &n2);
	
	switch(option){
		case '+': 
			answer = n1 + n2;
			break;
		case '-':
			answer = n1 - n2;
			break;
		case '*':
			answer = n1 * n2;
			break;
		case '/': 
			answer = n1 / n2;
			break;
		case '%': 
			answer = n1 / n2 * 100;
			break;
		default:
			answer = 0;
			break;
	}
	
	printf("%lf", answer);

	return(0);
}
