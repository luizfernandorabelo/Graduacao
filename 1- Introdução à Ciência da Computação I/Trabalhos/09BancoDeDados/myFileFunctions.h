#ifndef __MY_FILE_FUNCTIONS__
#define __MY_FILE_FUNCTIONS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "myStructsAndDefines.h"
#include "myStringFunctions.h"

FILE *myFileOpen(char *fileName, char *mode);
bool checkEndOfFile(FILE *stream);
bool checkFileExtension(char *fileName, char *extension);
char *getNewExtension(char *fileName, char *newExtension);
void adjustableRegFileWrite(FILE *stream, int typeCode, char *string, int size);
void *adjustableRegFileRead(FILE *stream, int typeCode, int size);
void adjustableIdxFileWrite(FILE *stream, int typeCode, void *keyValue, int size);

#endif
