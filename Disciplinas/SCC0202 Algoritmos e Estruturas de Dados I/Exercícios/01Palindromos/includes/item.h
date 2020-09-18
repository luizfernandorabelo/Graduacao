#ifndef ITEM_H
    #define ITEM_H
    
    #define bool char
    #define True 1
    #define False 0

    #define GET_KEY_ERROR -1

    typedef struct item_ ITEM;
    ITEM *itemCreate(char key);
    bool itemDelete(ITEM **item);
    void itemPrint(ITEM *item);
    char itemGetKey(ITEM *item);
    bool itemSetKey(ITEM *item, char key);

#endif