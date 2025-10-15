#include <stdio.h>
#include <stdlib.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#ifndef B_TREE_H_INCLUDED
#define B_TREE_H_INCLUDED
typedef enum {EQUAL,LOWER,HIGHER} Comparison;

typedef struct Node{

    void** keys;
    int keys_count;
    int min_degree;
    int children_count;
    struct Node** children;

} Node;

void insert_key(Node* node,void* data,Comparison (*compare_data_foo)(void*,void*));
int search_key(Node* node,void* data,Comparison (*compare_data_foo)(void*,void*));
void* remove_key_at(Node* node,int index);
void* remove_key(Node* node,void* data,Comparison (*compare_data_foo)(void*,void*));
void destroy_keys(Node* node,void (*destroy_data_foo)(void*));
void destroy_node(Node** node,void (*destroy_data_foo)(void*));
Node* create_node(int min_degree,void* data,Comparison (*compare_data_foo)(void*,void*),void (*destroy_data_foo)(void*));
Node* search_node(Node* node,void* data,Comparison (*compare_data_foo)(void*,void*));
void split_node(Node** node,int child_index,Comparison (*compare_data_foo)(void*,void*),void (*destroy_data_foo)(void*));
Node* insert_in_tree(Node** parent,int child_index,int min_degree,void* data,Comparison (*compare_data_foo)(void*,void*),void (*destroy_data_foo)(void*));

#endif // B_TREE_H_INCLUDED
