#ifndef __MY_USEFUL_FUNCTIONS__
#define __MY_USEFUL_FUNCTIONS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "myFileFunctions.h"
#include "myStringFunctions.h"
#include "mySortFunctions.h"
#include "myBinarySearch.h"
#include "myStructsAndDefines.h"

void readCommands(metadata **registerFields);
void runCommand(char *command, metadata **registerFields, bool *changeFlag);
metadata *loadRegisterFields();
type_data *getTypeData(FILE *stream);
int getOffsetValue(metadata *registerFields);
void appendRegFile(metadata **registerFields);
void createIdxFile(metadata **registerFields);
void searchIndex(metadata *registerFields);
void printFieldData(char *fieldName, int typeCode, int typeSize, FILE *regFilePointer);
void unloadRegisterFields(metadata *registerFields);

#endif