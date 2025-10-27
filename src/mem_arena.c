#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "../include/mem_arena.h"

MEMARENA* init_arena(size_t mem_size){
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

void* alloc_arena(MEMARENA* arena,size_t block_size){
    void* block = NULL;
    if(arena != NULL && arena->base != NULL){

        if(arena->offset + block_size > arena->mem_size){
            printf("ERROR: Arena overflow\n");
            return NULL;
        }

        block = (char*)arena->base + arena->offset;
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
        *arena = NULL;
    }
}

size_t remaining_arena(MEMARENA* arena){

    return arena->mem_size - arena->offset;

}
