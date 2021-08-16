// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#include "registrosLinhas.h"

/*
Descrição: aloca memória e inicializa uma estrutura do tipo CabecalhoLinha, preenchendo-a com valores nulos
@return um pontero para a região de memória em que a estrutura foi alocada
*/
CabecalhoLinha *inicializaCabecalhoLinha(void) {

    // Alocando memória para uma estrutura CabecalhoLinha:
    CabecalhoLinha *cabecalhoNovo = malloc(sizeof(CabecalhoLinha));

    // Zerando os campos inteiros e caractere:
    cabecalhoNovo->status = '0';
    cabecalhoNovo->byteProxReg = 0;
    cabecalhoNovo->nroRegistros = 0;
    cabecalhoNovo->nroRegRemovidos = 0;

    // Zerando as descrições:
    memset(cabecalhoNovo->descreveCodigo, 0, 16);
    memset(cabecalhoNovo->descreveCartao, 0, 14);
    memset(cabecalhoNovo->descreveNome, 0, 14);
    memset(cabecalhoNovo->descreveCor, 0, 25);

    return cabecalhoNovo;
}

/*
Descrição: Copia os campos de descrições de uma estrutura de cabeçalho para outra
@param cabecalhoOriginal: ponteiro para registro de cabeçalho de origem das descrições
@param cabecalhoCopia: ponteiro para registro de cabeçalho de destino das descrições
*/
void copiaDescricoesCabecalhoLinha(CabecalhoLinha *cabecalhoOriginal, CabecalhoLinha *cabecalhoCopia) {
    strcpy(cabecalhoCopia->descreveCodigo, cabecalhoOriginal->descreveCodigo);
    strcpy(cabecalhoCopia->descreveCartao, cabecalhoOriginal->descreveCartao);
    strcpy(cabecalhoCopia->descreveNome, cabecalhoOriginal->descreveNome);
    strcpy(cabecalhoCopia->descreveCor, cabecalhoOriginal->descreveCor);
}

/*
Descrição: Escreve os dados de uma estrutura do tipo CabecalhoLinha* em um arquivo binário
@param cabecalho: ponteiro para a região de memória onde o registro de cabeçalho está armazenado 
@param arquivoBIN: fluxo do arquivo binário em que os dados serão escritos
*/
void escreveCabecalhoLinhaNoBIN(CabecalhoLinha *cabecalho, FILE *arquivoBIN) {
    // Pulando para o início do arquivo binário
    fseek(arquivoBIN, 0, SEEK_SET);
    // Escrevendo os campos do registro de cabeçalho no binário:
    fwrite(&cabecalho->status, 1, 1, arquivoBIN);
    fwrite(&cabecalho->byteProxReg, sizeof(long long), 1, arquivoBIN);
    fwrite(&cabecalho->nroRegistros, sizeof(int), 1, arquivoBIN);
    fwrite(&cabecalho->nroRegRemovidos, sizeof(int), 1, arquivoBIN);
    fwrite(cabecalho->descreveCodigo, 1, 15, arquivoBIN);
    fwrite(cabecalho->descreveCartao, 1, 13, arquivoBIN);
    fwrite(cabecalho->descreveNome, 1, 13, arquivoBIN);
    fwrite(cabecalho->descreveCor, 1, 24, arquivoBIN);
}

/*
Descrição: Escreve os dados de uma estrutura do tipo RegistroLinha* em um arquivo binário
@param registroLinha: ponteiro para a região de memória onde o registro de dados está armazenado 
@param arquivoBIN: fluxo do arquivo binário em que os dados serão escritos
*/
void escreveRegistroLinhaNoBIN(RegistroLinha *registroLinha, FILE *arquivoBIN) {
    // Escrevendo os campos do registro de dados no binário:
    fwrite(&registroLinha->removido, 1, 1, arquivoBIN);
    fwrite(&registroLinha->tamanhoRegistro, sizeof(int), 1, arquivoBIN);
    fwrite(&registroLinha->codLinha, sizeof(int), 1, arquivoBIN);
    fwrite(&registroLinha->aceitaCartao, 1, 1, arquivoBIN);
    fwrite(&registroLinha->tamanhoNome, sizeof(int), 1, arquivoBIN);
    fwrite(registroLinha->nomeLinha, 1, registroLinha->tamanhoNome, arquivoBIN);
    fwrite(&registroLinha->tamanhoCor, sizeof(int), 1, arquivoBIN);
    fwrite(registroLinha->corLinha, 1, registroLinha->tamanhoCor, arquivoBIN);
}

/*
Descrição: Escreve os dados de um vetor de ponteiros para estruturas de RegistroLinha ordenados em um arquivo binário
@param arquivoBIN: fluxo do arquivo binário em que os dados serão escritos
@param registrosLinha: ponteiro para a região de memória onde o vetor de registros de dados está armazenado 
@param cabecalho: cabeçalho referente ao arquivoBIN
*/
void escreveVetorRegistrosLinhaOrdenadoNoBIN(FILE *arquivoBIN, RegistroLinha **registrosLinha, CabecalhoLinha *cabeclho) {
    // Escrevendo os registros ordenados, um a um:
    for (int i = 0; registrosLinha[i] != NULL; i++) {
        escreveRegistroLinhaNoBIN(registrosLinha[i], arquivoBIN);
        cabeclho->nroRegistros += 1;
        cabeclho->byteProxReg = ftell(arquivoBIN);
        free(registrosLinha[i]);
    }
}

/*
Descrição: Aloca memória e preenche dados uma estrutura do tipo CabecalhoLinha a partir de um arquivo binário 
@param arquivoBIN: fluxo do arquivo binário de onde as informações do registro de cabeçalho serão extraídas
@return CabecalhoLinha* ponteiro para a região de memória em que os dados foram armazenados 
*/
CabecalhoLinha *carregaCabecalhoLinhaDoBIN(FILE *arquivoBIN) {

    // Pulando para o início do arquivo binário
    fseek(arquivoBIN, 0, SEEK_SET);

    // Alocando memória para uma estrutura do tipo CabecalhoLinha:
    CabecalhoLinha *cabecalho = malloc(sizeof(CabecalhoLinha));

    // Lendo os campos do registro de cabeçalho do binário:
    fread(&cabecalho->status, 1, 1, arquivoBIN);
    fread(&cabecalho->byteProxReg, sizeof(long long), 1, arquivoBIN);
    fread(&cabecalho->nroRegistros, sizeof(int), 1, arquivoBIN);
    fread(&cabecalho->nroRegRemovidos, sizeof(int), 1, arquivoBIN);
    fread(cabecalho->descreveCodigo, 1, 15, arquivoBIN);
    fread(cabecalho->descreveCartao, 1, 13, arquivoBIN);
    fread(cabecalho->descreveNome, 1, 13, arquivoBIN);
    fread(cabecalho->descreveCor, 1, 24, arquivoBIN);

    // Finalizando os campos string com '\0':
    cabecalho->descreveCodigo[15] = '\0';
    cabecalho->descreveCartao[13] = '\0';
    cabecalho->descreveNome[13] = '\0';
    cabecalho->descreveCor[24] = '\0';

    return cabecalho;
}

/*
Descrição: Aloca memória e preenche dados uma estrutura do tipo RegistroLinha a partir de um arquivo binário 
@param arquivoBIN: fluxo do arquivo binário de onde as informações do registro de dados serão extraídas
@return RegistroLinha* ponteiro para a região de memória em que os dados foram armazenados 
*/
RegistroLinha *carregaRegistroLinhaDoBIN(FILE *arquivoBIN) {

    // Alocando memória para uma estrutura do tipo RegistroLinha:
    RegistroLinha *registroLinha = malloc(sizeof(RegistroLinha));

    // Lendo os campos do registro de dados do binário:
    fread(&registroLinha->removido, 1, 1, arquivoBIN);
    fread(&registroLinha->tamanhoRegistro, sizeof(int), 1, arquivoBIN);
    fread(&registroLinha->codLinha, sizeof(int), 1, arquivoBIN);
    fread(&registroLinha->aceitaCartao, 1, 1, arquivoBIN);
    fread(&registroLinha->tamanhoNome, sizeof(int), 1, arquivoBIN);
    fread(registroLinha->nomeLinha, 1, registroLinha->tamanhoNome, arquivoBIN);
    fread(&registroLinha->tamanhoCor, sizeof(int), 1, arquivoBIN);
    fread(registroLinha->corLinha, 1, registroLinha->tamanhoCor, arquivoBIN);

    // Finalizando os campos string com '\0':
    registroLinha->nomeLinha[registroLinha->tamanhoNome] = '\0';
    registroLinha->corLinha[registroLinha->tamanhoCor] = '\0';

    return registroLinha;
}

/*
Descrição: Aloca memória e preenche um vetor ordenado de estruturas do tipo RegistroLinha lidas de um arquivo binário 
@param arquivoBIN: fluxo do arquivo binário de onde as informações do registro de dados serão extraídas
@return RegistroLinha** ponteiro para a região de memória em que o vetor foi armazenado
*/
RegistroLinha **carregaVetorRegistrosLinhaOrdenadoDoBIN(FILE *arquivoBIN) {

    // Inicializando um vetor para os registros que serão carregados na memória:
    RegistroLinha **registrosLinha = NULL;
    int nroRegistros = 0;

    // Carregando todos os registros não removidos do arquivo desordenado para o vetor de registros:
    while (!fimDoArquivoBIN(arquivoBIN)) {
        RegistroLinha *registroAtual = carregaRegistroLinhaDoBIN(arquivoBIN);
        if (registroAtual->removido == '1') {
            registrosLinha = realloc(registrosLinha, (nroRegistros + 1) * sizeof(RegistroLinha *));
            registrosLinha[nroRegistros++] = registroAtual;
        }
        else {
            free(registroAtual);
        }
    }

    // Ordenando o vetor de registros não removidos com a função qsort:
    qsort(registrosLinha, nroRegistros, sizeof(RegistroLinha *), comparLinhas);

    // Adicionando o terminador de vetor, nessa implementação definido como nulo:
    registrosLinha = realloc(registrosLinha, (nroRegistros + 1) * sizeof(RegistroLinha *));
    registrosLinha[nroRegistros] = NULL;

    return registrosLinha;
}

/*
Descricao: Printa na tela o registro Linha segundo a forma indicada pelo cabecalho
@param Reg Registro Linha que será printado na tela
@param cabecalho estrutura de cabecalho que será utilizada para printar
*/
void linhaNaTela (RegistroLinha *Reg, CabecalhoLinha *cabecalho){

    // Imprimindo o campo código:
    printf("%s: %d\n", cabecalho->descreveCodigo, Reg->codLinha);

    // Imprimindo o campo nome:
    printf("%s: ", cabecalho->descreveNome);
    if (Reg->nomeLinha[0] != '\0') printf("%s\n", Reg->nomeLinha);
    else printf("campo com valor nulo\n");

    // Imprimindo o campo cor:
    printf("%s: ", cabecalho->descreveCor);
    if (Reg->corLinha[0] != '\0') printf("%s\n", Reg->corLinha);
    else printf("campo com valor nulo\n");

    // Imprimindo o campo aceita cartão:
    printf ("%s: ", cabecalho->descreveCartao);
    if (Reg->aceitaCartao != '\0') {
        switch (Reg->aceitaCartao)
        {
        case 'S':
            printf("PAGAMENTO SOMENTE COM CARTAO SEM PRESENCA DE COBRADOR\n");
            break;
        case 'N':
            printf("PAGAMENTO EM CARTAO E DINHEIRO\n");
            break;
        case 'F':
            printf("PAGAMENTO EM CARTAO SOMENTE NO FINAL DE SEMANA\n");
            break;
        
        default:
            break;
        }
    }
    else printf("campo com  valor  nulo\n");

    printf("\n");
}