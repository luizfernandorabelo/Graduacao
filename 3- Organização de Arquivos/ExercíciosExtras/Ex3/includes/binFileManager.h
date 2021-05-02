#ifndef __BIN_MANAGER_H__
    #define __BIN_MANAGR_H__

    #ifndef my_boolean_type
        #define my_boolean_type

        #define bool int
        #define true 1
        #define false 0
    #endif

    #include <stdio.h>
    #include <stdlib.h>

    bool is_end_of_file(FILE *stream);

    int read_int_from_bin_file(FILE *stream);
    float read_float_from_bin_file(FILE *stream);
    double read_double_from_bin_file(FILE *stream);
    char read_char_from_bin_file(FILE *stream);
    char *read_string_from_bin_file(FILE *stream, int string_length);

    void write_int_to_bin_file(FILE *stream, int *number);
    void write_float_to_bin_file(FILE *stream, float *number);
    void write_double_to_bin_file(FILE *stream, double *number);
    void write_char_to_bin_file(FILE *stream, char *character);
    void write_string_to_bin_file(FILE *stream, char *string, int string_length);

#endif