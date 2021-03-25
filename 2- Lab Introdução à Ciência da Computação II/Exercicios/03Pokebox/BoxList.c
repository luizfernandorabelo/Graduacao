#include "BoxList.h"
#include "PokeBox.h"

typedef struct node_ NODE;

struct node_{
    pokebox_t box;
    int totalPkmn;
    int currPkmn;
    NODE *previous;
    NODE *next;
};

struct box_list_{
    NODE *begin;
    NODE *end;
    NODE *currBox;
};

void setBoxNull(pokebox_t box){
    for(int i = 0; i < BOXSIZE; i++)
        box[i] = NULL;        
}

NODE *createNewNode(){
    NODE *node = malloc(sizeof(NODE));
    if(node != NULL){
        node->currPkmn = 0;
        node->totalPkmn = 0;
        node->previous = node;
        node->next = node;
        setBoxNull(node->box);
        
    }
    return(node);
}

boxlist_t *boxListCreate(){
    boxlist_t *boxList = malloc(sizeof(boxlist_t));
    if(boxList != NULL){
        NODE *firstNode = createNewNode();
        boxList->begin = firstNode;
        boxList->end = firstNode;
        boxList->currBox = firstNode;
    }
    return(boxList);
}

void boxListDelete(boxlist_t **boxList){
    if(*boxList != NULL){ 
        (*boxList)->currBox = (*boxList)->begin;
        while((*boxList)->currBox != (*boxList)->end){
            (*boxList)->currBox = (*boxList)->currBox->next;
            free((*boxList)->currBox->previous);
        }
        free((*boxList)->end);
        free(*boxList); *boxList = NULL;
    }
}

void boxListShiftLeft(boxlist_t *boxList){
    if(boxList != NULL)
        boxList->currBox = boxList->currBox->previous;
}

void boxListShiftRight(boxlist_t *boxList){
    if(boxList != NULL){
        boxList->currBox = boxList->currBox->next;
    }
}

void boxListAddNewEmptyBox(boxlist_t *boxList){
    NODE *newNode = createNewNode();
    newNode->previous = boxList->end;
    newNode->next = boxList->begin;
    boxList->end->next = newNode;
    boxList->begin->previous = newNode;
    boxList->end = newNode;
}
 
void boxListRemoveCurrentBox(boxlist_t *boxList){
    if(boxList->currBox == boxList->begin){
        boxList->currBox->currPkmn = 0;
        boxList->currBox->totalPkmn = 0;
        setBoxNull(boxList->currBox->box);
    }
    else{
        NODE *aux = boxList->currBox;
        aux->previous->next = aux->next;
        aux->next->previous = aux->previous;
        boxList->currBox = aux->next;
        free(aux);
    }
}

void boxListAddPkmnFirstPos(boxlist_t *boxList, pokemon_t *pkmn){
    if(boxList != NULL){
        int pos = boxList->currBox->currPkmn;
        while(boxList->currBox->box[pos] != NULL && pos < BOXSIZE) 
            pos++;
        if(pos < BOXSIZE){
            boxList->currBox->box[pos] = pkmn;
            boxList->currBox->currPkmn = pos + 1;
        }
        else{
            boxList->currBox = boxList->currBox->next;
            boxListAddPkmnFirstPos(boxList, pkmn);
        }
    }
}

void boxListAddPkmn(boxlist_t *boxList, pokemon_t *pkmn, int pos){
    if(boxList != NULL){
        int currPkmn = pos;
        while(boxList->currBox->box[currPkmn] != NULL && currPkmn < BOXSIZE) 
            currPkmn++;
        if(currPkmn < BOXSIZE){
            boxList->currBox->box[currPkmn] = pkmn;
        }
        else{
            boxList->currBox = boxList->currBox->next;
            boxListAddPkmn(boxList, pkmn, 0);
        }
    }
}

void boxListRemovePkmn(boxlist_t *boxList, int pos){
    if(boxList != NULL && pos < BOXSIZE)
        boxList->currBox->box[boxList->currBox->currPkmn] = NULL;
}

void boxListPrintCurrentBox(boxlist_t *boxList){
    if(boxList != NULL)
        printBox(boxList->currBox->box);
}