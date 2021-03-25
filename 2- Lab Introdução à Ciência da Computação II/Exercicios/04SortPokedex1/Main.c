#include <stdio.h>
#include <stdlib.h>

#include "PokeType.h"
#include "Pokemon.h"
#include "PokeDex.h"

#include "Sorting.h"


void printAllPkmon(pokemon_t **pkdex, int totalPkmn){
    for(int i = 0; i < totalPkmn; i++){
        printPokemon(pkdex[i]);
        free(pkdex[i]);
    }
    free(pkdex);
}


int main(){

    int sortingType; scanf("%d", &sortingType);
    char attribute[16]; scanf("%s", attribute);
    char fileName[16]; scanf("%s", fileName);
    int totalPkmn = 0;

    pokemon_t **pkdex = readPkDex(&totalPkmn, fileName);

    sortPkdexByAttribute(pkdex, totalPkmn, TIM_SORT, attribute);

    printAllPkmon(pkdex, totalPkmn); 

	return 0;
}