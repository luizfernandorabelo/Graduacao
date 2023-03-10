#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>

#define TAM_BUFFER 16

int main(int argc, char *argv[]) {

    int meu_rank, total_processos, qtd_valores_transmitidos, origem = 0;
    int *buffer_envio, *buffer_recebimento;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processos);

    buffer_envio = malloc(TAM_BUFFER * sizeof(int));
    buffer_recebimento = malloc(TAM_BUFFER * sizeof(int));

    if (meu_rank == origem) {
        for (int i = 0; i < TAM_BUFFER; i++)
            buffer_envio[i] = i;
    }

    qtd_valores_transmitidos = TAM_BUFFER / total_processos;

    MPI_Scatter(buffer_envio, qtd_valores_transmitidos, MPI_INT,
                buffer_recebimento, qtd_valores_transmitidos, MPI_INT,
                origem, MPI_COMM_WORLD);
    
    for (int i = 0; i < qtd_valores_transmitidos; i++)
        printf("Rank %d recebeu %d\n", meu_rank, buffer_recebimento[i]);

    free(buffer_envio);
    free(buffer_recebimento);

    MPI_Finalize();

    return 0;
}
