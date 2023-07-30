#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "gc.h"


int main(void) {
    int *x = gc_malloc(sizeof(int));
    *x = 10;
    printf("x = %d\n", *x);


    char *str = gc_calloc(sizeof(char), 128);
    strcpy(str, "Hello From C with GC!!!");
    printf("%s\n", str);

    gc_freeAll();
    return 0;
}

