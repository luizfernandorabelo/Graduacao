#ifndef __READ_INPUTS_H__
    #define __READ_INPUTS_H__

    #include <iostream>

    using std::cout;
    using std::cin;

    /* Funções para garantir a validação dos dados entrados pelo usuário. Implementações no arquivo readInputs.cpp */

    int read_number_of_vertices(FILE *stream);
    double read_connection_probability(FILE *stream);

#endif