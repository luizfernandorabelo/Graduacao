#include <stdio.h>

int main(int argc, char **argv){
	
	long long int a1, r, n, an, sn;

	scanf("%lld %lld %lld", &a1, &r, &n);

	an = a1 + (n - 1) * r;
	sn = (a1 + an) * n / 2;

	printf("%lld\n%lld", an, sn);

	return(0);
}
