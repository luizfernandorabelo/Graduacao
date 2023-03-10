#include <stdio.h>
#include <omp.h>

#define TOTAL_ITERACOES 1000000000
#define TOTAL_THREADS 4

int main(void)
{
    double pi = 0, passo, tempo;

    passo = 1.0 / TOTAL_ITERACOES;

    omp_set_num_threads(TOTAL_THREADS);

    // Medida do tempo paralelo com critical:
    tempo = omp_get_wtime();
    #pragma omp parallel
    {
        double x, soma = 0;
        int id = omp_get_thread_num();

        for (int i = id; i < TOTAL_ITERACOES; i += TOTAL_THREADS)
        {
            x = (i + .5) * passo;
            soma += 4 / (1 + x * x);  // integral de 0 a 1 de 4 / (1 + x ^ 2)
        }
        #pragma omp critical  // como é apenas 1 operação de incremento, poderia ser atomic
        pi += passo * soma;
    } 
    tempo = omp_get_wtime() - tempo;

    printf("Pi = %.8lf\n", pi);
    printf("Tempo = %.5lf\n", tempo);

    return 0;
}
