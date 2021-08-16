#include "leitorCSV.h"

/*
Descrição: Verifca se o caractere passado por parâmetro é um delimitador de campo ou de registro
@param caractere caractere a ser verificado
@return int 1 se verdadeiro | 0 se falso
*/
bool ehDelimitador(char caractere) {

    if (caractere == DELIMITADOR_CAMPO || caractere == '\n' || caractere == '\r' || caractere == EOF)
        return true;

    return false;
}

/*
Descrição: Verifica se o fluxo passado por parâmetro chegou ao seu fim
@param stream: fluxo a ser verificado
@return int 1 se verdadeiro | 0 se falso
*/
bool fimDoArquivoCSV(FILE *stream) {

    if (ehDelimitador(fgetc(stream)))
        return true;

    fseek(stream, -1, SEEK_CUR); // voltamos um byte (pois "comemos" um char válido)
    return false;
}

/*
Descrição: Verifica se um registro prestes a ser lido está marcado como logicamente removido
@param arquivoCSV: fluxo do arquivo csv a partir do qual a verificação será feita
@return int 1 se verdadeiro | 0 se falso
*/
bool registroDoCSVEhRemovido(FILE *arquivoCSV) {

    if (fgetc(arquivoCSV) == '*') 
        return true; 

    fseek(arquivoCSV, -1, SEEK_CUR); // voltamos um byte (pois "comemos" um char válido)
    return false;
}

/*
Descrição: Lê todas as frases das descrições do campo cabeçalho de um arquivo csv e as retorna
@param stream: fluxo a partir do qual as frases serão lidas
@return char** conjunto das frases lidas
*/
char **leDescricoesCabecalhoCSV(FILE *stream) {

    char **cabecalho = NULL;
    char *campoAtual = NULL;
    char *linha = calloc(256, sizeof(char));
    char *enderecoAtual = linha;
    int totalCampos = 0;

    // Lendo uma linha inteira do CSV:
    fscanf(stream, "%[^\n] ", linha);

    // Retornando nulo se houver algum erro com a linha lida:
    if (strlen(linha) <= 1) {
        free(linha);
        return NULL;
    }
    
    // Separando a linha lida em frases e armazenando-as na variável cabecalho:
    while ((campoAtual = strtok(enderecoAtual, ",")) != NULL) {
        cabecalho = realloc(cabecalho, (totalCampos + 1) * sizeof(char *));
        cabecalho[totalCampos] = calloc(strlen(campoAtual) + 1, sizeof(char));
        strcpy(cabecalho[totalCampos++], campoAtual);
        enderecoAtual = NULL;
    }

    free(linha);
    return cabecalho;
}

/*
Descrição: Lê uma string de um arquivo csv e a retorna
@param stream: fluxo a partir do qual a string será lida
@return char* string lida 
*/
char *leStringDoCSV(FILE *stream) {

    char caractereAtual = fgetc(stream);

    // Pulando caracteres não printáveis (menores que 32 na tabela ASCII)
    while (caractereAtual < 32) {
        caractereAtual = fgetc(stream);
        if (caractereAtual == EOF)
            return NULL;
    }

    char *string = calloc(1, sizeof(char));
    int tamanhoString = 0;

    // Lendo os campos válidos da string:
    while (!ehDelimitador(caractereAtual)) {
        string = realloc(string, tamanhoString + 2);
        string[tamanhoString++] = caractereAtual;
        caractereAtual = fgetc(stream);
    }

    string[tamanhoString] = '\0';
    return string;
}

/*
Descrição: Lê um inteiro de um arquivo csv e o retorna
@param stream: fluxo a partir do qual o inteiro será lido
@return int inteiro lido 
*/
int leIntDoCSV(FILE *stream) {

    // Lendo inteiro na forma string:
    char *inteiroAscii = leStringDoCSV(stream);

    // Verificando se a leitura foi bem sucedida:
    if (inteiroAscii == NULL)
        return -1;
    
    // Verificando se o inteiro é inválido:
    if (!isdigit(inteiroAscii[0])) {
        free(inteiroAscii);
        return -1;
    }

    // Convertendo o inteiro para sua forma numérica:
    int inteiro = atoi(inteiroAscii);
    free(inteiroAscii);

    return inteiro;
}

/*
Descrição: Lê um long long de um arquivo csv e o retorna
@param stream: fluxo a partir do qual o long long será lido
@return long long ll lido 
*/
long long leLongLongDoCSV(FILE *stream) {

    // Lendo long long na forma string:
    char *longlongAscii = leStringDoCSV(stream);

    // Verificando se a leitura foi bem sucedida:
    if (longlongAscii == NULL)
        return -1;
    
    // Verificando se o long long é inválido:
    if (!isdigit(longlongAscii[0])) {
        free(longlongAscii);
        return -1;
    }
    
    // Convertendo o long long para sua forma numérica:
    long long longlongNumerico = atoll(longlongAscii);
    free(longlongAscii);

    return longlongNumerico;
}

/*
Descrição: Lê um caractere de um arquivo csv e o retorna
@param stream: fluxo a partir do qual o caractere será lido
@return char caractere lido 
*/
char leCharDoCSV(FILE *stream) {
    
    char *string = leStringDoCSV(stream);

    if (string == NULL)
        return '\0';

    char caractere = string[0];

    free(string);
    return caractere;
}
