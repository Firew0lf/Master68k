#ifndef MALLOC_H
#define MALLOC_H

#define MALLOC_BLOCK_SIZE 64
//#define MALLOC_DEBUG

#include <stddef.h>
#include <stdint.h>

void malloc_init(void* mainMem, size_t memsize);
int malloc_blocksCount();
int malloc_freeBlocks();
int malloc_freeRam();
void* kmalloc(size_t size);
void* calloc(size_t nitems, size_t size);
void* krealloc(void* ptr, size_t size);
void kfree(void* m);

#endif
