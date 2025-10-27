#ifndef MEM_ARENA_H_INCLUDED
#define MEM_ARENA_H_INCLUDED

typedef struct MEMARENA{
    void* base;
    int offset;
    int mem_size;
} MEMARENA;

MEMARENA* init_arena(int mem_size);
void* alloc_arena(MEMARENA* arena,int block_size);
void reset_arena(MEMARENA* arena);
void free_arena(MEMARENA** arena);

#endif // MEM_ARENA_H_INCLUDED
