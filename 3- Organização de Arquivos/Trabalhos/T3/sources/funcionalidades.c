#include "funcionalidades.h"

/*
Descrição: Realiza a junção de um arquivo binario veiculos e um arquivo binario de dados linha atraves de um loop aninhado
@param nomeArqVeic: nome do arquivo binário com os veículos
@param nomeArqLinhas: nome do arquivo binário com as linhas
@param campoVeiculo: campo que servirá para comparar veículos com as linhas (sempre codLinha nesse caso)
@param campoLinha: campo que servirá para comparar linhas com os veiculos (sempre codLinha nesse caso)
*/
void juncaoLoopUnico(char *nomeArqVeic, char *nomeArqLinhas, char *campoVeiculo, char *campoLinha) {
    FILE *arqVeic = fopen(nomeArqVeic, "r");
    FILE *arqLinhas = fopen(nomeArqLinhas, "r");

    if (arqVeic == NULL || arqLinhas == NULL){
    // Abortando a funcionalidade se algum dos parâmetros for inválido:
        imprimeMensagemErro(stdout);
        return;
    }
    if (strcmp(campoLinha, "codLinha") || strcmp(campoVeiculo, "codLinha")) {
        fclose(arqVeic);
        fclose(arqLinhas);
        imprimeMensagemErro(stdout);
        return;
    }

    //carregamento dos cabeçalhos para a memória principal
    CabecalhoVeiculo *cabVeiculo = carregaCabecalhoVeiculoDoBIN(arqVeic);
    CabecalhoLinha *cabLinha = carregaCabecalhoLinhaDoBIN(arqLinhas);

    //checagem dos status do cabecalho
    if (cabLinha->status == '0' ||cabVeiculo->status == '0'){
        imprimeMensagemErro(stdout);
        free(cabLinha);
        free(cabVeiculo);
        fclose(arqVeic);
        fclose(arqLinhas);
        return;
    }
    long primeiroRegistro = ftell(arqLinhas);
    int tevePrint =false;

    //loop para percorrer arquivo de veiculos até o fim
    while (!fimDoArquivoBIN(arqVeic))
    {
        RegistroVeiculo *regVeiculo = carregaRegistroVeiculoDoBIN(arqVeic);

        //verificando se o veiculo está logicamente removida
        if (regVeiculo->removido == '0'){
            free(regVeiculo);
            continue;
        }
        
        while (!fimDoArquivoBIN(arqLinhas))
        {
            RegistroLinha *regLinha = carregaRegistroLinhaDoBIN(arqLinhas);
            
            //verificando se a linha está logicamente removida
            if (regLinha->removido == '0'){
                free(regLinha);
                continue;
            }

            //se os campos codLinha forem iguais realizar impressao
            if (regVeiculo->codLinha == regLinha->codLinha){
                tevePrint =true;
                veiculoNaTela(regVeiculo, cabVeiculo);
                linhaNaTela(regLinha, cabLinha);
                free(regLinha);
                break;
            }
            free(regLinha);
        }

        //voltando o ponteiro da linha para o primeiro registro
        fseek(arqLinhas, primeiroRegistro, SEEK_SET);
        free (regVeiculo);
    }
    
    //verificando se algo foi impresso
    if (!tevePrint){
        printf("Registro inexistente.");
    }

    //liberação da memoria
    free(cabLinha);
    free(cabVeiculo);

    //Fechando os arquivos
    fclose(arqVeic);
    fclose(arqLinhas);
}

/*
Descrição: Realiza a junção de um arquivo binario veiculos e um arquivo binario de dados linha atraves de um loop único
@param nomeArqVeic: nome do arquivo binário com os veículos
@param nomeArqLinhas: nome do arquivo binário com as linhas
@param campoVeiculo: campo que servirá para comparar veículos com as linhas (sempre codLinha nesse caso)
@param campoLinha: campo que servirá para comparar linhas com os veiculos (sempre codLinha nesse caso)
@param nomeArqIndice: nome do arquivo de indices das linhas
*/
void juncaoArquivoIndice(char *nomeArqVeic, char *nomeArqLinhas, char *campoVeiculo, char *campoLinha, char *nomeArqIndice) {

    //abrindo os arquivos
    FILE *arqVeic = fopen(nomeArqVeic, "rb");
    FILE *arqLinhas = fopen(nomeArqLinhas, "rb");
    FILE *arqIndice = fopen(nomeArqIndice, "rb");

    // Abortando a funcionalidade se algum dos parâmetros for inválido:
    if (arqVeic == NULL || arqLinhas == NULL){ 
        imprimeMensagemErro(stdout);
        return;
    }
    if (strcmp(campoLinha, "codLinha") || strcmp(campoVeiculo, "codLinha")) {
        fclose(arqVeic);
        fclose(arqLinhas);
        fclose(arqIndice);
        imprimeMensagemErro(stdout);
        return;
    }

    //Lendo os cabecalhos
    CabecalhoVeiculo *cabVeiculo = carregaCabecalhoVeiculoDoBIN(arqVeic);
    CabecalhoLinha *cabLinha = carregaCabecalhoLinhaDoBIN(arqLinhas);
    NoCabecalhoAB *noCabAB= carregaNoCabecalhoDaAB(arqIndice);

    //Verificando se algum cabecalho possui status incosistente
    if (cabLinha->status == '0' ||cabVeiculo->status == '0' || noCabAB->status == '0'){
        free(cabLinha);
        free(cabVeiculo);
        free(noCabAB);
        fclose(arqVeic);
        fclose(arqLinhas);
        fclose(arqIndice);
        imprimeMensagemErro(stdout);
        return;
    }
    
    int tevePrint =false;

    //Loop unico no arquivo de veiculos
    while (!fimDoArquivoBIN(arqVeic)) {
        RegistroVeiculo *regVeiculo = carregaRegistroVeiculoDoBIN(arqVeic);

        //Verificando se o veiculo não está logicamente removido
        if (regVeiculo->removido == '0'){
            free(regVeiculo);
            continue;
        }
        //buscando no arquivo de indice
        long long offset = buscaRegistroDadosNaAB(arqIndice, noCabAB, regVeiculo->codLinha);

        //impressão caso a busca tenha sucesso
        if (offset != VALOR_NULO){
            tevePrint = 1;
            fseek(arqLinhas, offset, SEEK_SET);
            RegistroLinha *regLinha = carregaRegistroLinhaDoBIN(arqLinhas);
            veiculoNaTela(regVeiculo, cabVeiculo);
            linhaNaTela(regLinha, cabLinha);
            free(regLinha);
        }
        free(regVeiculo);
    }

    //verificando se algum registro foi impresso
    if (!tevePrint){
        printf("Registro inexistente.");
    }

    //Liberando a memória alocada
    free(cabLinha);
    free(cabVeiculo);
    free(noCabAB);

    //fechando os arquivos
    fclose(arqVeic);
    fclose(arqLinhas);
    fclose(arqIndice);
}

/*
Descrição: Ordena um arquivo de dados de veículos a partir do campo de ordenação em memória primária
@param nomeArqDesordenado: nome do arquivo binário com os dados desordenados
@param nomeArqOrdenado: nome do arquivo vazio que receberá os dados ordenados
@param campoOrdenacao: campo a partir do qual a ordenação será feita (sempre "codLinha")
*/
void ordenacaoVeiculos(char *nomeArqDesordenado, char *nomeArqOrdenado, char *campoOrdenacao) {

    // Abrindo o arquivo desordenado para leitura e o ordenado para escrita:
    FILE *arqDesordenado = fopen(nomeArqDesordenado, "rb");
    FILE *arqOrdenado = fopen(nomeArqOrdenado, "w+b");

    // Abortando a funcionalidade se algum dos parâmetros for inválido:
    if (arqDesordenado == NULL || arqOrdenado == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }
    if (strcmp(campoOrdenacao, "codLinha")) {
        fclose(arqOrdenado);
        fclose(arqDesordenado);
        imprimeMensagemErro(stdout);
        return;
    }

    // Obtendo o registro de cabeçalho do arquivo desordenado:
    CabecalhoVeiculo *cabArqDesordenado = carregaCabecalhoVeiculoDoBIN(arqDesordenado);

    // Abortando a funcionalidade se o arquivo desordenado estiver inconsistente:
    if (cabArqDesordenado->status == '0') {
        fclose(arqDesordenado);
        fclose(arqOrdenado);
        free(cabArqDesordenado);
        imprimeMensagemErro(stdout);
        return;
    }

    // Inicializando um registro de cabeçalho para o arquivo ordenado:
    CabecalhoVeiculo *cabArqOrdenado = inicializaCabecalhoVeiculo();
    copiaDescricoesCabecalhoVeiculo(cabArqDesordenado, cabArqOrdenado);
    escreveCabecalhoVeiculoNoBIN(cabArqOrdenado, arqOrdenado);

    // Obtendo o vetor de registros ordenados lidos do arquivo antigo:
    RegistroVeiculo **registrosVeiculo = carregaVetorRegistrosVeiculoOrdenadoDoBIN(arqDesordenado);

    // Escrevendo os registros ordenados no novo arquivo:
    escreveVetorRegistrosVeiculoOrdenadoNoBIN(arqOrdenado, registrosVeiculo, cabArqOrdenado);

    // Atualizando o registro de cabeçalho do arquivo ordenado:
    cabArqOrdenado->status = '1';
    escreveCabecalhoVeiculoNoBIN(cabArqOrdenado, arqOrdenado);

    // Fechando os arquivos:
    fclose(arqDesordenado);
    fclose(arqOrdenado);

    // Liberando memória alocada:
    free(cabArqDesordenado);
    free(cabArqOrdenado);
    free(registrosVeiculo);

    // Imprimindo o resultado do novo binário na tela:
    binarioNaTela(nomeArqOrdenado);
}

/*
Descrição: Ordena um arquivo de dados de linhas a partir do campo de ordenação em memória primária
@param nomeArqDesordenado: nome do arquivo binário com os dados desordenados
@param nomeArqOrdenado: nome do arquivo vazio que receberá os dados ordenados
@param campoOrdenacao: campo a partir do qual a ordenação será feita (sempre "codLinha")
*/
void ordenacaoLinhas(char *nomeArqDesordenado, char *nomeArqOrdenado, char *campoOrdenacao) {

    // Abrindo o arquivo desordenado para leitura e o ordenado para escrita:
    FILE *arqDesordenado = fopen(nomeArqDesordenado, "rb");
    FILE *arqOrdenado = fopen(nomeArqOrdenado, "w+b");

    // Abortando a funcionalidade se algum dos parâmetros for inválido:
    if (arqDesordenado == NULL || arqOrdenado == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }
    if (strcmp(campoOrdenacao, "codLinha")) {
        fclose(arqOrdenado);
        fclose(arqDesordenado);
        imprimeMensagemErro(stdout);
        return;
    }

    // Obtendo o registro de cabeçalho do arquivo desordenado:
    CabecalhoLinha *cabArqDesordenado = carregaCabecalhoLinhaDoBIN(arqDesordenado);

    // Abortando a funcionalidade se o arquivo desordenado estiver inconsistente:
    if (cabArqDesordenado->status == '0') {
        fclose(arqDesordenado);
        fclose(arqOrdenado);
        free(cabArqDesordenado);
        imprimeMensagemErro(stdout);
        return;
    }

    // Inicializando um registro de cabeçalho para o arquivo ordenado:
    CabecalhoLinha *cabArqOrdenado = inicializaCabecalhoLinha();
    copiaDescricoesCabecalhoLinha(cabArqDesordenado, cabArqOrdenado);
    escreveCabecalhoLinhaNoBIN(cabArqOrdenado, arqOrdenado);

    // Obtendo o vetor de registros ordenados lidos do arquivo antigo:
    RegistroLinha **registrosLinha = carregaVetorRegistrosLinhaOrdenadoDoBIN(arqDesordenado);

    // Escrevendo os registros ordenados no novo arquivo:
    escreveVetorRegistrosLinhaOrdenadoNoBIN(arqOrdenado, registrosLinha, cabArqOrdenado);

    // Atualizando o registro de cabeçalho do arquivo ordenado:
    cabArqOrdenado->status = '1';
    escreveCabecalhoLinhaNoBIN(cabArqOrdenado, arqOrdenado);

    // Fechando os arquivos:
    fclose(arqDesordenado);
    fclose(arqOrdenado);

    // Liberando memória alocada:
    free(cabArqDesordenado);
    free(cabArqOrdenado);
    free(registrosLinha);

    // Imprimindo o resultado do novo binário na tela:
    binarioNaTela(nomeArqOrdenado);
}

/*
Descrição: Realiza a junção de dois arquivos de dados pelo método ordenação-intercalação, mostrando o resultado na saída padrão
@param nomeArqVeic: nome do arquivo binário com os dados dos veículos
@param nomeArqLinhas: nome do arquivo binário com os dados das linhas
@param campoVeiculo: campo de referência do veiculo para a junção (sempre codLinha)
@param campoLinha: campo de referência da linha para a junção (sempre codLinha)
*/
void juncaoOrdenada(char *nomeArqVeic, char *nomeArqLinhas, char *campoVeiculo, char *campoLinha) {

    // Abrindo os arquivos de dados para leitura:
    FILE *arqVeiculos = fopen(nomeArqVeic, "rb");
    FILE *arqLinhas = fopen(nomeArqLinhas, "rb");

    // Abortando a funcionalidade se algum dos parâmetros for inválido:
    if (arqVeiculos == NULL || arqLinhas == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }
    if (strcmp(campoVeiculo, "codLinha") || strcmp(campoLinha, "codLinha")) {
        fclose(arqLinhas);
        fclose(arqVeiculos);
        imprimeMensagemErro(stdout);
        return;
    }

    // Obtendo os registros de cabeçalho dos arquivos:
    CabecalhoVeiculo *cabecalhoVeiculo = carregaCabecalhoVeiculoDoBIN(arqVeiculos);
    CabecalhoLinha *cabecalhoLinha = carregaCabecalhoLinhaDoBIN(arqLinhas);

    // Abortando a funcionalidade se algum arquivo estiver inconsistente:
    if (cabecalhoVeiculo->status == '0' || cabecalhoLinha->status == '0') {
        free(cabecalhoLinha);
        free(cabecalhoVeiculo);
        fclose(arqLinhas);
        fclose(arqVeiculos);
        imprimeMensagemErro(stdout);
        return;
    }

    // Obtendo os vetores de registros ordenados lidos dos arquivos:
    RegistroVeiculo **registrosVeiculos = carregaVetorRegistrosVeiculoOrdenadoDoBIN(arqVeiculos);
    RegistroLinha **registrosLinhas = carregaVetorRegistrosLinhaOrdenadoDoBIN(arqLinhas);

    // Realizando a junção pala intercalação dos vetores ordenados:
    int indiceLinhas = 0, indiceVeiculos = 0, houveJuncao = false;
    while (registrosLinhas[indiceLinhas] != NULL) { // percorrendo as linhas
        int codLinhaAtual = registrosLinhas[indiceLinhas]->codLinha;
        while (registrosVeiculos[indiceVeiculos] != NULL && registrosVeiculos[indiceVeiculos]->codLinha <= codLinhaAtual) { // percorrendo os veículos
            if (registrosVeiculos[indiceVeiculos]->codLinha == codLinhaAtual) { 
                veiculoNaTela(registrosVeiculos[indiceVeiculos], cabecalhoVeiculo);
                linhaNaTela(registrosLinhas[indiceLinhas], cabecalhoLinha);
                houveJuncao = true;
            }
            indiceVeiculos++;
        }
        indiceLinhas++;
    }

    // Imprimindo alerta caso nenhuma junção tenha sido feita:
    if (!houveJuncao)
        printf("Registro inexistente.");

    // Re-inserindo os registros, agora ordenados, nos arquivos:
    CabecalhoVeiculo *cabVeiculoOrdenado = inicializaCabecalhoVeiculo();
    CabecalhoLinha *cabLinhaOrdenado = inicializaCabecalhoLinha();
    copiaDescricoesCabecalhoVeiculo(cabecalhoVeiculo, cabVeiculoOrdenado);
    copiaDescricoesCabecalhoLinha(cabecalhoLinha, cabLinhaOrdenado);
    escreveVetorRegistrosVeiculoOrdenadoNoBIN(arqVeiculos, registrosVeiculos, cabVeiculoOrdenado);
    escreveVetorRegistrosLinhaOrdenadoNoBIN(arqLinhas, registrosLinhas, cabLinhaOrdenado);

    // Fechando os arquivos:
    fclose(arqVeiculos);
    fclose(arqLinhas);

    // Liberando Memória Alocada:
    free(registrosVeiculos);
    free(registrosLinhas);
    free(cabecalhoLinha);
    free(cabecalhoVeiculo);
}