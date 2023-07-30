# CGC

A simple and tiny garbage collector in C for C :)

I wrote it in probably 1 or 1.5 hours so it's not a big deal and not ment to be used
in other projects. It's only a hubby side project to practice how to implement a simple
GC in C programming language with my own understanding of memory and data structures.

## How it works

It's only a wrapper for `malloc` and `calloc` functions to store allocated
memory chunkes in a doubly-linked-list to keep track of them.

then at the end of `main` function user must call `gc_freeAll` function to
free all of the allocated memory on the Heap.

