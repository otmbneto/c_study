#include <stdio.h>
#include <stdlib.h>
#include "include/b_tree.h"

void print_data(void* data){
    if(data != NULL){
        printf("%i ",*(int*)data);
    }
}

void destroy_data(void* data){
    if(data != NULL){
        free((int*)data);
    }
}

Comparison compare_data(void* node_data,void* new_data){

    if(node_data == NULL || new_data == NULL)return 0;

    if(*(int*)node_data > *(int*)new_data){
        return HIGHER;
    }
    else if(*(int*)node_data < *(int*)new_data){
        return LOWER;
    }
    else{
        return EQUAL;
    }
}

int main()
{
    Node* root = NULL;
    for (int k = 0; k < 15; k++) {
        int* val = malloc(sizeof(int));
        *val = k;
        root = insert_in_tree(&root, -1, 3, val, compare_data,destroy_data);
    }
    return 0;
}
