#include "myBinarySearch.h"

int binarySearch(metadata *registerFields){
    
    int keysNumber = registerFields->idxFile.keysNumber;
    idx_fields **idxFields = registerFields->idxFile.idxFields;
    
    int middle = 0, min = 0, max = keysNumber - 1;
    field_type inputKey;

    switch(registerFields->key.typeData->typeCode){
        case INT:
            scanf("%d", &inputKey.intField);
            if(keysNumber == 0) return -1;
            while(min <= max){
                middle = (min + max) / 2;
                if(inputKey.intField == *(int *) (idxFields[middle]->keyValue)) return middle;
                else if(inputKey.intField > *(int *) (idxFields[middle]->keyValue)) min = middle + 1;
                else if(inputKey.intField < *(int *) (idxFields[middle]->keyValue)) max = middle - 1;
            }    
            break;      
        case FLOAT:
            scanf("%f", &inputKey.floatField);
            if(keysNumber == 0) return -1;
            while(min <= max){
                middle = (min + max) / 2;
                if(inputKey.floatField == *(float *) idxFields[middle]->keyValue) return middle;
                else if(inputKey.floatField > *(float *) idxFields[middle]->keyValue) min = middle + 1;
                else if(inputKey.floatField < *(float *) idxFields[middle]->keyValue) max = middle - 1;
            }     
            break;       
        case DOUBLE:
            scanf("%lf", &inputKey.doubleFied);
            if(keysNumber == 0) return -1;
            while(min <= max){
                middle = (min + max) / 2;
                if(inputKey.doubleFied == *(double *) idxFields[middle]->keyValue) return middle;
                else if(inputKey.doubleFied > *(double *) idxFields[middle]->keyValue) min = middle + 1;
                else if(inputKey.doubleFied < *(double *) idxFields[middle]->keyValue) max = middle - 1;
            }     
            break;       
        case CHAR:
            scanf("%c", &inputKey.charField);
            if(keysNumber == 0) return -1;
            while(min <= max){
                middle = (min + max) / 2;
                if(inputKey.charField == *(char *) idxFields[middle]->keyValue) return middle;
                else if(inputKey.charField > *(char *) idxFields[middle]->keyValue) min = middle + 1;
                else if(inputKey.charField < *(char *) idxFields[middle]->keyValue) max = middle - 1;
            }     
            break; 
        case STRING:
            inputKey.stringField = readString(stdin, '\n');
            if(keysNumber == 0) return -1;
            while(min <= max){
                middle = (min + max) / 2;
                if(strcmp(inputKey.stringField, (char *) idxFields[middle]->keyValue) == 0){
                    free(inputKey.stringField);
                    return middle;
                }
                else if(strcmp(inputKey.stringField, (char *) idxFields[middle]->keyValue) > 0) min = middle + 1;
                else if(strcmp(inputKey.stringField, (char *) idxFields[middle]->keyValue) < 0) max = middle - 1;
            }     
            break;
        default:
            break;
    }
    return -1;
}
