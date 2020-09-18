#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct knot_ KNOT;

struct knot_{
    ITEM *item;
    KNOT *previous;
};

struct stack_{
    KNOT *top;
    int size;
};

STACK *stackCreate(){
    STACK *stack = malloc(sizeof(STACK));
    if(stack != NULL){
        stack->top = NULL;
        stack->size = 0;
    }
    return stack;
}

bool stackDelete(STACK **stack){
    if((*stack) == NULL) return False;
    while(!isStackEmpty(*stack)){
        KNOT *newTop = (*stack)->top->previous;
        free((*stack)->top);
        (*stack)->top = newTop;
    }
    free(*stack);
    *stack = NULL;
    return True;
}

bool isStackEmpty(STACK *stack){
    if(stack == NULL) exit(STACK_INVALID_ACCESS);
    return(stack->top == NULL) ? True : False;
}

bool isStackFull(STACK *stack){
    if(stack == NULL) exit(STACK_INVALID_ACCESS);
    return(stack->size == STACK_MAX_SIZE) ? True : False;
}

int stackSize(STACK *stack){
    if(stack == NULL) exit(STACK_INVALID_ACCESS);
    return stack->size;
}

ITEM *stackTop(STACK *stack){
    if(stack == NULL || isStackEmpty(stack)) return NULL;
    return stack->top->item;
}

bool stackUp(STACK *stack, ITEM *item){
    if(stack != NULL && stack->size < STACK_MAX_SIZE){
        KNOT *newKnot = malloc(sizeof(KNOT));
        newKnot->item = item;
        newKnot->previous = stack->top;
        stack->top = newKnot;
        stack->size += 1;
        return True;
    }
    return False;
}

ITEM *unStack(STACK *stack){
    if(stack != NULL && !isStackEmpty(stack)){
        KNOT *knot = stack->top;
        ITEM *item = stack->top->item;
        stack->top = knot->previous;
        free(knot);
        knot = NULL;
        stack->size -= 1;
        return item;
    }
    return NULL;
}
