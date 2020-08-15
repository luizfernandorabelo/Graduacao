#include "myFileFunctions.h"

FILE *myFileOpen(char *fileName, char *mode){
    FILE *filePointer = NULL;
    filePointer = fopen(fileName, mode);
    if(filePointer == NULL){
        printf("Erro ao abrir o arquivo %s\n", fileName);
        exit(FILE_OPEN_ERROR);
    }
    return filePointer;
}

bool checkEndOfFile(FILE *stream){
    long int character = fgetc(stream);
    fseek(stream, -1, SEEK_CUR);
    return (character == EOF) ? TRUE : FALSE;
}

bool checkFileExtension(char *fileName, char *extension){
    int j = strlen(extension), k = strlen(fileName);
    for(int i = j - 1; i >= 0; i--) if(extension[i] != fileName[k+i-j]) return FALSE;
    return TRUE;
}

char *getNewExtension(char *fileName, char *newExtension){
    int lenFileName = strlen(fileName), lenNewExtension = strlen(newExtension);
    char *newFileName = calloc(lenFileName + lenNewExtension - 3 + 1, sizeof(char));
    strcpy(newFileName, fileName);
    for(int i = lenFileName - 1; i >= 0; i--){
        if(newFileName[i] == '.'){
            for(int j = 0; j < lenNewExtension; j++) newFileName[i+j+1] = newExtension[j];
            break;
        }
    }
    return newFileName;
}

void adjustableRegFileWrite(FILE *stream, int typeCode, char *string, int size){
    field_type type;
    char *auxBuffer = NULL;
    switch(typeCode){
        case 0:
            type.intField = atoi(string);
            fwrite(&type.intField, size, 1, stream);                       
            return;
        case 1:
            type.floatField = atof(string);
            fwrite(&type.floatField, size, 1, stream);                       
            return;
        case 2:
            type.doubleFied = (double) atof(string);
            fwrite(&type.doubleFied, size, 1, stream);                       
            return;
        case 3:
            type.charField = string[0];
            fwrite(&type.charField, size, 1, stream);                       
            return;
        case 4:
            type.stringField = calloc(size, sizeof(char));
            auxBuffer = getStringInto(string, '"', '"');
            strcpy(type.stringField, auxBuffer);
            fwrite(type.stringField, size, 1, stream);
            free(type.stringField);     
            free(auxBuffer);                  
            return;
        default:
            exit(FILE_WRITE_ERROR);
    }
}

void *adjustableRegFileRead(FILE *stream, int typeCode, int size){
    field_type type;
    switch(typeCode){
        case 0:
            type.intPointerField = calloc(1, size);
            fread(type.intPointerField, size, 1, stream);                       
            return type.intPointerField;
        case 1:
            type.floatPointerField = calloc(1, size);
            fread(type.floatPointerField, size, 1, stream);                       
            return type.floatPointerField;
        case 2:
            type.doublePointerField = calloc(1, size);
            fread(type.doublePointerField, size, 1, stream);                       
            return type.doublePointerField;
        case 3:
            type.charPointerField = calloc(1, size);
            fread(type.charPointerField, size, 1, stream);                       
            return type.charPointerField;
        case 4:
            type.stringField = calloc(size, sizeof(char));
            fread(type.stringField, size, 1, stream);
            return type.stringField; 
        default:
            exit(FILE_READ_ERROR);
    }
}

void adjustableIdxFileWrite(FILE *stream, int typeCode, void *keyValue, int size){
    field_type type;
    switch(typeCode){
        case 0:
            type.intField = *(int *) keyValue;
            fwrite(&type.intField, size, 1, stream);                       
            return;
        case 1:
            type.floatField = *(float *) keyValue;
            fwrite(&type.floatField, size, 1, stream);                       
            return;
        case 2:
            type.doubleFied = *(double *) keyValue;
            fwrite(&type.doubleFied, size, 1, stream);                       
            return;
        case 3:
            type.charField = *(char *) keyValue;
            fwrite(&type.charField, size, 1, stream);                       
            return;
        case 4:
            type.stringField = calloc(size, sizeof(char));
            strcpy(type.stringField, (char *) keyValue);
            fwrite(type.stringField, size, 1, stream);
            free(type.stringField);     
            return;
        default:
            exit(PRIMITIVE_TYPE_NOT_FOUND);
    }
}
