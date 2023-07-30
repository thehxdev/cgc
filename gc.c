#include <stdlib.h>
#include "gc.h"


#define init_main_mem() if (main_mem == NULL) main_mem = memory_new()


static Memory *main_mem = NULL;

static Memory *memory_new() {
    // new memory instance
    Memory *nm = (Memory*) malloc(sizeof(Memory));
    if (nm == NULL)
        return NULL;

    nm->head = NULL;
    nm->tail = NULL;
    nm->sum_size = 0;

    return nm;
}


static void chunkptr_init_malloc(Chunk *chp, size_t size) {
    if (chp != NULL) {
        chp->size = size;
        chp->ptr  = (void*) malloc(size);
        chp->next = NULL;
        chp->prev = NULL;
    }
}

static void chunkptr_init_calloc(Chunk *chp, size_t size, size_t count) {
    if (chp != NULL) {
        chp->size = size;
        chp->ptr  = (void*) calloc(size, count);
        chp->next = NULL;
        chp->prev = NULL;
    }
}


static Chunk *chunk_new_malloc(size_t size) {
    if (size == 0)
        return NULL;

    Chunk *ch = (Chunk*) malloc(sizeof(Chunk));
    if (ch == NULL)
        return NULL;

    chunkptr_init_malloc(ch, size);
    return ch;
}


static Chunk *chunk_new_calloc(size_t size, size_t count) {
    if (size == 0)
        return NULL;

    Chunk *ch = (Chunk*) malloc(sizeof(Chunk));
    if (ch == NULL)
        return NULL;

    chunkptr_init_calloc(ch, size, count);
    return ch;
}


static void chunk_free(Chunk *chp) {
    if (chp) {
        if (chp->ptr)
            free(chp->ptr);
        free(chp);
    }
}


void *gc_malloc(size_t size) {
    init_main_mem();

    // new chunk of memory instace
    Chunk *ch = (Chunk*) chunk_new_malloc(size);
    if (ch == NULL)
        return NULL;

    if (main_mem->head == NULL) {
        main_mem->head = ch;
        main_mem->tail = ch;
        goto ret;
    }

    ch->prev = main_mem->tail;
    main_mem->tail->next = ch;
    main_mem->tail = ch;
    main_mem->sum_size += size;

ret:
    return ch->ptr;
}


void *gc_calloc(size_t size, size_t count) {
    init_main_mem();

    // new chunk of memory instace
    Chunk *ch = (Chunk*) chunk_new_calloc(size, count);
    if (ch == NULL)
        return NULL;

    if (main_mem->head == NULL) {
        main_mem->head = ch;
        main_mem->tail = ch;
        goto ret;
    }

    ch->prev = main_mem->tail;
    main_mem->tail->next = ch;
    main_mem->tail = ch;
    main_mem->sum_size += size;

ret:
    return ch->ptr;
}


void gc_freeAll() {
    if (main_mem != NULL) {
        Chunk *tmp = main_mem->head;
        if (tmp == NULL)
            goto only_mem;
        Chunk *next = tmp->next;

        while (1) {
            chunk_free(tmp);
            tmp = next;
            if (tmp == NULL)
                break;
            next = tmp->next;
        }
only_mem:
        free(main_mem);
        main_mem = NULL;
    }
}

