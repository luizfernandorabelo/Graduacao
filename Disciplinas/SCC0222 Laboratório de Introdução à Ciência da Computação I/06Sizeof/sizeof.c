#include <stdio.h>

int main(int argc, char **argv){

    printf("%lu", sizeof(char));
    printf("\n%lu", sizeof(unsigned int));
    printf("\n%lu", sizeof(short int));
    printf("\n%lu", sizeof(int));
    printf("\n%lu", sizeof(long int));
    printf("\n%lu", sizeof(unsigned long int));
    printf("\n%lu", sizeof(long long int));
    printf("\n%lu", sizeof(float));
    printf("\n%lu", sizeof(double));
    printf("\n%lu", sizeof(long double));

    return 0;

}
