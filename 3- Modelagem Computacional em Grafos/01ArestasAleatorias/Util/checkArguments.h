#ifndef __CHECK_ARGUMENTS_H__
    #define __CHECK_ARGUMENTS_H__

    /* Funções para checar o número e valores dos argumentos passados pela linha de comando a fim de evitar inputs inválidos */
    /* Se qualquer irregularidade for encontrada, o programa é abortado. Implementações no arquivo checkArguments.c */

    void check_argument_number(int argc);
    void check_argument_values(int numberOfNodes, double connectionProbability);

#endif