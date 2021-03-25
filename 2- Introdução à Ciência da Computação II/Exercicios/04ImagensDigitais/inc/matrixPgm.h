#ifndef MATRIX_PGM
    #define MATRIX_PGM

    #include <stdio.h>

    //Macro Valor Máximo que um Pixel pode assumir
    #define MAX_VALUE 255

    //Macros para Formato da Impressão da Matriz:
    #define DEFAULT_FORMAT 1 
    #define PGM_FORMAT 2

    typedef struct matrix_ MATRIX;

    MATRIX *matrix_alocate(int size);
    void matrix_free(MATRIX **matrix);
    void matrix_load_random_numbers(MATRIX *matrix, int seed);
    void matrix_change_numbers(MATRIX *matrix, int rowStart, int colStart, int seed);
    void matrix_copy(MATRIX *matrixDest, MATRIX *matrixOrign);
    void matrix_print(MATRIX *matrix, FILE *fp, int writeFormat);

#endif