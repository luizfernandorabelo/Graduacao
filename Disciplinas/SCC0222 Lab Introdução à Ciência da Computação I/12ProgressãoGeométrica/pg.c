#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
	
	float a1, q, n, an, sn;

	scanf("%f %f %f", &a1, &q, &n);

	an = a1 * pow(q, (n-1));
	sn = (an * q - a1) / (q - 1);

	printf("%.2f\n%.2f", an, sn);

	return(0);
}
