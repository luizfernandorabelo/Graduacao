#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>

#define TAM_BUFFER 16

int main(int argc, char *argv[]) {

    int meu_rank, total_processos, qtd_valores_transmitidos, receptor = 0;    
    int *buffer_envio, *buffer_recebimento;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processos);

    buffer_envio = malloc(TAM_BUFFER * sizeof(int));
    buffer_recebimento = malloc(TAM_BUFFER * sizeof(int));

    qtd_valores_transmitidos = TAM_BUFFER / total_processos;
    for (int i = 0; i < qtd_valores_transmitidos; i++)
        buffer_envio[i] = meu_rank * qtd_valores_transmitidos + i;
    
    /*
        Para esse código, foi considerado que o processo em que
        as informações são aglomeradas é o 0, mas se todos os
        processos precisassem das informações, poderia ser feito
        um "gather broadcast" com MPI_Allgather.
    
    */

    MPI_Gather(buffer_envio, qtd_valores_transmitidos, MPI_INT,
               buffer_recebimento, qtd_valores_transmitidos, MPI_INT,
               receptor, MPI_COMM_WORLD);
    
    if (meu_rank == receptor) {
        for (int i = 0; i < TAM_BUFFER; i++)
            printf("Rank %d recebeu v[%d] = %d\n", meu_rank, i, buffer_recebimento[i]);
    }

    free(buffer_envio);
    free(buffer_recebimento);

    MPI_Finalize();

    return 0;
}
