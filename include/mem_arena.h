#ifndef MEM_ARENA_H_INCLUDED
#define MEM_ARENA_H_INCLUDED

typedef struct MEMARENA{
    void* base;
    int offset;
    int mem_size;
} MEMARENA;

MEMARENA* arena_init(int mem_size);

#endif // MEM_ARENA_H_INCLUDED
