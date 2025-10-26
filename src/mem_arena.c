#include <stdio.h>
#include <stdlib.h>
#include "../include/mem_arena.h"

MEMARENA* arena_init(int mem_size){

    MEMARENA* arena = malloc(sizeof(MEMARENA));
    if(arena != NULL){
        arena->memory = malloc(mem_size);
        if(arena->memory == NULL){
            free(arena);
        }
        else{
            arena->base = arena->memory;
            arena->offset = 0;
        }

    }
    return arena;
}
