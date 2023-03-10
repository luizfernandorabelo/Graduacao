#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 16

int main(void)
{
    int numero_thread, total_threads, soma = 0;

    // Olá Mundo da região sequencial (da Trhead Mestre):
    numero_thread = omp_get_thread_num();
    total_threads = omp_get_num_threads();
    printf("Hello World da Thread Mestre (%d), com %d threads\n\n", numero_thread, total_threads);

    // Olá Mundo da região paralela, com realização de soma:
    #pragma omp parallel \
            private(numero_thread, total_threads) \
            num_threads(MAX_THREADS) \
            reduction(+: soma)
    {
        numero_thread = omp_get_thread_num();
        total_threads = omp_get_num_threads();
        soma = numero_thread;
        printf("Hello World da Thread %d, com %d threads\n", numero_thread, total_threads);
    }

    // Saiu da região paralela => redução da operação de soma em log(n)
    printf("\nSoma computada: %d\n\n", soma);

    // Tchau Mundo da região sequencial (da Thread Mestre):
    numero_thread = omp_get_thread_num();
    total_threads = omp_get_num_threads();
    printf("Bye World da Thread Mestre (%d), com %d threads\n", numero_thread, total_threads);

    return 0;
}
