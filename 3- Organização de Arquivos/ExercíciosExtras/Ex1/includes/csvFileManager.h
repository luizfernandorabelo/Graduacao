#ifndef __CSV_MANAGER_H__
    #define __CSV_MANAGR_H__

    #ifndef my_boolean_type
        #define my_boolean_type

        #define bool int
        #define true 1
        #define false 0
    #endif

    #define FIELD_DELIMETER ','

    #include <stdio.h>
    #include <stdlib.h>

    char *read_header_from_csv_file(FILE *stream);
    bool is_end_of_file(FILE *stream);

    int read_int_from_csv_file(FILE *stream);
    float read_float_from_csv_file(FILE *stream);
    double read_double_from_csv_file(FILE *stream);
    char read_char_from_csv_file(FILE *stream);
    char *read_string_from_csv_file(FILE *stream);

    void write_int_to_csv_file(FILE *stream, int number);
    void write_float_to_csv_file(FILE *stream, float number);
    void write_double_to_csv_file(FILE *stream, double number);
    void write_char_to_csv_file(FILE *stream, char character);
    void write_string_to_csv_file(FILE *stream, char *string);

#endif