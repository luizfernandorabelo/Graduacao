#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>
#include <string.h>
#include <math.h>

#define REG_COMP_FAILURE -1
#define NONEXISTENT_FILE -2
#define NO_BMP_FILE -3
#define INVALID_OPTION -4

#define BYTE_SIZE 1
#define BITMAP_COLORS 256

#define NEGATIVE 1
#define BLACK_AND_WHITE 2

//Estrutura para Cabeçalho de Arquivos:
typedef struct{
    char *signature;
    int fileSize;
    int reserved;
    int deslocation;
}header;

//Estrutura para Mapa de Bits de Arquivos:
typedef struct{
    int headerSize;
    int width;
    int height;
    short flatsNumber;
    unsigned char bitPerPixel;
    int compression;
    int imageSize;
    int horizontalResolution;
    int verticalResolution;
    int totalColors;
    int importantColors;
}bits_map;

//Estrutura para Paleta de Cores de Arquivos:
typedef struct{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char reserved;
}pallete;

//Estrutura para Área de Dados de Arquivos:
typedef struct{
    short **matrixData;
    long *lineSum;
    int trashNumber;
}data_area;

//Estrutura com todas as Informações do Arquivo:
typedef struct{
    header *fileHeader;
    bits_map *bitsMapHeader;
    pallete *colorsPallete;
    data_area *data;
}file_data;

char *readString(void);
/*Funçãoo que lê e armazena dinamicamente uma cadeia de caracteres até encontrar o '/n'. Retorna
o endereço em que a cadeia de caracteres foi armazenada.*/

int readOption(void);
/*Função que lê a opção de filtro. Retorna o número inteiro lido.*/

void checkFileName(FILE *filePointer);
/*Função que checa se o arquivo existe. Recebe como parâmetro um ponteiro para o arquivo. Se  o
arquivo não existir, o programa é abortado.*/

void checkFileExtension(char *fileName);
/*Função que checa a extensão do  arquivo. Recebe  como  parâmetro  o  nome  do  arquivo. Se  a
extensão do arquivo não for '.bmp', o programa é abortado.*/

void checkFileSignature(FILE *filePointer);
/*Função que checa a assinatura do arquivo. Recebe como parâmetro o um ponteiro para o
arquivo. Se a assinatura for difrente de "BM", o programa é abortado.*/

int getTrashNumber(int width);
/*Função que calcula o quanto de "lixo" é colocado em cada linha da área de dados  do  arquivo.
Recebe como parâmetro a largura da imagem. Retorna o tamanho do lixo calculado.*/

file_data *loadOriginalFileData(FILE *filePointer);
/*Função que lê o arquivo bmp e carrega seus dados em  uma  estrutura.  Recebe  como  par�metro
um ponteiro para o arquivo. Retorna o endere�o em que a estutura foi armazenada.*/

file_data *loadNewFileData(file_data *originalFileData, int option);
/*Função que carrega os dados no novo arquivo  em  uma  estrutura.  Recebe  como  parâmetros  o
endereço da estrutura do arquivo original e o número da opção  de  filtro.  Retorna  o  enderço
da estrutura em que os dados do novo arquivo foram armazenados.*/

char *getNewFileName(char *originalFileName, int option);
/*Função que determina e aloca dinamicamente o nome do novo  arquivo.  Recebe  como  parâmetros
o endereço do nome do arquivo original e a opção de filtro. Retorna o endereço em  que  o  novo
nome foi armazenado.*/

void writeNewFile(FILE *newFilePointer, file_data *newFileData);
/*Função que escreve os dados binários no novo arquvio. Recebe como parâetros  um ponteiro  para
o novo arquivo e o endereço da estrutura em que os dados do  novo  arquivo  estão  armazenados.*/

void printData(file_data *originalFileData, file_data *newFileData, char *newFileName);
/*Função que imprime na saída padrão informações sobre o cabeçalho, mapa  de  bits,  paleta  de
cores e área de dados das estruturas dos dois arquivos. Recebe como parâmetros os endereços das
estruturas do  antigo e do novo arquivo, respectivamente, e o endereço do nome do novo arquivo.*/

void freeData(file_data *originalFileData, file_data *newFileData);
/*Função que libera o espaço alocado dinamicamente para as estruturas.  Recebe como  parâmetros
os endereços das estruturas do antigo e novo arquivo, respectivamente.*/


int main(int argc, char *argv[]){

    //Leitura e Armazenamento do Nome do Arquivo Original e da Opção de Filtro:
    char *originalFileName = readString();
    int option = readOption();

    //Abertura do Arquivo Original:
    FILE *originalFilePointer = NULL;
    originalFilePointer = fopen(originalFileName, "rb");

    //Checagem de Possíveis Erros com o Arquivo Original:
    checkFileName(originalFilePointer);
    checkFileExtension(originalFileName);
    checkFileSignature(originalFilePointer);

    //Carregamento dos Dados do Arquivo Original e do Novo Arquivo em Estruturas:
    file_data *originalFileData = loadOriginalFileData(originalFilePointer);
    file_data *newFileData = loadNewFileData(originalFileData, option);

    //Determinação do Nome do Novo Arquivo:
    char *newFileName = getNewFileName(originalFileName, option);

    //Abertura do Novo Arquivo:
    FILE *newFilePointer = NULL;
    newFilePointer = fopen(newFileName, "wb");

    //Escrita de Dados Binários no Novo Arquivo:
    writeNewFile(newFilePointer, newFileData);

    //Impressão de Informações na Saída Padrão:
    printData(originalFileData, newFileData, newFileName);

    //Liberação de Memória Alocada e Fechamento dos Arquivos:
    freeData(originalFileData, newFileData);
    free(originalFileName);
    free(newFileName);
    fclose(originalFilePointer);
    fclose(newFilePointer);

    return 0;
}

char *readString(void){
    char *string = NULL;
    int character = 0, counter = 0;
    while(counter == 0 && character < 30) { character = fgetc(stdin); }
    do{
        string = (char *) realloc(string, (counter+1) * sizeof(char));
        string[counter++] = (char) character;
        character = fgetc(stdin);
    }while(character != '\n' && character != '\r');
    string = (char *) realloc(string, (counter+1) * sizeof(char));
    string[counter] = '\0';
    return string;
}

int readOption(void){
    int option;
    scanf("%d", &option);
    return option;
}

void checkFileName (FILE *filePointer){
    if(filePointer == NULL){
        printf("Erro no arquivo\n");
        exit(NONEXISTENT_FILE);
    }
    return;
}

void checkFileExtension(char *fileName){
    regex_t regex;
    if(regcomp(&regex, ".bmp+$", REG_EXTENDED)){
        printf("Erro de compilação da expressão regular\n");
        exit(REG_COMP_FAILURE);
    }
    if(regexec(&regex, fileName, 0, NULL, 0)){
        printf("Arquivo nao eh do formato BMP\n");
        exit(NO_BMP_FILE);
    }
    regfree(&regex);
    return;
}

void checkFileSignature(FILE *filePointer){
    char signature[2];
    fread(signature, BYTE_SIZE, 2, filePointer);
    if(memcmp(signature, "BM", 2) != 0){
        printf("Arquivo nao eh do formato BMP\n");
        exit(NO_BMP_FILE);
    }
    return;
}

int getTrashNumber(int width){
    int trashNumber = 0;
    while(width % 4 != 0){
        width += 1;
        trashNumber += 1;
    }
    return trashNumber;
}

file_data *loadOriginalFileData(FILE *filePointer){
    file_data *originalFileData = malloc(1 * sizeof(file_data));

    fseek(filePointer, 0, SEEK_SET);

    //Leitura e Armazenamento do Cabeçalho do Arquivo:
    originalFileData->fileHeader = (header *) malloc(1 * sizeof(header));
    originalFileData->fileHeader->signature = (char *) calloc(3, sizeof(char));
    fread(originalFileData->fileHeader->signature, BYTE_SIZE, 2, filePointer);
    fread(&originalFileData->fileHeader->fileSize, sizeof(int), 1, filePointer);
    fread(&originalFileData->fileHeader->reserved, sizeof(int), 1, filePointer);
    fread(&originalFileData->fileHeader->deslocation, sizeof(int), 1, filePointer);

    //Leitura e Armazenamento do Cabeçalho do Mapa de Bits:
    originalFileData->bitsMapHeader = (bits_map *) malloc(1 * sizeof(bits_map));
    fread(&originalFileData->bitsMapHeader->headerSize, sizeof(int), 1, filePointer);
    fread(&originalFileData->bitsMapHeader->width, sizeof(int), 1, filePointer);
    fread(&originalFileData->bitsMapHeader->height, sizeof(int), 1, filePointer);
    fread(&originalFileData->bitsMapHeader->flatsNumber, BYTE_SIZE, 2, filePointer);
    fread(&originalFileData->bitsMapHeader->bitPerPixel, BYTE_SIZE, 2, filePointer);
    fread(&originalFileData->bitsMapHeader->compression, sizeof(int), 1, filePointer);
    fread(&originalFileData->bitsMapHeader->imageSize, sizeof(int), 1, filePointer);
    fread(&originalFileData->bitsMapHeader->horizontalResolution, sizeof(int), 1, filePointer);
    fread(&originalFileData->bitsMapHeader->verticalResolution, sizeof(int), 1, filePointer);
    fread(&originalFileData->bitsMapHeader->totalColors, BYTE_SIZE, 4, filePointer);
    fread(&originalFileData->bitsMapHeader->importantColors, BYTE_SIZE, 4, filePointer);

    //Leitura e Armazenamento da Paleta de Cores:
    originalFileData->colorsPallete = (pallete *) malloc(BITMAP_COLORS * sizeof(pallete));
    for(int i = 0; i < BITMAP_COLORS; i++){
        fread(&originalFileData->colorsPallete[i].blue, BYTE_SIZE, 1, filePointer);
        fread(&originalFileData->colorsPallete[i].green, BYTE_SIZE, 1, filePointer);
        fread(&originalFileData->colorsPallete[i].red, BYTE_SIZE, 1, filePointer);
        fread(&originalFileData->colorsPallete[i].reserved, BYTE_SIZE, 1, filePointer);
    }

    //Leitura e Armazenamento da Área de Dados do Arquivo:
    originalFileData->data = (data_area *) malloc(1 * sizeof(data_area));
    int height = originalFileData->bitsMapHeader->height;
    int width = originalFileData->bitsMapHeader->width;
    int trashNumber = getTrashNumber(width);
    short **matrixData = calloc(height, sizeof(short *));
    long *lineSum = calloc(height, sizeof(long));
    for(int i = (height - 1); i >= 0; i--){
        matrixData[i] = (short *) calloc(width, sizeof(short));
        lineSum[i] = 0;
        for(int j = 0; j < (width); j++){
            fread(&matrixData[i][j], BYTE_SIZE, 1, filePointer);
            lineSum[i] = lineSum[i] + matrixData[i][j];
        }
        if(trashNumber != 0){
            char temporaryBuffer[3];
            fread(&temporaryBuffer, BYTE_SIZE, trashNumber, filePointer);
            lineSum[i] = lineSum[i] - trashNumber;
        }
    }
    originalFileData->data->matrixData = matrixData;
    originalFileData->data->lineSum = lineSum;
    originalFileData->data->trashNumber = trashNumber;

    return originalFileData;
}

file_data *loadNewFileData(file_data *originalFileData, int option){
    file_data *newFileData = malloc(1 * sizeof(file_data));

    //Cópia dos Cabeçalhos do Arquivo Original:
    newFileData->bitsMapHeader = originalFileData->bitsMapHeader;
    newFileData->fileHeader = originalFileData->fileHeader;

    //Determinação de Nova Paleta de Cores com base na opção desejada:
    newFileData->colorsPallete = (pallete *) malloc(BITMAP_COLORS * sizeof(pallete));
    if(option == NEGATIVE){
        for(int i = 0; i < BITMAP_COLORS; i++){
            newFileData->colorsPallete[i].red = fabs(originalFileData->colorsPallete[i].red - 255);
            newFileData->colorsPallete[i].green = fabs(originalFileData->colorsPallete[i].green - 255);
            newFileData->colorsPallete[i].blue = fabs(originalFileData->colorsPallete[i].blue - 255);
            newFileData->colorsPallete[i].reserved = originalFileData->colorsPallete[i].reserved;
        }
    }
    else if(option == BLACK_AND_WHITE){
        int average = 0;
        for(int i = 0; i < BITMAP_COLORS; i++){
            average = (originalFileData->colorsPallete[i].red + originalFileData->colorsPallete[i].green + originalFileData->colorsPallete[i].blue) / 3;
            newFileData->colorsPallete[i].red = average;
            newFileData->colorsPallete[i].green = average;
            newFileData->colorsPallete[i].blue = average;
            newFileData->colorsPallete[i].reserved = originalFileData->colorsPallete[i].reserved;
        }
    }
    else{
        printf("Opção Inválida!\n");
        exit(INVALID_OPTION);
    }

    //Cópia da Área de Dados do Arquivo:
    newFileData->data = originalFileData->data;

    return newFileData;
}

char *getNewFileName(char *originalFileName, int option){
    char *newFileName = NULL;
    int i;
    for(i = 0; originalFileName[i] != '.'; i++){
        newFileName = (char *) realloc(newFileName, (i+1) * sizeof(char));
        newFileName[i] = originalFileName[i];
    }
    newFileName = (char *) realloc(newFileName, (i+1) * sizeof(char));
    newFileName[i] = '\0';
    switch(option){
        case 1:
            newFileName = (char *) realloc(newFileName, i + 15);
            strcat(newFileName, "Negativo.bmp\0");
            break;
        case 2:
            newFileName = (char *) realloc(newFileName, i + 18);
            strcat(newFileName, "PretoBranco.bmp\0");
            break;
        default:
            break;
    }
    return newFileName;
}

void writeNewFile(FILE *newFilePointer, file_data *newFileData){
    fseek(newFilePointer, 0, SEEK_SET);

    //Escrita do Cabeçalho do Novo Arquivo:
    fwrite(newFileData->fileHeader->signature, BYTE_SIZE, 2, newFilePointer);
    fwrite(&newFileData->fileHeader->fileSize, sizeof(int), 1, newFilePointer);
    fwrite(&newFileData->fileHeader->reserved, sizeof(int), 1, newFilePointer);
    fwrite(&newFileData->fileHeader->deslocation, sizeof(int), 1, newFilePointer);

    //Escrita do Cabeçalho do Mapa de bits:
    fwrite(&newFileData->bitsMapHeader->headerSize, sizeof(int), 1, newFilePointer);
    fwrite(&newFileData->bitsMapHeader->width, sizeof(int), 1, newFilePointer);
    fwrite(&newFileData->bitsMapHeader->height, sizeof(int), 1, newFilePointer);
    fwrite(&newFileData->bitsMapHeader->flatsNumber, BYTE_SIZE, 2, newFilePointer);
    fwrite(&newFileData->bitsMapHeader->bitPerPixel, BYTE_SIZE, 2, newFilePointer);
    fwrite(&newFileData->bitsMapHeader->compression, sizeof(int), 1, newFilePointer);
    fwrite(&newFileData->bitsMapHeader->imageSize, sizeof(int), 1, newFilePointer);
    fwrite(&newFileData->bitsMapHeader->horizontalResolution, sizeof(int), 1, newFilePointer);
    fwrite(&newFileData->bitsMapHeader->verticalResolution, sizeof(int), 1, newFilePointer);
    fwrite(&newFileData->bitsMapHeader->totalColors, BYTE_SIZE, 4, newFilePointer);
    fwrite(&newFileData->bitsMapHeader->importantColors, BYTE_SIZE, 4, newFilePointer);

    //Escrita da Paleta de Cores:
    for(int i = 0; i < BITMAP_COLORS; i++){
        fwrite(&newFileData->colorsPallete[i].blue, BYTE_SIZE, 1, newFilePointer);
        fwrite(&newFileData->colorsPallete[i].green, BYTE_SIZE, 1, newFilePointer);
        fwrite(&newFileData->colorsPallete[i].red, BYTE_SIZE, 1, newFilePointer);
        fwrite(&newFileData->colorsPallete[i].reserved, BYTE_SIZE, 1, newFilePointer);
    }

    //Escrita da Área de Dados:
    int width = newFileData->bitsMapHeader->width;
    int height = newFileData->bitsMapHeader->height;
    int trashNumber = newFileData->data->trashNumber;
    for(int i = height - 1; i >= 0; i--){
        for(int j = 0; j < width; j++){
            fwrite(&newFileData->data->matrixData[i][j], BYTE_SIZE, 1, newFilePointer);
        }
        for(int j = 0; j < trashNumber; j++){
            fwrite("$", BYTE_SIZE, 1, newFilePointer);
        }
    }

    return;
}

void printData(file_data *originalFileData, file_data *newFileData, char *newFileName){
    //Impressão de Dados Gerais:
    printf("CABECALHO:\n");
    printf("Iniciais: %s\n", originalFileData->fileHeader->signature);
    printf("Tamanho do arquivo: %d\n", originalFileData->fileHeader->fileSize);
    printf("Reservado: %d\n", originalFileData->fileHeader->reserved);
    printf("Deslocamento, em bytes, para o inicio da area de dados: %d\n", originalFileData->fileHeader->deslocation);
    printf("Tamanho em bytes do segundo cabecalho: %d\n", originalFileData->bitsMapHeader->headerSize);
    printf("Resolucao: %d x %d\n", originalFileData->bitsMapHeader->width, originalFileData->bitsMapHeader->height);
    printf("Numero de planos: %d\n", originalFileData->bitsMapHeader->flatsNumber);
    printf("Bits por pixel: %d\n", originalFileData->bitsMapHeader->bitPerPixel);
    printf("Compressao usada: %d\n", originalFileData->bitsMapHeader->compression);
    printf("Tamanho imagem: %d\n", originalFileData->bitsMapHeader->imageSize);
    printf("Resolucao horizontal: %d pixel por metro\n", originalFileData->bitsMapHeader->horizontalResolution);
    printf("Resolucao Vertical: %d pixel por metro\n", originalFileData->bitsMapHeader->verticalResolution);
    printf("Numero de cores usadas: %d\n", originalFileData->bitsMapHeader->totalColors);
    printf("Numero de cores importantes: %d\n", originalFileData->bitsMapHeader->importantColors);

    //Impressão de Dados da Paleta Original:
    printf("PALETA ORIGINAL:\n");
    for(int i = 0; i < BITMAP_COLORS; i++){
        printf("Paleta[%d]:", i);
        printf(" R:%d", originalFileData->colorsPallete[i].red);
        printf(" G:%d", originalFileData->colorsPallete[i].green);
        printf(" B:%d\n", originalFileData->colorsPallete[i].blue);
    }

    //Impressão de Dados da Paleta Nova:
    printf("PALETA NOVA:\n");
    for(int i = 0; i < BITMAP_COLORS; i++){
        printf("Paleta[%d]:", i);
        printf(" R:%d", newFileData->colorsPallete[i].red);
        printf(" G:%d", newFileData->colorsPallete[i].green);
        printf(" B:%d\n", newFileData->colorsPallete[i].blue);
    }
    for(int i = 0; i < originalFileData->bitsMapHeader->height; i++){
        printf("Soma linha %d: %ld\n", i, originalFileData->data->lineSum[i]);
    }
    printf("%s\n", newFileName);
}

void freeData(file_data *originalFileData, file_data *newFileData){
    for(int i = 0; i < originalFileData->bitsMapHeader->height; i++){
        free(originalFileData->data->matrixData[i]);
    }
    free(originalFileData->data->matrixData);
    free(originalFileData->data->lineSum);
    free(originalFileData->data);
    free(originalFileData->colorsPallete);
    free(newFileData->colorsPallete);
    free(originalFileData->bitsMapHeader);
    free(originalFileData->fileHeader->signature);
    free(originalFileData->fileHeader);
    free(originalFileData);
    free(newFileData);
    return;
}
