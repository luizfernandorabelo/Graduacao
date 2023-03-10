#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main(int argc, char **argv)
{
    int limite_superior, soma;
    double tempo;

    if (argc != 2)
    {
        printf("Uso: ./numeros_perfeitos_paralelo <limite_superior>\n");
        exit(0); 
    }

    limite_superior = atoi(argv[1]);

    // Medida do tempo paralelo:
    tempo = omp_get_wtime();
    #pragma omp parallel for private (soma) num_threads(4)
    for (int atual = 1; atual <= limite_superior; atual++)
    {
        soma = 0;
        for (int divisor = 1; divisor < atual; divisor++)
            if (atual % divisor == 0)
                soma += divisor;
        if (atual == soma)
            printf("%d é perfeito\n", atual);
    }
    tempo = omp_get_wtime() - tempo;

    printf("\nTempo = %.5f\n", tempo);

    return 0;
}

