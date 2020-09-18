#ifndef MY_STACK_H
    #define MY_STACK_H

    #include "item.h"

    #define STACK_MAX_SIZE 2147483647 //int max value
    #define STACK_INVALID_ACCESS -1
    
    typedef struct stack_ STACK;
    
    STACK *stackCreate(void);
    bool stackDelete(STACK **stack);
    bool isStackEmpty(STACK *stack);
    bool isStackFull(STACK *stack);
    int stackSize(STACK *stack);
    ITEM *stackTop(STACK *stack);
    bool stackUp(STACK *stack, ITEM *item);
    ITEM *unStack(STACK *stack);

#endif