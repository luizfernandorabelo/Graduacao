// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#include "funcionalidadesVeiculos.h"

/*
Descrição: Lê vários registros de um arquivo binário e cria um arquivo de índice árvore B
@param nomeArquivoDados nome do arquivo binário de onde os registros serão lidos
@param nomeArquivoIndice nome do arquivo de índice que será gerado
*/
void createIndexVeiculos(char *nomeArquivoDados, char *nomeArquivoIndice) {

    // Abrindo o arquivo de dados para leitura e o de índice para escrita:
    FILE *arquivoDados = fopen(nomeArquivoDados, "rb");
    FILE *arquivoIndice = fopen(nomeArquivoIndice, "w+b");
    
    // Abortando a funcionalidade se ocorrer algum erro com a abertura dos arquivos:
    if (arquivoDados == NULL || arquivoIndice == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    // Carregando os cabeçalhos dos arquivos de dados e de índice para a memória:
    CabecalhoVeiculo *cabecalhoVeiculo = carregaCabecalhoVeiculoDoBIN(arquivoDados);
    NoCabecalhoAB *cabecalhoAB = carregaNoCabecalhoDaAB(arquivoIndice);

    // Abortando a funcionalidade se o status do arquivo de dados for inconsistente:
    if (cabecalhoVeiculo->status == '0') {
        imprimeMensagemErro(stdout);
        return;
    }

    // Obtendo os registros do arquivo de dados e inserindo suas chaves/byteoffsets no arquivo de índice:
    while (!fimDoArquivoBIN(arquivoDados)) {
        long long byteOffsetAtual = ftell(arquivoDados);
        RegistroVeiculo *registroAtual = carregaRegistroVeiculoDoBIN(arquivoDados);
        if (registroAtual->removido == '1') {
            int prefixoInteiro = convertePrefixo(registroAtual->prefixo);
            insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, prefixoInteiro, byteOffsetAtual);
        }
        free(registroAtual);
    }

    // Atualizando o registro de cabeçalho do arquivo de índice para consistente:
    cabecalhoAB->status = '1';
    escreveNoCabecalhoNaAB(arquivoIndice, cabecalhoAB);

    // Fechando os arquivos:
    fclose(arquivoDados);
    fclose(arquivoIndice);

    // Liberando memória alocada:
    free(cabecalhoAB);
    free(cabecalhoVeiculo);

    // Imprimindo o resultado do arquivo de índice com binário na tela:
    binarioNaTela(nomeArquivoIndice);
}

/*
Descrição: Essa função procura um registro veículo dado um campo e um valor
@param nomeArquivoDados nome do arquivo binário de onde os registros serão lidos
@param nomeArquivoIndice nome do arquivo de índice que será gerado
@param campo Campo que será utilizado para a busca (no caso sempre é o prefixo)
@param valor Valor do campo buscado
*/
void selectWhereVeiculos(char *nomeArquivoDados, char *nomeArquivoIndice, char *campo, char *valor) {
    
    // Abrindo os arquivos de dado e índice para leitura:
    FILE *arquivoDados = fopen(nomeArquivoDados, "rb");
    FILE *arquivoIndice = fopen(nomeArquivoIndice, "rb");

    // Abortando a funcionalidade se algum dos arquivos não existir:
    if (arquivoDados == NULL || arquivoIndice == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    // Carregando os cabeçalhos dos arquivos de dados e de índice para a memória:
    CabecalhoVeiculo *cabecalhoVeiculo = carregaCabecalhoVeiculoDoBIN(arquivoDados);
    NoCabecalhoAB *cabecalhoAB = carregaNoCabecalhoDaAB(arquivoIndice);

    // Abortando a funcionalidade se algum arquivo estiver inconsistente:
    if (cabecalhoVeiculo->status == '0' || cabecalhoAB->status == '0') {
        imprimeMensagemErro(stdout);
        return;
    }

    // Conversão do prefixo pra inteiro:
    int valorint = convertePrefixo(valor);
    
    // Realização da busca e verificação de erro:
    int byteOffSet = buscaRegistroDadosNaAB(arquivoIndice, cabecalhoAB, valorint);
    if (byteOffSet == VALOR_NULO) {
        printf("Registro inexistente.");
        return;
    }
    
    // Posicionamento do cursor no byte offset, carregamento do registro e impressão do registro na tela:
    fseek(arquivoDados, byteOffSet, SEEK_SET);
    RegistroVeiculo *veiculo = carregaRegistroVeiculoDoBIN(arquivoDados);
    veiculoNaTela(veiculo, cabecalhoVeiculo);

    // Fechando os arquivos:
    fclose(arquivoDados);
    fclose(arquivoIndice);

    // Liberando memória alocada:
    free(cabecalhoVeiculo);
    free(cabecalhoAB);
    free(veiculo);
}

/*
Descrição: Insere um conjunto de registros em um arquivo binário com dados lidos da entrada padrão, 
atualizando também o arquivo de índice 
@param nomeArquivoDados nome do arquivo de dados em que os registros serão inseridos 
@param nomeArquivoIndice nome do arquivo de índice referente ao arquivo de dados
@param numeroRegistros número de registros que serão inseridos
*/
void insertIntoVeiculos(char *nomeArquivoDados, char *nomeArquivoIndice, int numeroRegistros) {

    // Abrindo os arquivos de dado e índice para leitura e escrita:
    FILE *arquivoDados = fopen(nomeArquivoDados, "r+b");
    FILE *arquivoIndice = fopen(nomeArquivoIndice, "r+b");

    // Abortando a funcionalidade se algum dos arquivos não existir:
    if (arquivoDados == NULL || arquivoIndice == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    // Carregando os cabeçalhos dos arquivos de dados e de índice para a memória:
    CabecalhoVeiculo *cabecalhoVeiculo = carregaCabecalhoVeiculoDoBIN(arquivoDados);
    NoCabecalhoAB *cabecalhoAB = carregaNoCabecalhoDaAB(arquivoIndice);

    // Abortando a funcionalidade se algum arquivo estiver inconsistente:
    if (cabecalhoVeiculo->status == '0' || cabecalhoAB->status == '0') {
        imprimeMensagemErro(stdout);
        return;
    }

    // Atualizando os registros de cabeçalho para inconsistentes:
    cabecalhoVeiculo->status = '0';
    cabecalhoAB->status = '0';
    fseek(arquivoDados, 0, SEEK_SET);
    fseek(arquivoIndice, 0, SEEK_SET);
    fwrite(&cabecalhoVeiculo->status, 1, 1, arquivoDados);
    fwrite(&cabecalhoAB->status, 1, 1, arquivoIndice);

    // Inserindo os registros lidos da entrada padrão:
    fseek(arquivoDados, 0, SEEK_END);
    for (int i = 0; i < numeroRegistros; i++) {
        long long byteOffsetAtual = ftell(arquivoDados);
        RegistroVeiculo *registroAtual = carregaRegistroVeiculoDaStdin();
        escreveRegistroVeiculoNoBIN(registroAtual, arquivoDados);
        int prefixoInteiro = convertePrefixo(registroAtual->prefixo);
        insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, prefixoInteiro, byteOffsetAtual);
        cabecalhoVeiculo->nroRegistros += 1;
        cabecalhoVeiculo->byteProxReg = ftell(arquivoDados);
        free(registroAtual);
    }
    
    // Atualizando o cabeçalho do arquivo de dados:
    cabecalhoVeiculo->status = '1';
    escreveCabecalhoVeiculoNoBIN(cabecalhoVeiculo, arquivoDados);

    // Atualizando o cabeçalho do arquivo de índice:
    cabecalhoAB->status = '1';
    escreveNoCabecalhoNaAB(arquivoIndice, cabecalhoAB);

    // Fechando os arquivos:
    fclose(arquivoDados);
    fclose(arquivoIndice);

    // Liberando memória alocada:
    free(cabecalhoVeiculo);
    free(cabecalhoAB);

    // Imprimindo o resultado do arquivo de índice na tela:
    binarioNaTela(nomeArquivoIndice);
}
