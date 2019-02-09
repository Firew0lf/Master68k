#ifdef __cplusplus
extern "C" {
#endif

#ifndef STRING_H
#define STRING_H

#include <stddef.h>

void* memchr(const void *str, int c, size_t n);
int memcmp(const void *str1, const void *str2, size_t n);
void* memcpy(void* dest, const void* str, size_t n);
void* memmove(void* dest, const void* str, size_t n);
void* memset(void* str, int c, size_t n);

char* strchr(const char *str, int c);
int strcmp(const char* str1, const char* str2);
#define strcoll strcmp
int strncmp(const char* str1, const char* str2, size_t n);
char* strcpy(char* dest, const char* src);
char* strerror(int errnum);
size_t strlen(const char* str);
char* strpbrk(const char* str1, const char* str2);
char* strrchr(const char* str, int c);
size_t strspn(const char* str1, const char* str2);
char* strstr(const char* haystack, const char* needle);

#endif

#ifdef __cplusplus
}
#endif
