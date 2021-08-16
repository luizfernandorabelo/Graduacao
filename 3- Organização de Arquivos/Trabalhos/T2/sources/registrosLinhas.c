// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#include "registrosLinhas.h"

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
Descrição: Aloca memória e preenche dados uma estrutura do tipo RegistroLinha a partir da entrada padrão
@return RegistroLinha* ponteiro para a região de memória em que os dados foram armazenados 
*/
RegistroLinha *carregaRegistroLinhaDaStdin() {

    // Alocando memória para uma estrutura do tipo RegistroLinha:
    RegistroLinha *registroLinha = malloc(sizeof(RegistroLinha));

    char buffer[10];

    // Marcando o campo quantidade de lugares:
    scan_quote_string(buffer);
    registroLinha->codLinha = atoi(buffer);

    // Marcando o campo aceita cartão: 
    scan_quote_string(buffer);
    registroLinha->aceitaCartao = strcmp(buffer, "") != 0 ? buffer[0] : '\0';

    // Marcando o campo nome linha:
    scan_quote_string(registroLinha->nomeLinha);
    registroLinha->nomeLinha[0] = strcmp(registroLinha->nomeLinha, "") != 0 ? registroLinha->nomeLinha[0] : '\0'; 

    // Marcando o campo categoria:
    scan_quote_string(registroLinha->corLinha);
    registroLinha->corLinha[0] = strcmp(registroLinha->corLinha, "") != 0 ? registroLinha->corLinha[0] : '\0'; 

    // Marcando os demais campos:
    registroLinha->removido = '1';
    registroLinha->tamanhoNome = strlen(registroLinha->nomeLinha);
    registroLinha->tamanhoCor = strlen(registroLinha->corLinha);
    registroLinha->tamanhoRegistro = 13 + registroLinha->tamanhoNome + registroLinha->tamanhoCor;

    return registroLinha;
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