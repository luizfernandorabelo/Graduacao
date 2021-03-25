#ifndef __LIST_H__
    #define __LIST_H__

    #include <stdio.h>

    #ifndef BOOLEAN_TYPE
        #define BOOLEAN_TYPE

        #define bool char
        #define True 1
        #define False 0
    #endif

    #define BUBBLE 1
    #define INSERTION 2 
    #define MERGE 3    

    typedef struct names_list_ NAMES_LIST;

    NAMES_LIST *loadNamesList(char *fileName);
    void sortNamesListDescending(NAMES_LIST *namesList, int type);
    void printNamesList(NAMES_LIST *namesList);
    void freeNamesList(NAMES_LIST **namesList);

#endif