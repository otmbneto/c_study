#ifndef MEM_POOL_H_INCLUDED
#define MEM_POOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct MEMPOOL{

    void* memory;
    int block_size;
    int block_count;
    STACK* blocks;

} MEMPOOL;

MEMPOOL* pool_init(int block_size, int block_count);
void* pool_alloc(MEMPOOL* pool);
void pool_free(MEMPOOL* pool, void* ptr);

#endif // MEM_POOL_H_INCLUDED
