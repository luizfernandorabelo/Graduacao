// ŷ = a * x̂ + ŷ 

#include <stdio.h>
#include <stdlib.h>

#define TAM 16

void saxpy(int *x, int *y, int a) {
    for (int i = 0; i < TAM; i++)
        y[i] = a * x[i] + y[i];
}

int main(void) {

    // Preenchimento de x "identidade" (para facilitar teste):
    int *x = malloc(TAM * sizeof(int));
    for (int i = 0; i < TAM; i++)
        x[i] = i + 1;

    // Preenchimento de y com zeros (para facilitar teste):
    int *y = calloc(TAM, sizeof(int));

    saxpy(x, y, 2);

    // Impressão do resultado:
    for (int i = 0; i < TAM; i++)
        printf("%d ", y[i]);
    printf("\n");

    free(x);
    free(y);

    return 0;
}
