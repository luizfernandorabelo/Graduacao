#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>

#define TAMANHO 10  // máximo de processos / 2

int main(int argc, char *argv[]) {

    int meu_rank, total_processos, novo_rank;
    int ranks_pares[TAMANHO], ranks_impares[TAMANHO];

    MPI_Group grupo_original, grupo_par, grupo_impar;
    MPI_Comm comunicador_par, comunicador_impar, comunicador_utilizado;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processos);

    // Criação dos grupos de comunicação (0 pertence à ambos):
    ranks_pares[0] = ranks_impares[0] = 0;
    int total_pares = 1, total_impares = 1;
    for (int i = 1; i < total_processos; i++) {
        if (i % 2 == 0)
            ranks_pares[total_pares++] = i;
        else
            ranks_impares[total_impares++] = i;
    }

    // Obtenção do identificador do grupo original:
    MPI_Comm_group(MPI_COMM_WORLD, &grupo_original);

    // Criação do grupo dos pares e ímpares por inclusão:
    MPI_Group_incl(grupo_original, total_pares, ranks_pares, &grupo_par);
    MPI_Group_incl(grupo_original, total_impares, ranks_impares, &grupo_impar);
    
    /*
        A criação dos grupos poderia ser feita pela função MPI_Group_excl(),
        que em vez de criar o grupo com os ranks incluídos no vetor, cria os
        grupos com os ranks excluídos (não incluídos).
    */

    // Criação dos comunicadores dos pares e ímpares:
    MPI_Comm_create(MPI_COMM_WORLD, grupo_par, &comunicador_par);
    MPI_Comm_create(MPI_COMM_WORLD, grupo_impar, &comunicador_impar);

    if (meu_rank == 0) {
        MPI_Comm_rank(comunicador_par, &novo_rank);
        printf("Rank World: %d, Rank Pares: %d\n", meu_rank, novo_rank);
        MPI_Comm_rank(comunicador_impar, &novo_rank);
        printf("Rank World: %d, Rank Ímpares: %d\n", meu_rank, novo_rank);
    } else {
        if (meu_rank % 2 == 0)
            comunicador_utilizado = comunicador_par;
        else
            comunicador_utilizado = comunicador_impar;
        MPI_Comm_rank(comunicador_utilizado, &novo_rank);
        printf("Rank World: %d, Rank Novo: %d\n", meu_rank, novo_rank);
    }

    MPI_Finalize();

    return 0;
}
