#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int **criar_matriz(int dimensao)
{
    int **matriz = malloc(dimensao * sizeof(int *));

    for (int i = 0; i < dimensao; i++)
        matriz[i] = calloc(dimensao, sizeof(int));

    return matriz;
}


void preencher_aleatoriamente(int **matriz, int dimensao)
{
    for (int i = 0; i < dimensao; i++)
        for (int j = 0; j < dimensao; j++)
            matriz[i][j] = rand() % 10;
}


int main(int argc, char **argv)
{
    int dimensao, seed;
    int **a, **b, **c;
    double tempo;

    if (argc != 3)
    {
        printf("Uso: ./multiplicacao_matriz_paralelo <dimensao_da_matriz> <semente_para_rand>\n");
        exit(0); 
    }

    dimensao = atoi(argv[1]);
    seed = atoi(argv[2]);

    srand(seed);

    a = criar_matriz(dimensao);
    b = criar_matriz(dimensao);
    c = criar_matriz(dimensao);

    preencher_aleatoriamente(a, dimensao);
    preencher_aleatoriamente(b, dimensao);

    // Medida do tempo paralelo:
    tempo = omp_get_wtime();
    #pragma omp parallel shared(a, b, c, dimensao)
    {
        #pragma omp for collapse(2)  // 2 primeiros for's paralelizados
        for (int i = 0; i < dimensao; i++)
            for (int j = 0; j < dimensao; j++)
                for (int k = 0; k < dimensao; k++)
                    c[i][j] += a[i][k] * b[k][j];
    }
    tempo = omp_get_wtime() - tempo;

    printf("Tempo = %.5f\n", tempo);

    return 0;
}
