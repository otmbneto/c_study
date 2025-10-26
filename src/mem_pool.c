#include <stdio.h>
#include <stdlib.h>
#include "../include/mem_pool.h"

void pool_destroy(MEMPOOL* pool){
    free_stack(&pool->blocks);
    free(pool->memory);
    free(pool);
}

MEMPOOL* pool_init(int block_size, int block_count){

    MEMPOOL* mem_pool = malloc(sizeof(MEMPOOL));
    if(mem_pool != NULL){
        mem_pool->block_size = block_size;
        mem_pool->block_count = block_count;
        mem_pool->memory = malloc(block_size*block_count);
        if(mem_pool->memory != NULL){
            mem_pool->blocks = malloc(sizeof(STACK));
            mem_pool->blocks->next = NULL;
            if(mem_pool->blocks == NULL){
                free(mem_pool->memory);
                free(mem_pool);
            }
            else{
                //push each block pointer into the stack.
                for (int i = 0; i < block_count; i++) {
                    void* block = (char*)mem_pool->memory + i * block_size;
                    push(&mem_pool->blocks, block);
                }
            }
        }
        else{
            free(mem_pool);
        }
    }
    return mem_pool;
}

void* pool_alloc(MEMPOOL* pool){

    STACK* blocks = pool->blocks;
    void* block = NULL;
    if(!is_empty(blocks)){
        block = peek(blocks);
        pop(&pool->blocks);
    }
    return block;
}

void pool_free(MEMPOOL* pool, void* block){
    push(&pool->blocks,block);
}
