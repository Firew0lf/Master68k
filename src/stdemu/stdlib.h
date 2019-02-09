#ifdef __cplusplus
extern "C" {
#endif

#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>
#include <malloc.h>

#define EXIT_SUCCESS	0
#define EXIT_FAILURE	-1

#define RAND_MAX	100
#define MB_CUR_MAX	256

double strtod(const char* str, char** endptr);
long int strtol(const char *str, char** endptr, int base);
unsigned long int strtoul(const char *str, char** endptr, int base);

void abort(void);

char* getenv(const char* name);
int system(const char* string);

#define malloc kmalloc
#define realloc krealloc
#define free kfree

void exit(int status);
int abs(int x);

int rand(void);
void srand(unsigned int seed);

#endif

#ifdef __cplusplus
}
#endif
