// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#include "registrosVeiculos.h"

/*
Descrição: aloca memória e inicializa uma estrutura do tipo CabecalhoVeiculo, preenchendo-a com valores nulos
@return um pontero para a região de memória em que a estrutura foi alocada
*/
CabecalhoVeiculo *inicializaCabecalhoVeiculo(void) {

    // Alocando memória para uma estrutura CabecalhoVeiculo:
    CabecalhoVeiculo *cabecalhoNovo = malloc(sizeof(CabecalhoVeiculo));

    // Zerando os campos inteiros e caractere:
    cabecalhoNovo->status = '0';
    cabecalhoNovo->byteProxReg = 0;
    cabecalhoNovo->nroRegistros = 0;
    cabecalhoNovo->nroRegRemovidos = 0;

    // Zerando as descrições:
    memset(cabecalhoNovo->descrevePrefixo, 0, 19);
    memset(cabecalhoNovo->descreveData, 0, 36);
    memset(cabecalhoNovo->descreveLugares, 0, 43);
    memset(cabecalhoNovo->descreveLinha, 0, 27);
    memset(cabecalhoNovo->descreveModelo, 0, 18);
    memset(cabecalhoNovo->descreveCategoria, 0, 21);

    return cabecalhoNovo;
}

/*
Descrição: Copia os campos de descrições de uma estrutura de cabeçalho para outra
@param cabecalhoOriginal: ponteiro para registro de cabeçalho de origem das descrições
@param cabecalhoCopia: ponteiro para registro de cabeçalho de destino das descrições
*/
void copiaDescricoesCabecalhoVeiculo(CabecalhoVeiculo *cabecalhoOriginal, CabecalhoVeiculo *cabecalhoCopia) {
    strcpy(cabecalhoCopia->descrevePrefixo, cabecalhoOriginal->descrevePrefixo);
    strcpy(cabecalhoCopia->descreveData, cabecalhoOriginal->descreveData);
    strcpy(cabecalhoCopia->descreveLugares, cabecalhoOriginal->descreveLugares);
    strcpy(cabecalhoCopia->descreveLinha, cabecalhoOriginal->descreveLinha);
    strcpy(cabecalhoCopia->descreveModelo, cabecalhoOriginal->descreveModelo);
    strcpy(cabecalhoCopia->descreveCategoria, cabecalhoOriginal->descreveCategoria);
}

/*
Descrição: Escreve os dados de uma estrutura do tipo CabecalhoVeiculo* em um arquivo binário
@param cabecalho: ponteiro para a região de memória onde o registro de cabeçalho está armazenado 
@param arquivoBIN: fluxo do arquivo binário em que os dados serão escritos
*/
void escreveCabecalhoVeiculoNoBIN(CabecalhoVeiculo *cabecalho, FILE *arquivoBIN) {

    // Pulando para o início do arquivo binário
    fseek(arquivoBIN, 0, SEEK_SET);

    // Escrevendo os campos do registro de cabeçalho no binário:
    fwrite(&cabecalho->status, 1, 1, arquivoBIN);
    fwrite(&cabecalho->byteProxReg, sizeof(long long), 1, arquivoBIN);
    fwrite(&cabecalho->nroRegistros, sizeof(int), 1, arquivoBIN);
    fwrite(&cabecalho->nroRegRemovidos, sizeof(int), 1, arquivoBIN);
    fwrite(cabecalho->descrevePrefixo, 1, 18, arquivoBIN);
    fwrite(cabecalho->descreveData, 1, 35, arquivoBIN);
    fwrite(cabecalho->descreveLugares, 1, 42, arquivoBIN);
    fwrite(cabecalho->descreveLinha, 1, 26, arquivoBIN);
    fwrite(cabecalho->descreveModelo, 1, 17, arquivoBIN);
    fwrite(cabecalho->descreveCategoria, 1, 20, arquivoBIN);
}

/*
Descrição: Escreve os dados de uma estrutura do tipo RegistroVeiculo* em um arquivo binário
@param registroVeiculo: ponteiro para a região de memória onde o registro de dados está armazenado 
@param arquivoBIN: fluxo do arquivo binário em que os dados serão escritos
*/
void escreveRegistroVeiculoNoBIN(RegistroVeiculo *registroVeiculo, FILE *arquivoBIN) {
    // Escrevendo os campos do registro de dados no binário:
    fwrite(&registroVeiculo->removido, 1, 1, arquivoBIN);
    fwrite(&registroVeiculo->tamanhoRegistro, sizeof(int), 1, arquivoBIN);
    fwrite(registroVeiculo->prefixo, 1, 5, arquivoBIN);
    fwrite(registroVeiculo->data, 1, 10, arquivoBIN);
    fwrite(&registroVeiculo->quantidadeLugares, sizeof(int), 1, arquivoBIN);
    fwrite(&registroVeiculo->codLinha, sizeof(int), 1, arquivoBIN);
    fwrite(&registroVeiculo->tamanhoModelo, sizeof(int), 1, arquivoBIN);
    fwrite(registroVeiculo->modelo, registroVeiculo->tamanhoModelo, 1, arquivoBIN);
    fwrite(&registroVeiculo->tamanhoCategoria, sizeof(int), 1, arquivoBIN);
    fwrite(registroVeiculo->categoria, registroVeiculo->tamanhoCategoria, 1, arquivoBIN);
}

/*
Descrição: Escreve os dados de um vetor de ponteiros para estruturas de RegistroVeiculo ordenados em um arquivo binário
@param arquivoBIN: fluxo do arquivo binário em que os dados serão escritos
@param registroVeiculo: ponteiro para a região de memória onde o vetor de registros de dados está armazenado 
@param cabecalho: cabeçalho referente ao arquivoBIN
*/
void escreveVetorRegistrosVeiculoOrdenadoNoBIN(FILE *arquivoBIN, RegistroVeiculo **registrosVeiculo, CabecalhoVeiculo *cabecalho) {
    // Escrevendo os registros ordenados, um a um:
    for (int i = 0; registrosVeiculo[i] != NULL; i++) {
        escreveRegistroVeiculoNoBIN(registrosVeiculo[i], arquivoBIN);
        cabecalho->nroRegistros += 1;
        cabecalho->byteProxReg = ftell(arquivoBIN);
        free(registrosVeiculo[i]);
    }
}

/*
Descrição: Aloca memória e preenche dados uma estrutura do tipo CabecalhoVeiculo a partir de um arquivo binário 
@param arquivoBIN: fluxo do arquivo binário de onde as informações do registro de cabeçalho serão extraídas
@return CabecalhoVeiculo* ponteiro para a região de memória em que os dados foram armazenados 
*/
CabecalhoVeiculo *carregaCabecalhoVeiculoDoBIN(FILE *arquivoBIN) {

    // Pulando para o início do arquivo binário
    fseek(arquivoBIN, 0, SEEK_SET);

    // Alocando memória para uma estrutura do tipo CabecalhoVeiculo:
    CabecalhoVeiculo *cabecalho = malloc(sizeof(CabecalhoVeiculo));

    // Lendo os campos do registro de cabeçalho do binário:
    fread(&cabecalho->status, 1, 1, arquivoBIN);
    fread(&cabecalho->byteProxReg, sizeof(long long), 1, arquivoBIN);
    fread(&cabecalho->nroRegistros, sizeof(int), 1, arquivoBIN);
    fread(&cabecalho->nroRegRemovidos, sizeof(int), 1, arquivoBIN);
    fread(cabecalho->descrevePrefixo, 1, 18, arquivoBIN);
    fread(cabecalho->descreveData, 1, 35, arquivoBIN);
    fread(cabecalho->descreveLugares, 1, 42, arquivoBIN);
    fread(cabecalho->descreveLinha, 1, 26, arquivoBIN);
    fread(cabecalho->descreveModelo, 1, 17, arquivoBIN);
    fread(cabecalho->descreveCategoria, 1, 20, arquivoBIN);

    // Finalizando os campos string com '\0':
    cabecalho->descrevePrefixo[18] = '\0';
    cabecalho->descreveData[35] = '\0';
    cabecalho->descreveLugares[42] = '\0';
    cabecalho->descreveLinha[26] = '\0';
    cabecalho->descreveModelo[17] = '\0';
    cabecalho->descreveCategoria[20] = '\0';

    return cabecalho;
}

/*
Descrição: Aloca memória e preenche dados uma estrutura do tipo RegistroVeiculo a partir de um arquivo binário 
@param arquivoBIN: fluxo do arquivo binário de onde as informações do registro de dados serão extraídas
@return RegistroVeiculo* ponteiro para a região de memória em que os dados foram armazenados 
*/
RegistroVeiculo *carregaRegistroVeiculoDoBIN(FILE *arquivoBIN) {

    // Alocando memória para uma estrutura do tipo RegistroVeiculo:
    RegistroVeiculo *registroVeiculo = malloc(sizeof(RegistroVeiculo));

    // Lendo os campos do registro de dados do binário:
    fread(&registroVeiculo->removido, 1, 1, arquivoBIN);
    fread(&registroVeiculo->tamanhoRegistro, sizeof(int), 1, arquivoBIN);
    fread(registroVeiculo->prefixo, 5, 1, arquivoBIN);
    fread(registroVeiculo->data, 10, 1, arquivoBIN);
    fread(&registroVeiculo->quantidadeLugares, sizeof(int), 1, arquivoBIN);
    fread(&registroVeiculo->codLinha, sizeof(int), 1, arquivoBIN);
    fread(&registroVeiculo->tamanhoModelo, sizeof(int), 1, arquivoBIN);
    fread(registroVeiculo->modelo, registroVeiculo->tamanhoModelo, 1, arquivoBIN);
    fread(&registroVeiculo->tamanhoCategoria, sizeof(int), 1, arquivoBIN);
    fread(registroVeiculo->categoria, registroVeiculo->tamanhoCategoria, 1, arquivoBIN);

    // Finalizando os campos string com '\0':
    registroVeiculo->prefixo[5] = '\0';
    registroVeiculo->data[10] = '\0';
    registroVeiculo->modelo[registroVeiculo->tamanhoModelo] = '\0';
    registroVeiculo->categoria[registroVeiculo->tamanhoCategoria] = '\0';

    return registroVeiculo;
}

/*
Descrição: Aloca memória e preenche um vetor ordenado de estruturas do tipo RegistroVeiculo lidas de um arquivo binário 
@param arquivoBIN: fluxo do arquivo binário de onde as informações do registro de dados serão extraídas
@return RegistroVeiculo** ponteiro para a região de memória em que o vetor foi armazenado
*/
RegistroVeiculo **carregaVetorRegistrosVeiculoOrdenadoDoBIN(FILE *arquivoBIN) {

    // Inicializando um vetor para os registros que serão carregados na memória:
    RegistroVeiculo **registrosVeiculo = NULL;
    int nroRegistros = 0;

    // Carregando todos os registros não removidos do arquivo desordenado para o vetor de registros:
    while (!fimDoArquivoBIN(arquivoBIN)) {
        RegistroVeiculo *registroAtual = carregaRegistroVeiculoDoBIN(arquivoBIN);
        if (registroAtual->removido == '1') { // se o registro não for removido
            registrosVeiculo = realloc(registrosVeiculo, (nroRegistros + 1) * sizeof(RegistroVeiculo *));
            registrosVeiculo[nroRegistros++] = registroAtual;
        }
        else {
            free(registroAtual);
        }
    }

    // Ordenando o vetor de registros não removidos com a função qsort:
    qsort(registrosVeiculo, nroRegistros, sizeof(RegistroVeiculo *), comparVeiculos);

    // Adicionando o terminador de vetor, nessa implementação definido como nulo:
    registrosVeiculo = realloc(registrosVeiculo, (nroRegistros + 1) * sizeof(RegistroVeiculo *));
    registrosVeiculo[nroRegistros] = NULL;

    return registrosVeiculo;
}

/*
Descricao: Printa na tela o registro veiculos segundo a forma indicada pelo cabecalho
@param Reg Registro veiculos que será printado na tela
@param cabecalho estrutura de cabecalho que será utilizada para printar
*/
void veiculoNaTela(RegistroVeiculo *Reg, CabecalhoVeiculo *cabecalho) {

    // Imprimindo campo prefixo:
    printf("%s: %s\n", cabecalho->descrevePrefixo, Reg->prefixo);

    // Imprimindo campo modelo:
    printf("%s: ", cabecalho->descreveModelo);
    if (Reg->modelo[0] != '\0') printf("%s\n", Reg->modelo);
    else printf("campo com valor nulo\n");

    // Imprimindo campo categoria:
    printf ("%s: ", cabecalho->descreveCategoria);
    if (Reg->categoria[0] != '\0') printf("%s\n", Reg->categoria);
    else printf("campo com valor nulo\n");

    // Imprimindo campo data:
    printf("%s: ", cabecalho->descreveData);
    if (Reg->data[0] != '\0'){
        int ano = atoi (Reg->data);
        int auxMes = atoi (Reg->data+5);
        int dia = atoi (Reg->data+8);
        char *mes = verMes(auxMes);
        if (dia >=10) printf("%d de %s de %d\n", dia, mes, ano);
        else printf("0%d de %s de %d\n", dia, mes, ano);
        free(mes);
    }
    else printf("campo com valor nulo\n");

    // Imprimindo campo lugares:
    printf("%s: ", cabecalho->descreveLugares);
    if (Reg->quantidadeLugares != -1)
        printf ("%d\n", Reg->quantidadeLugares);
    else printf("campo com valor nulo\n");
}