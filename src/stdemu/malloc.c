/*
Platform-independent memory allocator.
Only depends on string for size_t and memmove.
Depends on stdio if MALLOC_DEBUG is defined.

How it works:
	- `blocks_mem` stores the block allocation table
		- if a 0 is stored, the block is free
		- if a 1 is stored, the block is the last of a chain
		- if something else is stored, it is the number of following blocks that are also allocated

Memory efficiency: up to (MALLOC_BLOCK_SIZE/(MALLOC_BLOCK_SIZE+sizeof(block_index))
*/

//#define MALLOC_DEBUG

#include <string.h>

#ifdef MALLOC_DEBUG
#include <stdio.h>
#endif

#include "malloc.h"

typedef uint16_t block_index;

static block_index* blocks_mem;  // for storing the allocation table
static block_index blocks_count;
static void* storage_mem; // for storing data

// Misc functions
static inline block_index blocksCount(size_t size) {
	return size/MALLOC_BLOCK_SIZE + ((size%MALLOC_BLOCK_SIZE)?1:0);
}

static inline void* blockAddress(block_index b) {
	return storage_mem + (MALLOC_BLOCK_SIZE*b);
}

static inline block_index addressBlock(void* a) {
	#ifdef MALLOC_DEBUG
	if ((a-storage_mem)%MALLOC_BLOCK_SIZE > 0) {
		printf("[malloc]misaligned address: %p\n", a);
	}
	#endif
	return (a-storage_mem)/MALLOC_BLOCK_SIZE;
}

static inline block_index getBlock(block_index i) {
	return blocks_mem[i];
}

static inline void setBlock(block_index i, block_index v) {
	blocks_mem[i] = v;
}

// Main functions
void malloc_init(void* mainMem, size_t memsize) {
	blocks_mem = mainMem; // put'em at the start
	blocks_count = memsize/(sizeof(block_index)+MALLOC_BLOCK_SIZE);
	storage_mem = mainMem + blocks_count*sizeof(block_index);
	
	int i;
	for (i=0; i<blocks_count; i++) {
		setBlock(i, 0);
	}
	#ifdef MALLOC_DEBUG
	printf("Blocks: %p | Storage: %p\n", blocks_mem, storage_mem);
	#endif
}

int malloc_blocksCount() {
	return blocks_count;
}

int malloc_freeBlocks() {
	block_index i;
	int c = 0;
	for (i=0; i<blocks_count; i++) {
		if (getBlock(i)) c++;
	}
	return c;
}

int malloc_freeRam() {
	return malloc_freeBlocks()*MALLOC_BLOCK_SIZE;
}

void* kmalloc(size_t size) {
	int blocksNeeded = blocksCount(size);
	#ifdef MALLOC_DEBUG
	printf("[kmalloc]Requesting %d blocks, %d bytes\n", blocksNeeded, (int)size);
	#endif
	
	// search for contiguous blocks
	int i;
	int max = 0;
	int where = -1;
	for (i=0; i<blocks_count; i++) {
		if (getBlock(i) == 0) {
			max++;
		} else {
			max = 0;
		}
		
		if (max == blocksNeeded) {
			where = i-blocksNeeded+1;
			break;
		}
	}
	//printf("[kmalloc]Found %d/(%d+%d) blocks (for %d bytes) at %d\n", max, size/MALLOC_BLOCK_SIZE, (size%MALLOC_BLOCK_SIZE)?1:0, size, where);
	if (max < blocksNeeded) { // didn't find enough space
		#ifdef MALLOC_DEBUG
		printf("[kmalloc]Not enough contiguous memory\n");
		#endif
		return NULL;
	}
	#ifdef MALLOC_DEBUG
	printf("[kmalloc]Found blocks at %d\n[kmalloc]Setting blocks:\n", where);
	#endif
	
	int j;
	for (j=blocksNeeded; j; j--) {
		#ifdef MALLOC_DEBUG
		printf("  %d: %d -> %d\n", where+(blocksNeeded-j), getBlock(where+(blocksNeeded-j)), j);
		#endif
		setBlock(where+(blocksNeeded-j), j);
	}
	
	#ifdef MALLOC_DEBUG
	void* ret = blockAddress(where);
	printf("[kmalloc]Returning address %p\n", ret);
	return ret;
	#endif
	return blockAddress(where);
}

void* calloc(size_t nitems, size_t size) {
	size_t s = nitems*size;
	void* ptr = kmalloc(s);
	if (ptr == NULL) return NULL;
	size_t i;
	for (i=0; i<s; i+=sizeof(char)) {
		((char*)ptr)[i] = 0;
	}
	return ptr;
}

void* krealloc(void* ptr, size_t size) {
	block_index firstBlock = addressBlock(ptr);
	int blocksNeeded = blocksCount(size);
	#ifdef MALLOC_DEBUG
	printf("[krealloc]Requesting %d blocks, %d bytes, from 0x%p/%d (%d allocated)\n", blocksNeeded, (int)size, ptr, firstBlock, getBlock(firstBlock));
	#endif
	
	if (ptr == NULL || getBlock(firstBlock) == 0) {
		//printf("[krealloc]allocating from NULL -> kmalloc\n");
		return kmalloc(size);
	}
	if (size == 0 && getBlock(firstBlock) != 0) {
		kfree(ptr);
		return NULL;
	}
	
	// check if more or less are needed
	if (getBlock(firstBlock) > blocksNeeded) {
		int i=0;
		for (i=firstBlock; getBlock(i) > 0; i++) {
			int toAlloc = blocksNeeded+firstBlock-i;
			setBlock(i, (toAlloc>0)?toAlloc:0);
		}
		return ptr;
	}
	// check if nothing to do
	if (getBlock(firstBlock) == blocksNeeded) {
		return ptr;
	}
	
	void* newptr = kmalloc(size);
	if (newptr == NULL) { // not enough memory
		#ifdef MALLOC_DEBUG
		printf("[krealloc]Not enough memory\n");
		#endif
		for (;;);
		return NULL;
	}
	// copy to new location
	size_t oldsize = getBlock(firstBlock)*MALLOC_BLOCK_SIZE;
	size_t i;
	/*for (i=0; i<oldsize; i+=sizeof(char)) {
		((char*)newptr)[i] = ((char*)ptr)[i];
	}*/
	memmove(newptr, ptr, oldsize);
	kfree(ptr);
	
	return newptr; // not enough space - don't ask
}

void kfree(void* m) {
	block_index firstBlock = addressBlock(m);
	block_index allocated = getBlock(firstBlock);
	#ifdef MALLOC_DEBUG
	printf("[kfree]Freeing %d (0x%p), %d blocks allocated\n", (int)firstBlock, m, (int)allocated);
	#endif
	if (allocated == 0) {
		return; // double free, just ignore. Might use traps on this one tho.
	}
	int i;
	for (i=firstBlock; i<(firstBlock+allocated); i++) {
		#ifdef MALLOC_DEBUG
		printf("  %d: %d -> 0\n", i, getBlock(i));
		#endif
		if (getBlock(i) == 0)
			break;
		setBlock(i, 0);
	}
}

