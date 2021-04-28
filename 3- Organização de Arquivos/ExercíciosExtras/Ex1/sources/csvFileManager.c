#include "csvFileManager.h"


bool is_delimiter(char character) {

    /*
        Retorna verdadeiro se o caractere passado for:
            - um delimitador de campo (definido pela macro 'FIELD_DELIMITER') ou
            - um delimitador de registro (quebra de linha ou fim do arquivo)
    */

    if (character == FIELD_DELIMETER || character == '\n' || character == '\r' || character == EOF)
        return true;

    return false;
}


void skip_delimiter(FILE *stream) {
    fseek(stream, 1, SEEK_CUR);
}


bool is_end_of_file(FILE *stream) {
    char character = fgetc(stream);
    if (character == '\n' || character == '\r' || character == EOF)
        return true;
    fseek(stream, -1, SEEK_CUR);
    return false;
}


char *read_header_from_csv_file(FILE *stream){

    char *header = NULL;
    int char_counter = 0;
    char current_character = fgetc(stream);
    
    while (current_character != '\n' && current_character != '\r') {
        header = realloc(header, char_counter + 2);
        header[char_counter++] = current_character;
        current_character = fgetc(stream);
    }

    header[char_counter] = '\0';

    return header;
}


int read_int_from_csv_file(FILE *stream) {

    int number = 0;

    fscanf(stream, "%d", &number);
    skip_delimiter(stream);

    return number;
}


float read_float_from_csv_file(FILE *stream) {

    float number = 0.0;

    fscanf(stream, "%f", &number);
    skip_delimiter(stream);

    return number;
}


double read_double_from_csv_file(FILE *stream) {

    double number = 0.0;

    fscanf(stream, "%lf", &number);
    skip_delimiter(stream);

    return number;
}


char read_char_from_csv_file(FILE *stream) {

    char character = '\0';

    fscanf(stream, "%c", &character);
    skip_delimiter(stream);

    return character;
}


char *read_string_from_csv_file(FILE *stream) {

    char *string = calloc(1, sizeof(char));
    int char_counter = 0;
    char current_character = fgetc(stream);

    while (!is_delimiter(current_character)) {
        string = realloc(string, char_counter + 2);
        string[char_counter++] = current_character;
        current_character = fgetc(stream);
    }

    string[char_counter] = '\0';

    return string;
}


void write_int_to_csv_file(FILE *stream, int number) {
    fprintf(stream, "%d", number);
}


void write_float_to_csv_file(FILE *stream, float number) {
    fprintf(stream, "%f", number);
}


void write_double_to_csv_file(FILE *stream, double number) {
    fprintf(stream, "%lf", number);
}


void write_char_to_csv_file(FILE *stream, char character) {
    fprintf(stream, "%c", character);
}


void write_string_to_csv_file(FILE *stream, char *string) {
    fprintf(stream, "%s", string);
}