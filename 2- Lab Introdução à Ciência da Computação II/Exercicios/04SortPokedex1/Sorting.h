#ifndef SORTING_H
    #define SORTING_H

    #define QUICK_SORT 1
    #define HEAP_SORT 2
    #define TIM_SORT 3

    #define PKDEX_NUMBER "dexNumber"
    #define ATTACK "atk"
    #define MAIN_TYPE "mainType"

    #include "PokeDex.h"

    void sortPkdexByAttribute(pokemon_t **pkdex, int totalPkmn, int sortingType, char *attribute);

#endif