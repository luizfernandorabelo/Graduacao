#include <stdio.h>
#include <omp.h>

#define TOTAL_ITERACOES 1000000000

int main(void)
{
    double x, pi, soma, passo, tempo;

    passo = 1.0 / TOTAL_ITERACOES;

    // Medida do tempo sequencial:
    tempo = omp_get_wtime();
    for (int i = 0; i < TOTAL_ITERACOES; i++)
    {
        x = (i + .5) * passo;
        soma += 4 / (1 + x * x);  // integral de 0 a 1 de 4 / (1 + x ^ 2)
    }
    tempo = omp_get_wtime() - tempo;

    pi = passo * soma;

    printf("Pi = %.8lf\n", pi);
    printf("Tempo = %.5lf\n", tempo);

    return 0;
}
