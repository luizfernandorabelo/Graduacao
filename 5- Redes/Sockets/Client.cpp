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
    int fd_cliente;
    struct sockaddr_in endereco_servidor;
    char mensagem_servidor[TAMANHO_MENSAGEM], mensagem_cliente[TAMANHO_MENSAGEM];
    
    // Limpeza dos buffers de mensagens:
    memset(mensagem_servidor, '\0', sizeof(mensagem_servidor));
    memset(mensagem_cliente, '\0', sizeof(mensagem_cliente));
    
    // Criação do socket:
    fd_cliente = socket(AF_INET, SOCK_STREAM, 0);
    
    // Verificação de sucesso na criação:
    if (fd_cliente < 0){
        std::cerr << "Erro ao criar socket do cliente!\n";
        exit(-1);
    }
    std::cout << "Socket do cliente criado com sucesso!\n";
    
    // Atribuição do IP e porta do servidor:
    endereco_servidor.sin_family = AF_INET;                      // família de sockets p/ IPv4
    endereco_servidor.sin_port = htons(2000);                    // porta padrão definida em Server.cpp
    endereco_servidor.sin_addr.s_addr = inet_addr("127.0.0.1");  // loopback (mas funcionaria com outros hosts na mesma rede)
    
    // Requisição de conexão com o servidor:
    if (connect(fd_cliente, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor)) < 0) {
        std::cerr << "Não foi possível se conectar ao servidor!\n";
        exit(-1);
    }
    std::cout << "Conexão com o servidor estabelecida com sucesso!\n";
    
    // Leitura de mensagem do usuário:
    std::cout << "Digite sua mensagem: ";
    std::string mensagem_digitada;
    getline(std::cin, mensagem_digitada);

    // Cópia da mensagem lida para o buffer:
    strcpy(mensagem_cliente, mensagem_digitada.c_str());
    
    // Envio da menssagem para o servidor:
    if (send(fd_cliente, mensagem_cliente, strlen(mensagem_cliente), 0) < 0) {
        std::cerr << "A mensagem não foi enviada :(\n";
        exit(-1);
    }
    std::cout << "Mensagem enviada com sucesso!\n";
    
    // Recebimento da resposta do servidor:
    if (recv(fd_cliente, mensagem_servidor, sizeof(mensagem_servidor), 0) < 0) {
        std::cerr << "Não foi possível receber nenhuma resposta :(\n";
        exit(-1);
    }
    std::cout << "Servidor disse: " << mensagem_servidor << "\n";
    
    // Fechamento do socket:
    close(fd_cliente);
    
    return 0;
}
