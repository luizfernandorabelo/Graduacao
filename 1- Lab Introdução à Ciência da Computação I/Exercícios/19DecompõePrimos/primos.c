#include <stdio.h> 

int main(int argc, char *argv[]){

    //Leitura e Armazenamento do Número a ser decomposto:
    int number; 
    scanf("%d", &number); //o número digitado na entrada é armazenado no endereço de number
    
    for(int divider = 2; divider <= number; divider++){ 
        int multiplicity = 0;
        while(number % divider == 0){
            multiplicity += 1;
            number /= divider;
        }
        if(multiplicity != 0) printf("%d %d\n", divider, multiplicity);   
    }

    return 0;
}
