#ifndef SORTING_H
    #define SORTING_H

    #define COUNTING_SORT 1
    #define RADIX_SORT 2
    #define BUCKET_SORT 3

    #include "PokeDex.h"

    void sortPkdexByAttack(pokemon_t **pkdex, int totalPkmn, int sortingType);

#endif