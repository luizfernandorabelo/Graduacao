#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "InpReader.h"
#include "BoxList.h"
#include "Util.h"
#include "PokeType.h"
#include "Pokemon.h"
#include "PokeBox.h"
#include "PokeDex.h"
#include "SaveManager.h"
#include "Moves.h"


int main(){   

    //Inicialização do Número Total de Pokemons e da Pokedex:
    int totalPkmn = 0;
    pokemon_t **pkdex = readPkDex(&totalPkmn);

    //Criação da Lista para as Caixas:
    boxlist_t *boxList = boxListCreate();

    //Leitura da Opção e Direcionamento para Operações:
    int option = readOption();

    while(option != EXIT){

        if(option == SHIFT_RIGHT)
            boxListShiftRight(boxList);
        
        else if(option == SHIFT_LEFT)
            boxListShiftLeft(boxList);
        
        else if(option == ADD_EMPTY_BOX)
            boxListAddNewEmptyBox(boxList);
        
        else if(option == REMOVE_BOX)
            boxListRemoveCurrentBox(boxList);
        
        else if(option == ADD_PKMN_START){
            int pokePos = readPos();
            boxListAddPkmnFirstPos(boxList, pkdex[pokePos]);
        }

        else if(option == ADD_PKMN_POS){
            int pokePos = readPos();
            int insertionPos = readPos();
            boxListAddPkmn(boxList, pkdex[pokePos], insertionPos);
        }

        else if(option == REMOVE_PKMN_POS){
            int removalPos = readPos();
            boxListRemovePkmn(boxList, removalPos);
        }
        
        else if(option == PRINT_BOX)
            boxListPrintCurrentBox(boxList);
        
        option = readOption();
    }

    //Liberação de Memória Alocada:
    boxListDelete(&boxList);

    for(int i = 0; i < totalPkmn; ++i)
        free(pkdex[i]);

    free(pkdex);

    return(0);
}