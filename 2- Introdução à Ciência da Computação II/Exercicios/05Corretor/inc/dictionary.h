#ifndef DICTIONARY_H
    #define DICTIONARY_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    typedef struct dictionary_ dictionary_t;

    dictionary_t *loadDictionaryFromTxtFile(char *fileName);
    void unloadDictionary(dictionary_t *dictionary);
    bool isWordInDictionary(char *word, dictionary_t *dictionary);

#endif