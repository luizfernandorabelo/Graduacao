#include "binFileManager.h"


bool is_end_of_file(FILE *stream) {
    return feof(stream);
}


int read_int_from_bin_file(FILE *stream) {
    int number = 0;
    fread(&number, sizeof(int), 1, stream);
    return number;
}


float read_float_from_bin_file(FILE *stream){
    float number = 0.0;
    fread(&number, sizeof(float), 1, stream);
    return number;
}


double read_double_from_bin_file(FILE *stream){
    double number = 0.0;
    fread(&number, sizeof(double), 1, stream);
    return number;
}


char read_char_from_bin_file(FILE *stream){
    char character = '\0';
    fread(&character, sizeof(char), 1, stream);
    return character;
}


char *read_string_from_bin_file(FILE *stream, int string_length){
    char *string = calloc(string_length, sizeof(char));
    fread(string, string_length, 1, stream);
    return string;
}


void write_int_to_bin_file(FILE *stream, int *number) {
    fwrite(number, sizeof(int), 1, stream);
}


void write_float_to_bin_file(FILE *stream, float *number) {
    fwrite(number, sizeof(float), 1, stream);
}


void write_double_to_bin_file(FILE *stream, double *number) {
    fwrite(number, sizeof(double), 1, stream);
}


void write_char_to_bin_file(FILE *stream, char *character) {
    fwrite(character, sizeof(char), 1, stream);
}


void write_string_to_bin_file(FILE *stream, char *string, int string_length) {
    fwrite(string, sizeof(char), string_length, stream);
}