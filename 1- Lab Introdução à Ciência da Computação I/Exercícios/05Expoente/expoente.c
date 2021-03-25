#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){

    double base, exponent, answer;

    scanf("%lf", &base);
    scanf("%lf", &exponent);

    answer = pow(base, exponent);

    printf("%.4lf\n", answer);

    return 0;
}
