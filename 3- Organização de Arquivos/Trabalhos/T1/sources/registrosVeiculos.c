#include "registrosVeiculos.h"

/*
Descrição: Aloca memória e preenche dados uma estrutura do tipo CabecalhoVeiculo a partir de um arquivo csv
@param arquivoCSV: fluxo do arquivo csv de onde as informações do registro de cabeçalho serão extraídas
@return CabecalhoVeiculo* ponteiro para a região de memória em que os dados foram armazenados 
*/
CabecalhoVeiculo *carregaCabecalhoVeiculoDoCSV(FILE *arquivoCSV) {

    // Alocando memória para uma estrutura do tipo CabecalhoVeiculo:
    CabecalhoVeiculo *cabecalho = malloc(sizeof(CabecalhoVeiculo));

    // Lendo o vetor de descrições dos campos do cabeçalho do arquivo CSV:
    char **descricoesCabecalho = leDescricoesCabecalhoCSV(arquivoCSV);

    // Atribuindo os valores das descrições lidas do csv à estrutura cabeçalho:
    strcpy(cabecalho->descrevePrefixo, descricoesCabecalho[0]);
    strcpy(cabecalho->descreveData, descricoesCabecalho[1]);
    strcpy(cabecalho->descreveLugares, descricoesCabecalho[2]);
    strcpy(cabecalho->descreveLinha, descricoesCabecalho[3]);
    strcpy(cabecalho->descreveModelo, descricoesCabecalho[4]);
    strcpy(cabecalho->descreveCategoria, descricoesCabecalho[5]);
    
    // Inicializando os demais campos da estrutura cabeçalho:
    cabecalho->status = '0';
    cabecalho->byteProxReg = 0;
    cabecalho->nroRegistros = 0;
    cabecalho->nroRegRemovidos = 0;

    // Liberando a memória alocada leitura das descricoes:
    for (int i = 0; i < 6; i++)
        free(descricoesCabecalho[i]);
    free(descricoesCabecalho);

    return cabecalho;
}

/*
Descrição: Aloca memória e preenche dados uma estrutura do tipo RegistroVeiculo a partir de um arquivo csv
@param arquivoCSV: fluxo do arquivo csv de onde as informações do registro de dados serão extraídas
@return RegistroVeiculo* ponteiro para a região de memória em que os dados foram armazenados 
*/
RegistroVeiculo *carregaRegistroVeiculoDoCSV(FILE *arquivoCSV) {

    // Alocando memória para uma estrutura do tipo RegistroVeiculo:
    RegistroVeiculo *registro = malloc(sizeof(RegistroVeiculo));

    // Marcando o campo removido:
    if (registroDoCSVEhRemovido(arquivoCSV))
        registro->removido = '0';
    else
        registro->removido = '1';

    // Marcando o campo prefixo:
    char *prefixo = leStringDoCSV(arquivoCSV);
    strcpy(registro->prefixo, prefixo);
    if (strlen(prefixo) < 5)
        for (int i = strlen(prefixo); i < 6; i++)
            registro->prefixo[i] = '\0';

    // Marcando o campo data:
    char *data = leStringDoCSV(arquivoCSV);
    strcpy(registro->data, data);
    if (strcmp(data, "NULO") == 0) {
        for (int i = 1; i < 10; i++)
            registro->data[i] = '@';
        registro->data[0] = '\0';
    }

    // Marcando os campos qtLugares e codLinha:
    registro->quantidadeLugares = leIntDoCSV(arquivoCSV);
    registro->codLinha = leIntDoCSV(arquivoCSV);

    // Marcando o campo modelo:
    char *modelo = leStringDoCSV(arquivoCSV);
    strcpy(registro->modelo, modelo);
    registro->modelo[0] = strcmp(modelo, "NULO") == 0 ? '\0' : registro->modelo[0];

    // Marcando o campo categoria:
    char *categoria = leStringDoCSV(arquivoCSV);
    strcpy(registro->categoria, categoria);
    registro->categoria[0] = strcmp(categoria, "NULO") == 0 ? '\0' : registro->categoria[0];

    // Marcando os demais campos:
    registro->tamanhoModelo = strlen(registro->modelo);
    registro->tamanhoCategoria = strlen(registro->categoria);
    registro->tamanhoRegistro = 31 + registro->tamanhoModelo + registro->tamanhoCategoria; 

    // Liberando memória alocada para leitura dos campos:
    free(prefixo);
    free(data);
    free(modelo);
    free(categoria);

    return registro;
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
Descrição: Aloca memória e preenche dados uma estrutura do tipo RegistroVeiculo a partir da entrada padrão
@return RegistroVeiculo* ponteiro para a região de memória em que os dados foram armazenados 
*/
RegistroVeiculo *carregaRegistroVeiculoDaStdin() {

    // Alocando memória para uma estrutura do tipo RegistroVeiculo:
    RegistroVeiculo *registroVeiculo = malloc(sizeof(RegistroVeiculo));

    // Marcando o campo prefixo:
    scan_quote_string(registroVeiculo->prefixo);

    // Marcando campo data:
    scan_quote_string(registroVeiculo->data);
    if (strcmp(registroVeiculo->data, "") == 0) {
        for (int i = 1; i < 10; i++)
            registroVeiculo->data[i] = '@';
        registroVeiculo->data[0] = '\0';
    }

    char inteiroAscii[10];

    // Marcando o campo quantidade de lugares:
    scan_quote_string(inteiroAscii);
    registroVeiculo->quantidadeLugares = strcmp(inteiroAscii, "") != 0 ? atoi(inteiroAscii) : -1;

    // Marcando o campo código da linha:
    scan_quote_string(inteiroAscii);
    registroVeiculo->codLinha = strcmp(inteiroAscii, "") != 0 ? atoi(inteiroAscii) : -1;

    // Marcando o campo modelo:
    scan_quote_string(registroVeiculo->modelo);
    registroVeiculo->modelo[0] = strcmp(registroVeiculo->modelo, "") != 0 ? registroVeiculo->modelo[0] : '\0'; 

    // Marcando o campo categoria:
    scan_quote_string(registroVeiculo->categoria);
    registroVeiculo->categoria[0] = strcmp(registroVeiculo->categoria, "") != 0 ? registroVeiculo->categoria[0] : '\0'; 

    // Marcando os demais campos:
    registroVeiculo->removido = '1';
    registroVeiculo->tamanhoCategoria = strlen(registroVeiculo->categoria);
    registroVeiculo->tamanhoModelo = strlen(registroVeiculo->modelo);
    registroVeiculo->tamanhoRegistro = 31 + registroVeiculo->tamanhoModelo + registroVeiculo->tamanhoCategoria;

    return registroVeiculo;
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

    printf("\n");
}

/*
Descricao: localiza qual campo está sendo buscado e faz uma busca sequencial no binário retornando o registro que satisfaz a condicao de busca
@param arquivoBIN arquivo binario que será utilizado para busca
@param valor valor buscado
@param campo campo buscado
@return Registro que possui o campo buscado com o valor fornecido, retorna NULL caso nada seja encontrado
*/
RegistroVeiculo *localizaVeiculo(FILE *arquivoBIN, char* valor, char *campo){
    if (strcmp("categoria", campo) == 0){
        while (!fimDoArquivoBIN(arquivoBIN))
        {
            RegistroVeiculo *reg = carregaRegistroVeiculoDoBIN(arquivoBIN);
            if (strcmp(reg->categoria, valor)==0 && reg->removido == '1') return reg;
            else free(reg);
        }
    }
    else if(strcmp("data", campo) ==0){
        while (!fimDoArquivoBIN(arquivoBIN))
        {
            RegistroVeiculo *reg = carregaRegistroVeiculoDoBIN(arquivoBIN);
            if (strcmp(reg->data, valor)==0 && reg->removido == '1') return reg;
            else free(reg);
        }
    }
    else if(strcmp("codLinha" , campo) ==0){
        int aux = atoi(valor);
        while (!fimDoArquivoBIN(arquivoBIN))
        {
            RegistroVeiculo *reg = carregaRegistroVeiculoDoBIN(arquivoBIN);
            if (reg->quantidadeLugares == aux && reg->removido == '1') return reg;
            else free(reg);
        }
    }
    else if (strcmp("quantidadeLugares", campo) == 0){
        int aux = atoi(valor);
        while (!fimDoArquivoBIN(arquivoBIN))
        {
            RegistroVeiculo *reg = carregaRegistroVeiculoDoBIN(arquivoBIN);
            if (reg->quantidadeLugares == aux && reg->removido == '1') return reg;
            else free(reg);
        }
    }
    else if (strcmp("modelo", campo) == 0){
        while (!fimDoArquivoBIN(arquivoBIN))
        {
            RegistroVeiculo *reg = carregaRegistroVeiculoDoBIN(arquivoBIN);
            if (strcmp(reg->modelo, valor)==0 && reg->removido == '1') return reg;
            else free(reg);
        }
    }
    else if (strcmp("prefixo", campo) == 0){
        while (!fimDoArquivoBIN(arquivoBIN))
        {
            RegistroVeiculo *reg = carregaRegistroVeiculoDoBIN(arquivoBIN);
            if (strcmp(reg->prefixo, valor)==0 && reg->removido == '1') return reg;
            else free(reg);
        }
    }
    return NULL;
}
