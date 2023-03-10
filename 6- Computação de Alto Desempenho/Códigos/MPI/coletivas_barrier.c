#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>

int main(int argc, char *argv[]) {

    int meu_rank, total_processos;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processos);

    /*
        Se o processo 1 não executar a barrier, os
        demais ficaram em deadlock esperando por ele.
        Portanto, todos devem executar a primitiva.
    */

    // if (meu_rank != 1)
        MPI_Barrier(MPI_COMM_WORLD);
    
    printf("Rank %d de %d processos\n", meu_rank, total_processos);

    MPI_Finalize();

    return 0;
}
