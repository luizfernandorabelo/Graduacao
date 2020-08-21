#include <stdio.h>

int main(int argc, char **argv){
	
	int a, b;

	scanf("%d %d", &a, &b);

	printf("%d", a&b);
	printf("\n%d", a|b);
	printf("\n%d", a^b);
	printf("\n%d", ~a);
	printf("\n%d", ~b);
	printf("\n%d", a>>2);
	printf("\n%d", b<<2);

	return(0);
}
