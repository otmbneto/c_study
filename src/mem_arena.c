#include <stdio.h>
#include <stdlib.h>
#include "../include/mem_arena.h"

MEMARENA* init_arena(int mem_size){
    MEMARENA* arena = malloc(sizeof(MEMARENA));
    if(arena != NULL){
        arena->base = malloc(mem_size);
        if(arena->base == NULL){
            free(arena);
        }
        else{
            arena->offset = 0;
            arena->mem_size = mem_size;
        }
    }
    return arena;
}

void* alloc_arena(MEMARENA* arena,int block_size){
    void* block = NULL;
    if(arena != NULL && arena->base != NULL){
        block = arena->base + arena->offset;
        arena->offset += block_size;
    }
    return block;
}

void reset_arena(MEMARENA* arena){
    if(arena != NULL){
        arena->offset = 0;
    }
}

void free_arena(MEMARENA** arena){
    if(*arena != NULL && (*arena)->base != NULL){
        free((*arena)->base);
        free(*arena);
    }
}
