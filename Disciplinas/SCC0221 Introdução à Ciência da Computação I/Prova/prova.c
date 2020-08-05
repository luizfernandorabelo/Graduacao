#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define bool char
#define TRUE 1
#define FALSE 0

#define FILE_OPEN_FAILURE -1
#define REG_COMP_FAILURE -2

//Protótipos de Funções Complementares (em Ordem Alfabética):
void freeStrings(char *file_name, char *pattern1, char *pattern2, char *pattern3, char *word);
char *getLongestPatternTwoWord(char *pattern2, char **words_list, int size_of_words_list);
char *getLongestWord(char **words_list, int size_of_words_list);
char *getMostSimilarWord(char *word, char **words_list, int size_of_words_list);
int getPalindromeOccurrence(char **words_list, int size_of_words_list);
int getPatternOneOccurrence(char *pattern1, char **words_list, int size_of_words_list);
char **getPatternThreeWordsList(char *pattern3, char **words_list, int size_of_words_list, int *size_of_pattern3_list);
char *getShortestWord(char **words_list, int size_of_words_list);
int integerComparison(const void *a, const void *b);
char **loadWordsList(FILE *fp, int *size_of_words_list);
char *readString(FILE *stream);
int stringComparison(const void *a, const void *b);
void unloadWordsList(char **words_list, int size_of_words_list);

int main(int argc, char *argv[]){
    
    //Leitura e Armazenamento das Entradas Recebidas pela STDIN:
    char *file_name = readString(stdin);
    char *pattern1 = readString(stdin);
    char *pattern2 = readString(stdin);
    char *pattern3 = readString(stdin);
    char *word = readString(stdin);

    //Abertura do Arquivo de Dados a ser Manipulado:
    FILE *file_pointer = NULL;
    file_pointer = fopen(file_name, "r"); 
    
    //Verificação de Possível Erro de Abertura de Arquivo:
    if(file_pointer == NULL){
        printf("Falha na abertura do arquivo.\n");
        exit(FILE_OPEN_FAILURE);
    }
    
    //"Carregamento" das Palavras do Arquivo em uma Matriz e Impressão do Número de Palavras Contidas no Mesmo:
    int size_of_file_words_list = 0;
    char **file_words_list = loadWordsList(file_pointer, &size_of_file_words_list);
    printf("%d\n", size_of_file_words_list);

    //Determinação e Impressão da Palavra mais Curta:
    char *shortest_word = getShortestWord(file_words_list, size_of_file_words_list);
    printf("%s\n", shortest_word);
    
    //Determinação e Impressão da Palavra mais Longa:
    char *longest_word = getLongestWord(file_words_list, size_of_file_words_list);
    printf("%s\n", longest_word);

    //Determinação e Impressão do Número de Ocorrências do Padrão 1:
    int pattern1_occurrence = getPatternOneOccurrence(pattern1, file_words_list, size_of_file_words_list);
    printf("%d\n", pattern1_occurrence);

    //Determinação e Impressão do Número de Palíndromos:
    int palindrome_occurrence = getPalindromeOccurrence(file_words_list, size_of_file_words_list);
    printf("%d\n", palindrome_occurrence);

    //Determinação e Impressão da Palavra mais Longa que Segue o Padrão 2: 
    char *longest_pattern2_word = getLongestPatternTwoWord(pattern2, file_words_list, size_of_file_words_list);
    printf("%s\n", longest_pattern2_word);

    //Determinação e Impressão da Lista Ordenada de Palavras que Seguem o Padrão 3:
    int pattern3_words_list_size = 0;
    char **pattern3_words_list = getPatternThreeWordsList(pattern3, file_words_list, size_of_file_words_list, &pattern3_words_list_size);
    for(int i = 0; i < pattern3_words_list_size; i++) { printf("%s\n", pattern3_words_list[i]); }

    //Determinação e Impressão da Palavra mais Similar:
    char *similar_word = getMostSimilarWord(word, file_words_list, size_of_file_words_list);
    printf("%s\n", similar_word);

    //Fechamento do Arquivo:
    fclose(file_pointer);

    //Liberação do Restante Memória Alocada:
    unloadWordsList(file_words_list, size_of_file_words_list);
    unloadWordsList(pattern3_words_list, pattern3_words_list_size);
    freeStrings(file_name, pattern1, pattern2, pattern3, word);

    //Fim da Execução com Sucesso: 
    return EXIT_SUCCESS;
}


char *readString(FILE *stream){
    //Declaração e Inicialização de Variáveis:
    char *string = NULL;
    int counter = 0, character = 0;
    //"Limpeza" do buffer (para evitar caracteres como '\r' e '\n'):
    while(counter == 0 && character <= 31 && character >= 0){ character = fgetc(stream); }
    //Leitura e Armazenamento da String:
    do{
        string = (char *) realloc(string, (counter+1) * sizeof(char));
        string[counter++] = (char) character;
        character = fgetc(stream);
    }while(character != '\n' && character != EOF);
    //Adição do Terminador de Strings '\0':
    string = (char *) realloc(string, (counter+1) * sizeof(char));
    string[counter] = '\0';
    //Retorno do Endereço de Memória em que a String foi Alocada:
    return string;
}

char **loadWordsList(FILE *fp, int *size_of_file_words_list){
    //Declaração e Inicialização de Variáveis:
    int lines_counter = 0;
    char *string = NULL, **file_words_list = NULL;
    //Armazenamento da Lista de Palavras:
    while(feof(fp) == FALSE){
        string = readString(fp);
        if(strlen(string) > 0 && string[0] != EOF){ //se for uma string válida:
            file_words_list = (char **) realloc(file_words_list, (lines_counter+1) * sizeof(char *));
            file_words_list[lines_counter++] = string;
        }
        else{ //mas se não for uma string válida:
            free(string);
        }
    }
    //Passagem por Referência do Tamanho da Lista:
    *size_of_file_words_list = lines_counter;
    //Retorno do Endereço de Memóri'a em que a Lista foi Alocada:
    return file_words_list;
}

int stringComparison(const void *a, const void *b){
    return (strcmp(*(const char **)a, *(const char **)b));
}

int integerComparison(const void *a, const void *b){
    return (*(const int *)a - *(const int *)b);
}

char *getShortestWord(char **words_list, int size_of_words_list){
    //Inicialização da Menor Palavra como sendo a de Primeiro Índice:
    char *shortest = words_list[0];
    //Comparação com Tamanho das Demais Palavras da Lista: 
    for(int i = 1; i < size_of_words_list; i++){
        if(strlen(words_list[i]) < strlen(shortest)){
            shortest = words_list[i];
        }
    }
    //Retorno do Endereço em que a Palavra está Alocada:
    return shortest;
}

char *getLongestWord(char **words_list, int size_of_words_list){
    //Inicialização da Maior Palavra como sendo a de Primiro Índice:
    char *longest = words_list[0];
    //Comparação com o Tamanho das Demais Palavras da Lista:
    for(int i = 1; i < size_of_words_list; i++){
        if(strlen(words_list[i]) > strlen(longest)){
            longest = words_list[i];
        }
    }
    //Retorno do Endereço em que a Palavra está Alocada:
    return longest;
}       

int getPatternOneOccurrence(char *pattern1, char **words_list, int size_of_words_list){
    //Declaração e Inicialização de Variáveis:
    int occurrence = 0;
    regex_t regex;
    //Compilação da Expressão Regular e Tratamento de Possível Erro:
    if(regcomp(&regex, pattern1, REG_EXTENDED) != FALSE){
        printf("Não foi possível compilar expressão regular.\n");
        printf("Padrão não reconhecido: %s\n", pattern1);
        exit(REG_COMP_FAILURE);
    }
    //Contagem do Número de Ocorrências do Padrão na Lista:
    for(int i = 0; i < size_of_words_list; i++){
        if(regexec(&regex, words_list[i], 0, NULL, 0) == FALSE){
            occurrence += 1;
        }
    }
    //Liberação da Compilação da Expressão Regular:
    regfree(&regex);
    return occurrence;
}

int getPalindromeOccurrence(char **words_list, int size_of_words_list){
    //Declaração e Inicialização de Variáveis:
    int occurrence = 0;
    bool flag = FALSE;
    //Contagem do Número de Palíndromos:
    for(int i = 0; i < size_of_words_list; i++){
        for(int j = 0, k = (strlen(words_list[i])-1); j <= k; j++, k--){
            if(words_list[i][j] == words_list[i][k]){ //se as posições correspondentes forem iguais
                flag = TRUE; //a flag è setada como verdadeio
            }
            else{ //mas se alguma das posições correspondentes for diferente 
                flag = FALSE; //a flag é setada como falso
                break; //e deve-se sair do laço de repetição 
            }
        }
        occurrence = (flag == TRUE) ? (occurrence + 1) : occurrence;
        flag = FALSE;
    }
    //Retrono do Número de Ocorrências de Palíndromos: 
    return occurrence;
}

char *getLongestPatternTwoWord(char *pattern2, char **file_words_list, int size_of_file_words_list){
    //Declaração e Inicialização de Variáveis:
    char **pattern2_list = NULL; 
    int pattern2_list_size = 0;
    regex_t regex;
    //Compilação da Expressão Regular e Tratamento de Possível Erro:
    if(regcomp(&regex, pattern2, REG_EXTENDED) != FALSE){
        printf("Não foi possível compilar expressão regular.\n");
        printf("Padrão não reconhecido: %s\n", pattern2);
        exit(REG_COMP_FAILURE);
    }
    //Procura por Todas as Palavra que Seguem o Padrão 2:
    for(int i = 0; i < size_of_file_words_list; i++){
        if(regexec(&regex, file_words_list[i], 0, NULL, 0) == FALSE){
            pattern2_list = (char **) realloc(pattern2_list, (pattern2_list_size+1) * sizeof(char *));
            pattern2_list[pattern2_list_size++] = file_words_list[i];
        }
    }
    //Determinação da Maior Palavra que Segue o Padrão 2:
    char *longest = getLongestWord(pattern2_list, pattern2_list_size);
    //Liberação de Memória Alocada:
    free(pattern2_list);
    regfree(&regex);
    //Retorno do Endereço em que a maior Palavra que Segue o Padrão 2 está Alocada: 
    return longest;
}

char **getPatternThreeWordsList(char *pattern3, char **file_words_list, int size_of_file_words_list, int *size_of_pattern3_words_list){
    //Declaração e Inicialização de Variáveis:
    char **pattern3_words_list = NULL;
    regex_t regex;
    //Compilação de Expressão Regular e Tratamento de Possível Erro:
    if(regcomp(&regex, pattern3, REG_EXTENDED)){
        printf("Não foi possível compilar expressão regular.\n");
        printf("Padrão não reconhecido: %s\n", pattern3);
        exit(REG_COMP_FAILURE);
    }
    //Armazenamento da Nova Lista com as Palavras que Seguem o Padrão 3:
    for(int i = 0; i < size_of_file_words_list; i++){
        if(!regexec(&regex, file_words_list[i], 0, NULL, 0)){
            pattern3_words_list = (char **) realloc(pattern3_words_list, (*size_of_pattern3_words_list+1) * sizeof(char *));
            pattern3_words_list[*size_of_pattern3_words_list] = calloc(strlen(file_words_list[i]) + 1, sizeof(char));
            strcpy(pattern3_words_list[*size_of_pattern3_words_list], file_words_list[i]);
            *size_of_pattern3_words_list = *size_of_pattern3_words_list + 1;
        }
    }
    //Ordenação da Lista de Palavras que Seguem o Padrão 3:
    qsort(pattern3_words_list, *size_of_pattern3_words_list, sizeof(char **), stringComparison);
    //Liberação da Compilação da Expressão Regular:
    regfree(&regex);
    //Retorno do Endereço em que a Lista de Palavras que Seguem o Padrão 3 foi Alocada:
    return pattern3_words_list;
}

char *getMostSimilarWord(char *word, char **file_words_list, int size_of_file_words_list){
    //Declaração e Inicialização de Variáveis:
    int *similarity_per_combination = NULL; 
    int *similarity_per_index = malloc(size_of_file_words_list * sizeof(int));
    for(int i = 0; i < size_of_file_words_list; i++){
        //Determinação de String (maior tamanho) e de Substring (menor tamanho) para a comparação: 
        char *string = NULL, *substring = NULL;
        if(strlen(word) < strlen(file_words_list[i])){
            substring = word;
            string = file_words_list[i];
        }
        else{
            substring = file_words_list[i];
            string = word;
        }
        //Determinação do Número de Combições de Strings com o Tamanho da Substring:
        int combinations_number = strlen(string) - strlen(substring) + 1;
        //Alocação Dinâmica do Vetor que Armazenará os Valores de Similaridade por Combinação:
        similarity_per_combination = (int *) malloc(combinations_number * sizeof(int));
        //Cálculo dos Valores de Similaridade Por Combinação:
        for(int j = 0; j < combinations_number; j++){
            int counter = 0;
            for(int k = 0; k < strlen(substring); k++){
                counter = string[j+k] == substring[k] ? counter + 1 : counter;
            }
            similarity_per_combination[j] = counter;
        }
        //Ordenaçã do Vetro de Similaridade por Combinação e Atribuição de seu Último Valor(maior) ao Vetor de Similaridade por Índice
        qsort(similarity_per_combination, combinations_number, sizeof(int), integerComparison);
        similarity_per_index[i] = similarity_per_combination[combinations_number-1];
        //Liberação de Memória Alocada:
        free(similarity_per_combination);
    }
    //Determinação do Melhor Índice Dentro do Vetro de Similaridade por Índice:
    int best_index = 0;
    for(int i = 0; i < size_of_file_words_list; i++){
        if(similarity_per_index[i] > similarity_per_index[best_index]){ 
            //se for encontrado um valor maior na posição i, o valor do melhor índice é atualizado (recebe i)
            best_index = i;
        }
        else if(similarity_per_index[i] == similarity_per_index[best_index] && strlen(file_words_list[i]) < strlen(file_words_list[best_index])){
            //mas se os valores forem iguais, o melhor índice será atualizado apenas se a palavra em i for menor que a palavra no menor índice
            best_index = i;       
        }
    }
    //Liberação de Memória Alocada para o Vetro de Similaridade por Combinação:
    free(similarity_per_index);
    //Retorno do Endereço da Palavra Mais Similar a Word:
    return file_words_list[best_index];
}

void unloadWordsList(char **words_list, int size_of_words_list){
    //Liberação de Ponteiros Simples:
    for(int i = 0; i < size_of_words_list; i++){
        free(words_list[i]);
    }
    //Liberação de Ponteiro Duplo:
    free(words_list);
    return;
}

void freeStrings(char *file_name, char *pattern1, char *pattern2, char *pattern3, char *word){
    free(file_name);
    free(pattern1);
    free(pattern2);
    free(pattern3);
    free(word);
    return;
}