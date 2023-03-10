#include <stdio.h>
#include <omp.h>

#define TOTAL_ITERACOES 1000000000
#define TOTAL_THREADS 4

int main(void)
{
    double x, pi = 0, passo, tempo, soma = 0;

    passo = 1.0 / TOTAL_ITERACOES;

    omp_set_num_threads(TOTAL_THREADS);

    // Medida do tempo paralelo com reduction:
    tempo = omp_get_wtime();
    #pragma omp parallel for reduction(+ : soma) private(x)
    for (int i = 0; i < TOTAL_ITERACOES; i++)
    {
        x = (i + .5) * passo;
        soma += 4 / (1 + x * x);  // integral de 0 a 1 de 4 / (1 + x ^ 2)
    }
    pi = passo * soma;
    tempo = omp_get_wtime() - tempo;

    printf("Pi = %.8lf\n", pi);
    printf("Tempo = %.5lf\n", tempo);

    return 0;
}
