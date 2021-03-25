#ifndef BOX_LIST_H
#define BOX_LIST_H

#include "Pokemon.h"

typedef struct box_list_ boxlist_t;

boxlist_t *boxListCreate();
void boxListDelete(boxlist_t **boxList);
void boxListShiftLeft(boxlist_t *boxList);
void boxListShiftRight(boxlist_t *boxList);
void boxListAddNewEmptyBox(boxlist_t *boxList);
void boxListRemoveCurrentBox(boxlist_t *boxList);
void boxListAddPkmnFirstPos(boxlist_t *boxList, pokemon_t *pkmn);
void boxListAddPkmn(boxlist_t *boxList, pokemon_t *pkmn, int position);
void boxListRemovePkmn(boxlist_t *boxList, int position);
void boxListPrintCurrentBox(boxlist_t *boxList);

#endif