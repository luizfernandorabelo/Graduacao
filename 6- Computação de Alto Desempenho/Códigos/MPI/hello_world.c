// mpirun -np 2 hello_world

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi/mpi.h>

#define MENSAGEM "Olá mundo!!!"

int main(int argc, char *argv[]) {

    int total_processos, meu_rank, origem, destino, tag_mensagem = 1;  // tag = "id da msg"
    char *buffer_recebimento = calloc(strlen(MENSAGEM) + 1, sizeof(char));
    char *buffer_envio = calloc(strlen(MENSAGEM) + 1, sizeof(char));
    MPI_Status status_mpi;

    // Inicialização do MPI:
    MPI_Init(&argc, &argv);

    // Contagem do número de processos:
    MPI_Comm_size(MPI_COMM_WORLD, &total_processos);

    // Obtensão da "classificação" entre os processos:
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);

    // Envio / Recebimento de mensagens:
    if (meu_rank == 0) {
        origem = destino = 1;
        strcpy(buffer_envio, MENSAGEM);
        MPI_Send(buffer_envio, strlen(MENSAGEM) + 1, MPI_CHAR, destino, tag_mensagem++, MPI_COMM_WORLD);
        MPI_Recv(buffer_recebimento, strlen(MENSAGEM) + 1, MPI_CHAR, origem, tag_mensagem, MPI_COMM_WORLD, &status_mpi);
        printf("Mensagem recebida: %s\n", buffer_recebimento);
    } else {
        origem = destino = 0;
        MPI_Recv(buffer_recebimento, strlen(MENSAGEM) + 1, MPI_CHAR, origem, tag_mensagem++, MPI_COMM_WORLD, &status_mpi); 
        strcpy(buffer_envio, buffer_recebimento);
        MPI_Send(buffer_envio, strlen(MENSAGEM) + 1, MPI_CHAR, destino, tag_mensagem, MPI_COMM_WORLD);
    }

    free(buffer_envio);
    free(buffer_recebimento);
    
    if (MPI_Finalize() == MPI_SUCCESS)
        printf("Execução terminada com sucesso!\n");

    return 0;
}
