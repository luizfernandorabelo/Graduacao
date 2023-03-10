#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>

#define PI 3.14159265

int main(int argc, char *argv[]) {

    int meu_rank, total_processos, emissor = 0;
    double dado = -1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processos);

    if (meu_rank == 0)
        dado = PI;

    MPI_Bcast(&dado, 1, MPI_DOUBLE, emissor, MPI_COMM_WORLD);

    printf("Rank %d recebeu %.2lf\n", meu_rank, dado);

    MPI_Finalize();

    return 0;
}
