// mpirun -np 2 ponto_a_ponto

/*
-> Modos de send no MPI:
    - standard: pode ou não ter buffer interno; transferência síncrona ou assíncrona; implementação decide;
    - buffered: usuário cria um buffer e o utiliza para o send;
    - synchronous: exige sincronização entre o send e INÍCIO da execução do receive; pode ou não ter buffer;
    - ready: receive deve ser executado antes do send; essa garantia deve ser dada pelo programador;

-> Modo de receive no MPI:
    - standard: análogo ao send standard, mas para o recebimento da mensagem;

* Cada um dos modos pode ser implementado de maneira bloqueante ou não bloqueante => 8 sends e 2 receives diferentes
*/

/*
-> Cenário do código:
+------------------------------------------------------------------------------+
| Processo 0                            | Processo 1                           |
+------------------------------------------------------------------------------+
| tag = 0                               | tag = 0                              |
| rcv_nao_bloqueante_standard(i)        | rcv_bloqueante_standard(ii)          |
| snd_bloqueante_standard(ii)           | rcv_bloqueante_standard(iii)         |
| snd_bloqueante_buffered(iii)          | rcv_bloqueante_standard(iv)          |
| snd_bloqueante_sincrono(iv)           | rcv_nao_bloqueante_standard(vi)      |
| tag = 1                               | tag = 1                              |
| rcv_bloqueante_standard(v)            | snd_bloqueante_standard(v)           |
| tag = 0                               | wait rcv_nao_bloqueante_standard(vi) |
| snd_bloqueante_ready(vi)              | tag = 0                              |
| wait rcv_nao_bloqueante_standard(i)   | snd_nao_bloqueante_standard(i)       |
|                                       | wait snd_nao_bloqueante(i)           |
-------------------------------------------------------------------------------+
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi/mpi.h>

#define TAMANHO 80

void receive_bloqueante_standard(char *mensagem, int origem, int tag, MPI_Status *status, int rank) {
    MPI_Recv(mensagem, TAMANHO, MPI_CHAR, origem, tag, MPI_COMM_WORLD, status);
    printf("Rank %d: Mensagem recebida bloqueante = %s\n", rank, mensagem);
    fflush(0);
}

void receive_nao_bloqueante_standard(char *mensagem, int origem, int tag, MPI_Request *requisicao, MPI_Status *status,  int rank, int *flag) {
    MPI_Irecv(mensagem, TAMANHO, MPI_CHAR, origem, tag, MPI_COMM_WORLD, requisicao);
    MPI_Test(requisicao, flag, status);
    if (*flag)
        printf("Rank %d: MPI_Test flag = %d, mensagem recebida nao bloqueante = %s\n", rank, *flag, mensagem);
    else
        printf("Rank %d: MPI_Test flag = %d, mensagem recebida nao bloqueante = \"null\"\n", rank, *flag);
}

void send_bloqueante_standard(char *mensagem, int destino, int tag) {
    strcpy(mensagem, "Mensagem Enviada por Send Bloqueante Standard");
    MPI_Send(mensagem, strlen(mensagem) + 1, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
}

void send_nao_bloqueante_standard(char *mensagem, int destino, int tag, MPI_Request *requisicao) {
    strcpy(mensagem, "Mensagem Enviada por Send não Bloqueante Standard");
    MPI_Isend(mensagem, strlen(mensagem) + 1, MPI_CHAR, destino, tag, MPI_COMM_WORLD, requisicao);
}

void send_bloqueante_buffer(char *mensagem, int destino, int tag) {
    int tamanho_mensagem, tamanho_buffer, total_mensagens = 1;
    strcpy(mensagem, "Mensagem Enviada por Send Bloqueante com Buffer");
    MPI_Pack_size(strlen(mensagem) + 1, MPI_CHAR, MPI_COMM_WORLD, &tamanho_mensagem);
    tamanho_buffer = tamanho_mensagem + total_mensagens * MPI_BSEND_OVERHEAD;
    char *buffer = malloc(tamanho_buffer);
    MPI_Buffer_attach(buffer, tamanho_buffer);
    MPI_Bsend(mensagem, strlen(mensagem) + 1, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
    MPI_Buffer_detach(buffer, &tamanho_buffer);
}

void send_bloqueante_sincrono(char *mensagem, int destino, int tag) {
    strcpy(mensagem, "Mensagem Enviada por Send Bloqueante Síncrono");
    MPI_Ssend(mensagem, strlen(mensagem) + 1, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
}

void send_bloqueante_ready(char *mensagem, int destino, int tag) {
    strcpy(mensagem, "Mensagem Enviada por Send Bloqueante Ready");
    MPI_Rsend(mensagem, strlen(mensagem) + 1, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
}

void esperar_recebimento_mensagem(char *mensagem, MPI_Request *requisicao, MPI_Status *status, int rank, int flag) {
    if (!flag) {
        MPI_Wait(requisicao, status);
        printf("Rank %d: Mensagem recebida com wait = %s\n", rank, mensagem);
    }
}

void esperar_envio_mensagem(MPI_Request *requisicao, MPI_Status *status, int rank) {
    MPI_Wait(requisicao, status);
    printf("Rank %d: Mensagem segura para ser enviada!\n", rank);
    fflush(0);
}

int main(int argc, char *argv[]) {

    int meu_rank, total_processos;

    MPI_Status status;
    MPI_Request requisicao_standard, requisicao_ready;
    char mensagem_envio[TAMANHO], mensagem_recebimento[TAMANHO], mensagem_sincronizacao[TAMANHO];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processos);

    if (meu_rank == 0) {
        int origem = 1, destino = 1, tag = 0, flag;
        receive_nao_bloqueante_standard(mensagem_recebimento, origem, tag, &requisicao_standard, &status, meu_rank, &flag);
        send_bloqueante_standard(mensagem_envio, destino, tag);
        send_bloqueante_buffer(mensagem_envio, destino, tag);
        send_bloqueante_sincrono(mensagem_envio, destino, tag);
        tag = 1;
        receive_bloqueante_standard(mensagem_sincronizacao, origem, tag, &status, meu_rank);
        tag = 0;
        send_bloqueante_ready(mensagem_envio, destino, tag);
        esperar_recebimento_mensagem(mensagem_recebimento, &requisicao_standard, &status, meu_rank, flag);
    } else {
        int origem = 0, destino = 0, tag = 0, flag;
        receive_bloqueante_standard(mensagem_recebimento, origem, tag, &status, meu_rank);
        receive_bloqueante_standard(mensagem_recebimento, origem, tag, &status, meu_rank);
        receive_bloqueante_standard(mensagem_recebimento, origem, tag, &status, meu_rank);
        receive_nao_bloqueante_standard(mensagem_recebimento, origem, tag, &requisicao_ready, &status, meu_rank, &flag);
        tag = 1;
        send_bloqueante_standard(mensagem_sincronizacao, destino, tag);
        esperar_recebimento_mensagem(mensagem_recebimento, &requisicao_ready, &status, meu_rank, flag);
        tag = 0;
        send_nao_bloqueante_standard(mensagem_envio, destino, tag, &requisicao_standard);
        esperar_envio_mensagem(&requisicao_standard, &status, meu_rank);
    }

    MPI_Finalize();

    return 0;
}
