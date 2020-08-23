#include <stdio.h>

int main(){

    double n1, n2, n3, n4, discard, average;

    scanf("%lf", &n1);
    discard = n1;
    
    scanf("%lf", &n2);
    if(n2 <= discard){
        discard = n2;
    }
    
    scanf("%lf", &n3);
    if(n3 <= discard){
        discard = n3;
    }
    
    scanf("%lf", &n4);
    if(n4 <= discard){
        discard = n4;
    }

    average = (n1 + n2 + n3 + n4 - discard) / 3;

    printf("%.4lf", average);

    return 0;
}
