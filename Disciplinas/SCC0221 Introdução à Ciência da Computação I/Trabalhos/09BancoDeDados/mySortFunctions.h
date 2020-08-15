#ifndef __MY_SORT_FUNCTIONS__
#define __MY_SORT_FUNCTIONS__

#include <stdlib.h>
#include <string.h>
#include "myStructsAndDefines.h"

void idxFieldSort(metadata **registerFields);
int intCompar(const void *a, const void *b);
int floatCompar(const void *a, const void *b);
int doubleCompar(const void *a, const void *b);
int charCompar(const void *a, const void *b);
int stringCompar(const void *a, const void *b);

#endif
