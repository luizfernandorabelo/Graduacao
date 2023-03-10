#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TOTAL_THREADS 4


int *criar_vetor_aleatorio(int tamanho, int semente)
{
    int *vetor = malloc(tamanho * sizeof(int));

    srand(semente);

    for (int i = 0; i < tamanho; i++)
        vetor[i] = rand() % 10;

    return vetor;
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: ./encontra_maior_paralelo_lock <tamanho_do_vetor> <semente_para_rand>\n");
        exit(-1);
    }

    int tamanho_vetor = atoi(argv[1]);
    int semente = atoi(argv[2]);

    int *vetor = criar_vetor_aleatorio(tamanho_vetor, semente);

    omp_lock_t meu_lock;
    omp_init_lock(&meu_lock);

    int maior = -1, local_maior = -1;

    // Medida do tempo paralelo com lock:
    double tempo = omp_get_wtime();
    #pragma omp parallel num_threads(TOTAL_THREADS) shared(maior) firstprivate(local_maior)
    {
        #pragma omp for
        for (int i = 0; i < tamanho_vetor; i++)
            if (vetor[i] > local_maior) local_maior = vetor[i];
        omp_set_lock(&meu_lock);
        if (local_maior > maior) maior = local_maior;
        omp_unset_lock(&meu_lock);
    }
    tempo = omp_get_wtime() - tempo;

    printf("Maior: %d\n", maior);
    printf("Tempo: %.5lf\n", tempo);

    omp_destroy_lock(&meu_lock);

    free(vetor);

    return 0;
}
