#include <stdio.h>
#include <stdlib.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
typedef enum {EQUAL,LOWER,HIGHER} Comparison;

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
        return LOWER;
    }
    else if(*(int*)node_data < *(int*)new_data){
        return HIGHER;
    }
    else{
        return EQUAL;
    }
}

typedef struct Node{

    void** keys;
    int keys_count;
    int min_degree;
    int children_count;
    struct Node** children;

} Node;

//function assumes enough space for the new insertion
void insert_key(Node* node,void* data,Comparison (*compare_data_foo)(void*,void*)){

    int i = node->keys_count-1;
    while(i >=0 && compare_data_foo(node->keys[i],data) == LOWER){
        node->keys[i+1] = node->keys[i];
        i--;
    }
    node->keys[i+1] = data;
    node->keys_count++;

}

int search_key(Node* node,void* data,Comparison (*compare_data_foo)(void*,void*)){

    int i = 0;
    while(i < node->keys_count){
        if(compare_data_foo(node->keys[i],data) == EQUAL){
            return i;
        }
        i++;
    }

    return -1;
}

void* remove_key_at(Node* node,int index){

    void* target = node->keys[index];
    for(int i = index;i < node->keys_count-1;i++){
        node->keys[i] = node->keys[i+1];
    }
    node->keys[node->keys_count-1] = NULL;
    node->keys_count--;

    return target;
}

void* remove_key(Node* node,void* data,Comparison (*compare_data_foo)(void*,void*)){

    void* target = NULL;
    int index = search_key(node,data,compare_data_foo);
    if(index >= 0){
        target = remove_key_at(node,index);
    }

    return target;
}

void destroy_keys(Node* node,void (*destroy_data_foo)(void*)){

    for(int i = 0;i < node->keys_count;i++){
        destroy_data_foo(node->keys[i]);
        node->keys[i] = NULL;
    }
    node->keys_count = 0;
}

void destroy_node(Node** node,void (*destroy_data_foo)(void*)){

    if(node != NULL){
        destroy_keys(*node,destroy_data);
        free((*node)->keys);
        if((*node)->children != NULL){
            for(int i = 0;i < (*node)->children_count;i++){
                destroy_node(&(*node)->children[i],destroy_data_foo);
                (*node)->children[i] = NULL;
            }
            free((*node)->children);
        }
        free(*node);
        *node = NULL;
    }
}

Node* create_node(int min_degree,void* data,Comparison (*compare_data_foo)(void*,void*)){

    Node* new_node = malloc(sizeof(Node));
    if(new_node != NULL){
        new_node->keys_count = 0;
        new_node->keys = calloc(2*min_degree - 1, sizeof(void*));
        if(new_node->keys == NULL){
            free(new_node);
            new_node = NULL;
        }
        else{
            new_node->min_degree = min_degree;
            new_node->children_count = 0;
            new_node->children = calloc(2*min_degree, sizeof(Node*));
            if(new_node->children == NULL){
                destroy_keys(new_node,destroy_data);
                free(new_node);
                new_node = NULL;
            }
            if(data != NULL){
                insert_key(new_node,data,compare_data_foo);
            }
        }
    }
    return new_node;
}

Node* search_node(Node* node,void* data,Comparison (*compare_data_foo)(void*,void*)){
    //TODO
}


//if child index is less than 0 node is the root;otherwise is a child.
void split_node(Node** node,int child_index,Comparison (*compare_data_foo)(void*,void*)){
    Node* full_node = NULL;
    Node* new_node = create_node((*node)->min_degree,NULL,NULL);
    int T = (*node)->min_degree;
    int i = 0;

    //if node is root create new root and proceed to split old node.
    if(child_index < 0){
        Node* new_root = create_node((*node)->min_degree,NULL,NULL);
        if(new_root == NULL) return;
        new_root->children[0] = *node;
        *node = new_root;
        child_index++;
    }

    full_node = (*node)->children[child_index];
    //insert the second half of the keys into the new node;remove it from og node
    for(int j=0;j < T-1;j++){

        insert_key(new_node,full_node->keys[j + T],compare_data_foo);
        full_node->keys[j + T] = NULL;
        full_node->keys_count--;

    }
    //it is not a leaf,send the second half of the children to the new node
    if(full_node->children_count > 0){
        for(int k = 0;k < T;k++){
            new_node->children[k] = full_node->children[k + T];
            new_node->children_count++;
            full_node->children[k + T] = NULL;
            full_node->children_count--;
        }
    }
    //add new node to parent
    for(int j = (*node)->children_count; j > child_index; j--){
        (*node)->children[j+1] = (*node)->children[j];
    }
    (*node)->children[child_index + 1] = new_node;
    (*node)->children_count++;

    //send the M-1 key to the parent
    for (int i = (*node)->keys_count - 1; i >= child_index; i--) {
            (*node)->keys[i+1] = (*node)->keys[i];
    }
    (*node)->keys[child_index] = full_node->keys[T-1];
    full_node->keys[T-1] = NULL;
    (*node)->keys_count++;
    full_node->keys_count--;

}

//TODO: correct the recursion
Node* insert_in_tree(Node** parent,int child_index,int min_degree,void* data,Comparison (*compare_data_foo)(void*,void*)){

    Node** child = NULL;
    //init tree
    if(*parent == NULL){
        return create_node(min_degree,data,compare_data_foo);
    }

    //parent is root
    if(child_index < 0){
        child = parent;
    }
    else{
        child = &(*parent)->children[child_index];
    }

    //leaf node
    if((*child)->children_count == 0){

        //if it is full,split it.
        if((*child)->keys_count == (2*(*child)->min_degree - 1)){
            split_node(parent,child_index,compare_data_foo);
        }

        insert_key(*child,data,compare_data_foo);
    }
    else{ //intermediary node
        int i = (*child)->keys_count-1;
        while(i >= 0 && compare_data_foo((*child)->keys[i],data) == LOWER){
            i--;
        }
        i++;

        insert_in_tree(child,i,(*child)->min_degree,data,compare_data_foo);
        if((*child)->keys_count == (2*(*child)->min_degree - 1)){
            split_node(parent,child_index,compare_data_foo);
        }

    }

    return *child;
}

int main(){


    return 0;
}
