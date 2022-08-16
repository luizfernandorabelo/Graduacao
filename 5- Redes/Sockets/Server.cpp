/*
    Par de programas (Client.cpp e Server.cpp) simples 
    para troca de 1 mensagem em uma conexão cliente-servidor
    feita por meio de sockets. 

    Projeto mais elaborado em https://github.com/Tulio-Santana-Ramos/TrabalhoFinalRedes
*/

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define TAMANHO_MENSAGEM 2048

int main(void) {
    
    // Criação de variáveis auxiliares:
    int fd_servidor, fd_cliente;
    struct sockaddr_in endereco_servidor, endereco_cliente;
    socklen_t tamanho_cliente;
    char mensagem_servidor[2000], mensagem_cliente[2000];
    
    // Limpeza dos buffers de mensagens:
    memset(mensagem_servidor, '\0', sizeof(mensagem_servidor));
    memset(mensagem_cliente, '\0', sizeof(mensagem_cliente));
    
    // Criação do socket:
    fd_servidor = socket(AF_INET, SOCK_STREAM, 0);
    
    // Verificação de sucesso na criação:
    if (fd_servidor < 0){
        std::cerr << "Erro ao criar socket do servidor!\n";
        exit(-1);
    }
    std::cout << "Socket do servidor criado com sucesso!\n";
    
    // Atribuição de IP e porta:
    endereco_servidor.sin_family = AF_INET;                      // família de sockets p/ IPv4 
    endereco_servidor.sin_port = htons(2000);                    // porta padrão em que os clientes se conectarão
    endereco_servidor.sin_addr.s_addr = inet_addr("127.0.0.1");  // loopback (mas funcionaria com outros hosts na mesma rede)
    
    // Conexão no IP e porta pré determinados:
    if (bind(fd_servidor, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor)) < 0) {
        std::cerr << "Não foi possível se conectar ao IP e porta determinados!\n";    
        exit(-1);
    }
    std::cout << "Bind realizado com sucesso!\n";
    
    // Marcação do socket para escuta por um único cliente:
    if (listen(fd_servidor, 1) < 0) {
        std::cout << "Erro na escuta por clientes!\n";
        exit(-1);
    }
    std::cout << "Servidor esperando por conexões!\n";
    
    // Aceite de conexão:
    tamanho_cliente = sizeof(endereco_cliente);
    fd_cliente = accept(fd_servidor, (struct sockaddr*) &endereco_cliente, &tamanho_cliente);
    
    /*
        As conversões realizads pelas funções inet_ntoa e ntohs (utilizadas
        abaixo) são necessárias pois rede e host armazenam os bits em memória
        de forma distinta (hosts por little endian e redes por big endian). 
    */

    // Verificação de sucesso na conexão:
    if (fd_cliente < 0) {
        std::cout << "Erro na conexão com o cliente :(\n";
    }
    std::cout << "Cliente conectado no IP " << inet_ntoa(endereco_cliente.sin_addr) << " e porta " << ntohs(endereco_cliente.sin_port) << "\n";
    
    // Recepção da mensagem do cliente:
    if (recv(fd_cliente, mensagem_cliente, sizeof(mensagem_cliente), 0) < 0) {
        std::cout << "Não foi possível receber a mensagem do cliente :(\n";
        exit(-1);
    }
    std::cout << "Mensagem recebida do cliente: " << mensagem_cliente << "\n";
    
    // Resposta ao cliente:
    strcpy(mensagem_servidor, "'Mensagem recebida com sucesso!'");
    if (send(fd_cliente, mensagem_servidor, strlen(mensagem_servidor), 0) < 0) {
        std::cout << "Não foi possível responder ao cliente :(\n";
        exit(-1);
    }
    
    // Fechamento dos sockets:
    close(fd_cliente);
    close(fd_servidor);
    
    return 0;
}
