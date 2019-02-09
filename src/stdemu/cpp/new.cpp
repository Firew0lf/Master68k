#include "new"

#include <stdio.h>

void* operator new(size_t size) {
	return malloc(size);
}

void* operator new(size_t size, void* ptr) {
	return ptr;
}

void operator delete(void* ptr) {
	free(ptr);
}

void operator delete(void* ptr, unsigned long st) {
	free(ptr);
}
