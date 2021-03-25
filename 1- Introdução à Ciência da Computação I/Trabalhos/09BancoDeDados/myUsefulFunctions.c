#include "myUsefulFunctions.h"

void readCommands(metadata **registerFields){
    bool changeFlag = FALSE;
    char *command = readString(stdin, ' ');
    while(strcmp(command, "exit") != 0){
        runCommand(command, registerFields, &changeFlag);
        free(command);
        command = readString(stdin, ' ');
    }
    free(command);
}

void runCommand(char *command, metadata **registerFields, bool *changeFlag){
    if(strcmp(command, "insert") == 0){
        appendRegFile(registerFields);
        *changeFlag = TRUE; 
    }
    else if(strcmp(command, "index") == 0){
        if(*changeFlag == TRUE){
            createIdxFile(registerFields);
            *changeFlag = FALSE; 
        }
    }
    else if(strcmp(command, "search") == 0){
        if(*changeFlag == TRUE) { 
            createIdxFile(registerFields);
            *changeFlag = FALSE;
        }
        searchIndex((*registerFields));
    }
    else{
        //printf("O comando %s nao foi encontrado\n", command);
    }
}

metadata *loadRegisterFields(){
    metadata *registerFields = malloc(sizeof(metadata));
    
    registerFields->files.datFileName = readString(stdin, '\n');
    bool validFileExtension = checkFileExtension(registerFields->files.datFileName, ".dat");
    if(validFileExtension == FALSE){
        printf("O arquivo %s não possui extensão .dat\n",  registerFields->files.datFileName);
        exit(FILE_EXTENSION_ERROR);
    }
    
    FILE *datFilePointer = myFileOpen(registerFields->files.datFileName, "r");

    checkExpectedWord(datFilePointer, "filename:");
    registerFields->files.regFileName = readString(datFilePointer, '\n');
    registerFields->files.idxFileName = getNewExtension(registerFields->files.regFileName, "idx\0");
    registerFields->files.extraFileName = getNewExtension(registerFields->files.regFileName, "extra\0");

    checkExpectedWord(datFilePointer, "key-name:");
    registerFields->key.name = readString(datFilePointer, '\n');
    checkExpectedWord(datFilePointer, "key-type:");
    registerFields->key.typeData = getTypeData(datFilePointer);

    registerFields->fields = NULL;
    bool endFlag = FALSE;
    int index = 0;
    while(endFlag == FALSE){
        registerFields->fields = realloc(registerFields->fields, (index+1) * sizeof(field_data));
        checkExpectedWord(datFilePointer, "field-name:");
        registerFields->fields[index].name = readString(datFilePointer, '\n');
        checkExpectedWord(datFilePointer, "field-type:");
        registerFields->fields[index++].typeData = getTypeData(datFilePointer);
        endFlag = checkEndOfFile(datFilePointer);
    }
   
    registerFields->fieldsNumber = index;

    registerFields->idxFile.offsetValue = getOffsetValue(registerFields);    

    registerFields->idxFile.keysNumber = 0;    

    fclose(datFilePointer);

    return registerFields;
}

type_data *getTypeData(FILE *stream){
    type_data *typeData = malloc(sizeof(type_data));
    char *string = readString(stream, '\n');
    if(strcmp(string, "int") == 0) {
        typeData->typeCode = INT;
        typeData->typeSize = sizeof(int);
    }
    else if(strcmp(string, "float") == 0) {
        typeData->typeCode = FLOAT;
        typeData->typeSize = sizeof(float);
    }
    else if(strcmp(string, "double") == 0) {
        typeData->typeCode = DOUBLE;
        typeData->typeSize = sizeof(double);
    }
    else if(strcmp(string, "char") == 0) {
        typeData->typeCode = CHAR;
        typeData->typeSize = sizeof(char);
    }
    else if(strncmp(string, "char[", 4) == 0 && string[strlen(string)-1] == ']') {
        typeData->typeCode = STRING;
        char *size = getStringInto(string, '[', ']');
        typeData->typeSize = atoi(size)  * sizeof(char);
        free(size);
    }
    else{
        printf("O tipo %s não foi reconhecido\n", string);
        exit(PRIMITIVE_TYPE_NOT_FOUND);
    }
    free(string);
    return typeData;
}

int getOffsetValue(metadata *registerFields){
    int offsetValue = 0;
    offsetValue += registerFields->key.typeData->typeSize;
    for(int i = 0; i < registerFields->fieldsNumber; i++){
        offsetValue += registerFields->fields[i].typeData->typeSize;
    }
    return offsetValue;
}

void appendRegFile(metadata **registerFields){
    FILE *regFilePointer = myFileOpen((*registerFields)->files.regFileName, "a+b");
    
    char *auxBuffer = readString(stdin, ',');
    adjustableRegFileWrite(regFilePointer, (*registerFields)->key.typeData->typeCode, auxBuffer, (*registerFields)->key.typeData->typeSize);
    free(auxBuffer);
    
    for(int i = 0; i < (*registerFields)->fieldsNumber; i++){
        auxBuffer = readString(stdin, ',');
        adjustableRegFileWrite(regFilePointer, (*registerFields)->fields[i].typeData->typeCode, auxBuffer, (*registerFields)->fields[i].typeData->typeSize);
        free(auxBuffer);
    }

    fclose(regFilePointer);
}

void createIdxFile(metadata **registerFields){
    FILE *regFilePointer = myFileOpen((*registerFields)->files.regFileName, "rb");

    int offsetValue = (*registerFields)->idxFile.offsetValue, index = 0;
    int typeCode = (*registerFields)->key.typeData->typeCode;
    idx_fields **idxFields = NULL;
    bool endFlag = FALSE;
    
    while(endFlag == FALSE){
        idxFields = (idx_fields **) realloc(idxFields, (index+1) * sizeof(idx_fields *));
        idxFields[index] = (idx_fields *) malloc(sizeof(idx_fields));
        idxFields[index]->keyValue = adjustableRegFileRead(regFilePointer, typeCode, (*registerFields)->key.typeData->typeSize);
        idxFields[index]->offset = index * offsetValue;
        index++;
        fseek(regFilePointer, index  * offsetValue, SEEK_SET);
        endFlag = checkEndOfFile(regFilePointer);
    }            
    
    fclose(regFilePointer);

    (*registerFields)->idxFile.idxFields = idxFields;
    (*registerFields)->idxFile.keysNumber = index;

    idxFieldSort(registerFields);

    FILE *idxFilePointer = myFileOpen((*registerFields)->files.idxFileName, "wb");

    for(int i = 0; i < index; i++){
        adjustableIdxFileWrite(idxFilePointer, typeCode, (*registerFields)->idxFile.idxFields[i]->keyValue, (*registerFields)->key.typeData->typeSize);
        fwrite(&(*registerFields)->idxFile.idxFields[i]->offset, sizeof(int), 1, idxFilePointer);
    } 

    fclose(idxFilePointer);
}

void searchIndex(metadata *registerFields){
    int pos = binarySearch(registerFields);
    if(pos == -1){
        //printf("O arquivo .reg não esta carregado com essa chave.\n\n");
        return;
    }
    
    FILE *regFilePointer = myFileOpen(registerFields->files.regFileName, "rb");
    
    fseek(regFilePointer, registerFields->idxFile.idxFields[pos]->offset, SEEK_SET);
 
    printFieldData(registerFields->key.name, registerFields->key.typeData->typeCode, registerFields->key.typeData->typeSize, regFilePointer);
    
    for(int i = 0; i < registerFields->fieldsNumber; i++){
        printFieldData(registerFields->fields[i].name, registerFields->fields[i].typeData->typeCode, registerFields->fields[i].typeData->typeSize, regFilePointer);  
    }
    fclose(regFilePointer);
    printf("\n");
    
}

void printFieldData(char *fieldName, int typeCode, int typeSize, FILE *regFilePointer){
    field_type fieldType;
    printf("%s: ", fieldName);
    switch(typeCode){
        case INT:
            fread(&fieldType.intField, typeSize, 1, regFilePointer);
            printf("%d\n", fieldType.intField);
            return;
        case FLOAT:
            fread(&fieldType.floatField, typeSize, 1, regFilePointer);
            printf("%.2f\n", fieldType.floatField);
            return;
        case DOUBLE:
            fread(&fieldType.doubleFied, typeSize, 1, regFilePointer);
            printf("%.2lf\n", fieldType.doubleFied);
            return;
        case CHAR:
            fread(&fieldType.charField, typeSize, 1, regFilePointer);
            printf("%c\n", fieldType.charField);
            return;
        case STRING:
            fieldType.stringField = calloc(typeSize, sizeof(char));
            fread(fieldType.stringField, typeSize, 1, regFilePointer);
            printf("%s\n", fieldType.stringField);
            free(fieldType.stringField);
            return;
        default:
            exit(PRIMITIVE_TYPE_NOT_FOUND);
    }
}

void unloadRegisterFields(metadata *registerFields){
    free(registerFields->files.datFileName);    
    free(registerFields->files.regFileName);    
    free(registerFields->files.idxFileName);    
    free(registerFields->files.extraFileName);    
    
    free(registerFields->key.name);
    free(registerFields->key.typeData);
    
    for(int i = 0; i < registerFields->fieldsNumber; i++){
        free(registerFields->fields[i].name);
        free(registerFields->fields[i].typeData);
    }
    free(registerFields->fields);
    
    for(int i = 0; i < registerFields->idxFile.keysNumber; i++){
        free(registerFields->idxFile.idxFields[i]->keyValue);
        free(registerFields->idxFile.idxFields[i]);
    }
    if(registerFields->idxFile.keysNumber > 0) free(registerFields->idxFile.idxFields);

    free(registerFields);
}
