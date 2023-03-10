#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi/mpi.h>

#define MENSAGEM "Uma mensagem qualquer passada circularmente"

int main(int argc, char *argv[]) {

    int total_processos, meu_rank, origem, destino, tag_mensagem = 1;
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
        origem = total_processos - 1;
        destino = 1;
        strcpy(buffer_envio, MENSAGEM);
        printf("P0: Enviando mensagem para P%d\n", destino);
        MPI_Send(buffer_envio, strlen(MENSAGEM) + 1, MPI_CHAR, destino, tag_mensagem, MPI_COMM_WORLD);
        printf("P0: Aguardando mensagem de P%d\n", origem);
        MPI_Recv(buffer_recebimento, strlen(MENSAGEM) + 1, MPI_CHAR, origem, tag_mensagem, MPI_COMM_WORLD, &status_mpi);
        printf("P0: Recebeu \"%s\" de P%d\n", buffer_recebimento, origem);
    } else {
        origem = meu_rank - 1;
        destino = meu_rank == total_processos - 1 ? 0 : meu_rank + 1;
        printf("P%d: Aguardando mensagem de P%d\n", meu_rank, origem);
        MPI_Recv(buffer_recebimento, strlen(MENSAGEM) + 1, MPI_CHAR, origem, tag_mensagem, MPI_COMM_WORLD, &status_mpi); 
        printf("P%d: Recebeu \"%s\" de P%d\n", meu_rank, buffer_recebimento, origem);
        strcpy(buffer_envio, buffer_recebimento);
        printf("P%d: Enviando mensagem para P%d\n", meu_rank, destino);
        MPI_Send(buffer_envio, strlen(MENSAGEM) + 1, MPI_CHAR, destino, tag_mensagem, MPI_COMM_WORLD);
    }

    free(buffer_envio);
    free(buffer_recebimento);
    
    if (MPI_Finalize() == MPI_SUCCESS)
        printf("Execução terminada com sucesso!\n");

    return 0;
}

