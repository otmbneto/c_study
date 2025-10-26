#include "../include/stack.h"

void* peek(STACK* top){

    void* data = NULL;
    if(top != NULL){
        data = top->data;
    }

    return data;
}


void push(STACK** top,void* data){

    STACK* new_item = malloc(sizeof(STACK));
    if(new_item != NULL){

        new_item->data = data;
        new_item->next = *top;
        *top = new_item;

    }
    else{
        printf("ERROR: Memory alloc failed for new Item.\n");
    }
}

int pop(STACK** top){

    int sucess = 0;
    STACK* temp;
    if(*top != NULL){
        temp = *top;
        *top = (*top)->next;
        free(temp);
        sucess = 1;
    }

    return sucess;
}

int is_empty(STACK* top){
    return top == NULL;
}

void free_stack(STACK** top){
    while(!is_empty(*top)){
        pop(top);
    }
}
