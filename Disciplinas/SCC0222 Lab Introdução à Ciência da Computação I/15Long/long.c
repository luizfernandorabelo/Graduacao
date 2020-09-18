#include <stdio.h> 

int main(int argc, char *argv[]){

    long int number; //variável que guardará o número original
    unsigned char *address; //variável que guardará o endereço do número original

    scanf("%ld", &number); 

    //Determinação e Impressão dos bytes de number:
    address = (unsigned char*) &number; 

    for(int i = 0; i < 8; i++){ 
        printf("%x\n", address[i]); 
    }

    return 0;
}








