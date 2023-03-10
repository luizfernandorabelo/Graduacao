#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>

int main(int argc, char *argv[]) {

    int meu_rank, total_processos, novo_rank, cor, chave;
    MPI_Comm novo_comunicador;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processos);

    /*
        Cor: identificador do grupo.
            - resto da divisão por 2 p/ separar pares de ímpares;
        Chave: rank do processo no novo intracomunicador.
            - rank original / 2 (apenas exemplificação);
    */

    cor = meu_rank % 2;
    chave = meu_rank / 2;

    /*
        O split deve estar, obrigatoriamente, contido no
        ambiente de execução do MPI. Se um processo não
        for participar do split, colocar MPI_UNDEFINED
        para o novo comunicador.
    */

    MPI_Comm_split(MPI_COMM_WORLD, cor, chave, &novo_comunicador);

    MPI_Comm_rank(novo_comunicador, &novo_rank);
    printf("Rank World: %d, Cor: %d, Rank Novo: %d\n", meu_rank, cor, novo_rank);

    MPI_Finalize();

    return 0;
}
