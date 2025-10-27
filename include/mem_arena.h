#ifndef MEM_ARENA_H_INCLUDED
#define MEM_ARENA_H_INCLUDED

typedef struct MEMARENA{
    void* base;
    size_t offset;
    size_t mem_size;
} MEMARENA;

MEMARENA* init_arena(size_t mem_size);
void* alloc_arena(MEMARENA* arena,size_t block_size);
void reset_arena(MEMARENA* arena);
void free_arena(MEMARENA** arena);

#endif // MEM_ARENA_H_INCLUDED
