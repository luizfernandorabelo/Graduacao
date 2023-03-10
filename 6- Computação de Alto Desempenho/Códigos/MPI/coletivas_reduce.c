#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>

#define TAM_VETOR 16

int main(int argc, char *argv[]) {

    int meu_rank, total_processos, receptor = 0;
    int soma_local = 0, soma_final = 0, qtd_elementos_por_processo;
    int *subvetor_parcial;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processos);

    // Criação do vetor local:
    srand(meu_rank);
    qtd_elementos_por_processo = TAM_VETOR / total_processos;
    subvetor_parcial = malloc(qtd_elementos_por_processo * sizeof(int));
    for (int i = 0; i < qtd_elementos_por_processo; i++)
        subvetor_parcial[i] = rand() % 10;

    // Soma local:
    for (int i = 0; i < qtd_elementos_por_processo; i++)
        soma_local += subvetor_parcial[i];
    printf("Rank %d, Soma Local: %d\n", meu_rank, soma_local);

    // Soma global por redução:
    MPI_Reduce(&soma_local, &soma_final, 1, MPI_INT, MPI_SUM, receptor, MPI_COMM_WORLD);

    if (meu_rank == receptor)
        printf("Rank %d (receptor), Soma final: %d\n", meu_rank, soma_final);

    free(subvetor_parcial);

    MPI_Finalize();

    return 0;
}
