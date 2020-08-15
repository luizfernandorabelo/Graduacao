#include "mySortFunctions.h"

void idxFieldSort(metadata **registerFields){
    int typeCode = (*registerFields)->key.typeData->typeCode;
    int keysNumber = (*registerFields)->idxFile.keysNumber;
    idx_fields **idxFields = (*registerFields)->idxFile.idxFields;
    switch(typeCode){
        case INT:
            qsort(idxFields, keysNumber, sizeof(idx_fields *), intCompar);
            break;
        case FLOAT:
            qsort(idxFields, keysNumber, sizeof(idx_fields *), floatCompar);
            break;
        case DOUBLE:
            qsort(idxFields, keysNumber, sizeof(idx_fields *), doubleCompar);
            break;
        case CHAR:
            qsort(idxFields, keysNumber, sizeof(idx_fields *), charCompar);
            break;
        case STRING:
            qsort(idxFields, keysNumber, sizeof(idx_fields *), stringCompar);
            break;
        default:
            break;
    }
}

int intCompar(const void *a, const void *b){
    return(*((int *)((*(idx_fields **)a))->keyValue) - *((int *)((*(idx_fields **)b))->keyValue));
}

int floatCompar(const void *a, const void *b){
    return(*((float *)((*(idx_fields **)a))->keyValue) - *((float *)((*(idx_fields **)b))->keyValue));
}

int doubleCompar(const void *a, const void *b){
    return(*((double *)((*(idx_fields **)a))->keyValue) - *((double *)((*(idx_fields **)b))->keyValue));
}

int charCompar(const void *a, const void *b){
    return(*((char *)((*(idx_fields **)a))->keyValue) - *((char *)((*(idx_fields **)b))->keyValue));
}

int stringCompar(const void *a, const void *b){
    return(strcmp((char *)(*(idx_fields **)a)->keyValue, (char *)((*(idx_fields **)b)->keyValue)));
}
