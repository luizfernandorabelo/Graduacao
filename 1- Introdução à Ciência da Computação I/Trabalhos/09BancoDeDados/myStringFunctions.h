#ifndef __MY_STRING_FUNCTIONS__
#define __MY_STRING_FUNCTIONS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "myStructsAndDefines.h"
#include "myUsefulFunctions.h"
 
char *readString(FILE *stream, char delim);
char *getStringInto(char *originalString, char begin, char end);
void checkExpectedWord(FILE *stream, char *expectedWord);

#endif
