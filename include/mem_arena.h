#ifndef MEM_ARENA_H_INCLUDED
#define MEM_ARENA_H_INCLUDED

typedef struct MEMARENA{
    void* memory;
    void* base;
    int offset;
} MEMARENA;

MEMARENA* arena_init(int mem_size);

#endif // MEM_ARENA_H_INCLUDED
