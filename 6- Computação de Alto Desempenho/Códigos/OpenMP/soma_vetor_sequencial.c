#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int *criar_vetor_aleatorio(int tamanho, int semente)
{
    int *vetor = malloc(tamanho * sizeof(int));

    srand(semente);

    for (int i = 0; i < tamanho; i++)
        vetor[i] = rand() % 10;

    return vetor;
}


int main(int argc, char **argv)
{
    int tamanho_vetor, semente, *vetor, soma = 0;
    double tempo;

    if (argc != 3)
    {
        printf("Uso: ./soma_vetor_sequencial <tamanho_do_vetor> <semente_para_rand>\n");
        exit(0); 
    }

    tamanho_vetor = atoi(argv[1]);
    semente = atoi(argv[2]);

    vetor = criar_vetor_aleatorio(tamanho_vetor, semente);

    // Medida de tempo sequencial:
    tempo = omp_get_wtime();
    for (int i = 0; i < tamanho_vetor; i++)
        soma += vetor[i];
    tempo = omp_get_wtime() - tempo;
    
    printf("Soma = %d\n", soma);
    printf("Tempo = %.5f\n", tempo);

    free(vetor);
    
    return 0;
}
