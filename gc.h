#ifndef GC_H
#define GC_H

#include <stdlib.h>
#include <memory.h>


typedef struct __chunk {
    size_t size;
    void *ptr;
    struct __chunk *next;
    struct __chunk *prev;
} Chunk;


typedef struct __mem {
    Chunk *head;
    Chunk *tail;
    size_t sum_size;
} Memory;


void *gc_malloc(size_t size);
void *gc_calloc(size_t size, size_t count);
void gc_freeAll();


#endif // GC_H
