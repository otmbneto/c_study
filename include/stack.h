#include <stdio.h>
#include <stdlib.h>

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct STACK {
    void* data;
    struct STACK* next;
} STACK;

void* peek(STACK* top);
void push(STACK** top,void* data);
int pop(STACK** top);
int is_empty(STACK* top);
void free_stack(STACK** top);

#endif // STACK_H_INCLUDED
