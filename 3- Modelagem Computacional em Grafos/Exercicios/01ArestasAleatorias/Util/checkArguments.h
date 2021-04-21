#ifndef __CHECK_ARGUMENTS__H
    #define __CHECK_ARGUMENTS_H

    /* Funções para checar o número e valores dos argumentos passados pela linha de comando a fim de evitar inputs inválidos */
    /* Se qualquer irregularidade for encontrada, o programa é abortado. Implementações no arquivo checkArguments.c */

    void checkArgumentNumber(int argc);
    void checkArgumentValues(int numberOfNodes, double connectionProbability);

#endif