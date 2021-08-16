#include "funcionalidadesLinhas.h"

/*
Descrição: Lê vários registros de um arquivo de entrada e grava esses registros em um arquivo de saída
@param arquivoEntrada nome do arquivo csv de onde os registros serão lidos
@param arquivoSaida nome do arquivo binário no qual os registros serão gravados 
*/
void createTableLinhas(char *arquivoEntrada, char *arquivoSaida) {
    
    // Abrindo o arquivo CSV para leitura e o arquivo binário para escrita:
    FILE *arquivoCSV = fopen(arquivoEntrada, "r");
    FILE *arquivoBIN = fopen(arquivoSaida, "wb");

    // Abortando a funcionalidade se ocorrer algum erro com a abertura dos arquivos:
    if (arquivoCSV == NULL || arquivoBIN == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    // Obtendo os campos do cabeçalho do arquivo CSV e escrevendo-os no arquivo binário:
    CabecalhoLinha *cabecalho = carregaCabecalhoLinhaDoCSV(arquivoCSV);
    escreveCabecalhoLinhaNoBIN(cabecalho, arquivoBIN);

    // Obtendo os registros de dados do arquivo CSV e escrevendo-os no arquivo binário:
    while (!fimDoArquivoCSV(arquivoCSV)) {
        RegistroLinha *registroAtual = carregaRegistroLinhaDoCSV(arquivoCSV);
        if (registroAtual->removido == '0') // se o registro estiver removido
            cabecalho->nroRegRemovidos += 1;
        else
            cabecalho->nroRegistros += 1;
        escreveRegistroLinhaNoBIN(registroAtual, arquivoBIN);
        free(registroAtual);
    }

    // Atualizando o registro de cabeçalho:
    cabecalho->status = '1';
    cabecalho->byteProxReg = ftell(arquivoBIN);
    escreveCabecalhoLinhaNoBIN(cabecalho, arquivoBIN);

    // Fechando os arquivos
    fclose(arquivoCSV);
    fclose(arquivoBIN);

    // Liberando memória do cabeçalho:
    free(cabecalho);
    
    // Imprimindo o resultado do binário na tela:
    binarioNaTela(arquivoSaida);
}

/*
Descrição: Recupera todos os registros armazenados em um arquivo binário e os imprime na saída padrão 
@param arquivoEntrada nome do arquivo binário de onde os registros serão recuperados 
*/
void selectFromLinhas(char *arquivoEntrada) {

    // Abrindo o arquivo binário para leitura:
    FILE* arquivoBIN = fopen(arquivoEntrada, "rb");

    // Abortando a funcionalidade se o arquivo de entrada não existir:
    if (arquivoBIN == NULL){
        imprimeMensagemErro(stdout);
        return;
    }

    // Carregando o registro de cabeçalho do arquivo binário para a memória:
    CabecalhoLinha *Cabecalho = carregaCabecalhoLinhaDoBIN(arquivoBIN);

    // Abortando a funcionalidade se o arquivo de entrada estiver inconsistente:
    if (Cabecalho->status == '0') {
        imprimeMensagemErro(stdout);
        fclose(arquivoBIN);
        free(Cabecalho);
        return;
    }

    // Lendo e imprimindo os registros na tela:
    int printouRegistro = false;
    while (!fimDoArquivoBIN(arquivoBIN)) {
        RegistroLinha *reg = carregaRegistroLinhaDoBIN(arquivoBIN);
        if (reg->removido == '1') linhaNaTela(reg, Cabecalho);
        free(reg);
        printouRegistro = true;
    }

    // Imprimindo "Registro inexistente" caso nenhum registro seja encontrado:
    if (!printouRegistro)
        printf("Registro inexistente.\n");

    // Liberando memória alocada e fechando o arquivo binário:
    free(Cabecalho);
    fclose(arquivoBIN);
}

/*
Descrição: Imprime na saída padrão os registros armazenados em um arquivo binário que satisfazem uma condição de busca
@param arquivoEntrada nome do arquivo binário de onde os registros serão recuperados 
@param campo nome do campo buscado
@param valor valor do campo buscado
*/
void selectWhereLinhas(char *arquivoEntrada, char *campo, char *valor) {

    // Abrindo o arquivo binário para leitura:
    FILE *arquivoBIN = fopen(arquivoEntrada, "rb");

    // Abortando a funcionalidade se o arquivo de entrada não existir:
    if (arquivoBIN == NULL){
        imprimeMensagemErro(stdout);
        return;
    }

    // Carregando o registro de cabeçalho do arquivo binário para a memória:
    CabecalhoLinha *cabecalho = carregaCabecalhoLinhaDoBIN(arquivoBIN);

    // Abortando a funcionalidade se o arquivo de entrada estiver inconsistente:
    if (cabecalho->status == '0') {
        imprimeMensagemErro(stdout);
        fclose(arquivoBIN);
        free(cabecalho);
        return;
    }

    // Lendo e imprimindo os registros na tela que satisfazem à condição de busca:
    int printouRegistro = false;
    while (!fimDoArquivoBIN(arquivoBIN)) {
        RegistroLinha *reg = localizaLinha(arquivoBIN, valor, campo);
        if (reg == NULL) break;
        linhaNaTela(reg, cabecalho);
        printouRegistro = true;
        free(reg);
    } 

    // Imprimindo "Registro inexistente" caso nenhum registro seja encontrado:
    if (!printouRegistro)
        printf("Registro inexistente.\n");

    // Liberando memória alocada e fechando o arquivo binário:
    fclose(arquivoBIN);
    free(cabecalho);
}

/*
Descrição: Insere um conjunto de registros em um arquivo binário com dados lidos da entrada padrão 
@param arquivoEntrada nome do arquivo binário em que os registros serão inseridos 
@param numeroRegistros numero de registros que serão inseridos
*/
void insertIntoLinhas(char *arquivoEntrada, int numeroRegistros) {

    // Abrindo o arquivo binário para leitura e escrita:
    FILE *arquivoBIN = fopen(arquivoEntrada, "r+b");

    // Abortando a funcionalidade se o arquivo de entrada não existir:
    if (arquivoBIN == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    // Carregando o registro de cabeçalho do arquivo binário para a memória:
    CabecalhoLinha *cabecalho = carregaCabecalhoLinhaDoBIN(arquivoBIN);

    // Abortando a funcionalidade se o arquivo de entrada estiver inconsistente:
    if (cabecalho->status == '0') {
        imprimeMensagemErro(stdout);
        fclose(arquivoBIN);
        free(cabecalho);
        return;
    }

    // Atualizando o registro de cabeçalho no arquivo binário:
    cabecalho->status = '0';
    fseek(arquivoBIN, 0, SEEK_SET);
    fwrite(&cabecalho->status, 1, 1, arquivoBIN);

    // Inserindo os registros lidos da entrada padrão:
    fseek(arquivoBIN, 0, SEEK_END);
    for (int i = 0; i < numeroRegistros; i++) {
        RegistroLinha *registroAtual = carregaRegistroLinhaDaStdin();
        escreveRegistroLinhaNoBIN(registroAtual, arquivoBIN);
        cabecalho->nroRegistros += 1;
        free(registroAtual);
    }
    
    // Atualizando o registro de cabeçalho no arquivo binário:
    cabecalho->status = '1';
    cabecalho->byteProxReg = ftell(arquivoBIN);
    escreveCabecalhoLinhaNoBIN(cabecalho, arquivoBIN);

    // Fechando arquivo binário e liberando memória alocada:
    fclose(arquivoBIN);
    free(cabecalho);

    // Imprimindo o resultado do binário na tela:
    binarioNaTela(arquivoEntrada);
}
