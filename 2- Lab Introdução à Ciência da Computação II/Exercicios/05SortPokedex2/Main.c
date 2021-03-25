#include <stdio.h>
#include <stdlib.h>

#include "PokeType.h"
#include "Pokemon.h"
#include "PokeDex.h"

#include "Sorting.h"


int main(){

    //Leitura do Tipo de Ordenação e do Nome do Arquivo CSV:
    int sortingType; scanf("%d", &sortingType);
    char fileName[16]; scanf("%s", fileName);
    
    //Inicialização do Número Total de Pokemons:
    int totalPkmn = 0;

    //Carregamento da Pokedex para a Memória:
    pokemon_t **pkdex = readPkDex(&totalPkmn, fileName);

    //Ordenação dos Pokemons por Ataque:
    sortPkdexByAttack(pkdex, totalPkmn, sortingType);

    //Impressão dos Pokemons e Liberação de Memória Alocada:
    for(int i = 0; i < totalPkmn; i++){
        printPokemon(pkdex[i]);
        free(pkdex[i]);
    }

    free(pkdex);

	return 0;
}