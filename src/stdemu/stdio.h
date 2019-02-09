#ifdef __cplusplus
extern "C" {
#endif

#ifndef STDIO_H
#define STDIO_H

#include <stddef.h>
#include <stdarg.h>

#include "iostream.h"

typedef struct{} FILE;

#define _IOFBF 1
#define _IOLBF 2
#define _IONBF 2

#define BUFSIZ    512
#define EOF       -1
#define FOPEN_MAX 0 // TODO
#define FILENAME_MAX 12
#define L_tmpnam FILENAME_MAX
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 3
#define TMP_MAX 0

/*FILE* stderr = (FILE*)1;
FILE* stdin = (FILE*)2;
FILE* stdout = (FILE*)3;*/
#define stderr ((FILE*)1)
#define stdin  ((FILE*)2)
#define stdout ((FILE*)3)

// FILE* functions
int fclose(FILE* stream);
FILE* fopen(const char *filename, const char *mode);
FILE* freopen(const char* filename, const char* mode, FILE* stream);
FILE* tmpfile(void);

size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);

int fgetc(FILE* stream);
//int getc(FILE* stream);
#define getc fgetc
int putc(int c, FILE* stream);
int ungetc(int c, FILE* stream);

void clearerr(FILE *stream);
int feof(FILE* stream);
int ferror(FILE* stream);
int fflush(FILE* stream);
long int ftell(FILE* stream);
int fseek(FILE* stream, long int offset, int whence);

int fputs(const char* str, FILE* stream);
char* fgets(char* str, int n, FILE* stream);

int setvbuf(FILE* stream, char* buffer, int mode, size_t size);

// FS functions
int remove(const char* filename);
int rename(const char* old_filename, const char* new_filename);

// tmp name functions
char* tmpnam(char* str);

// functions

//int printf(const char *format, ...);
#define printf iostream_printf
int sprintf(char* str, const char* format, ...);
int snprintf(char* str, size_t n, const char* format, ...);
int vsnprintf(char* str, size_t n, const char* format, va_list arg);
//int fprintf(FILE* f, const char* format, ...);
#define fprintf(a,...) iostream_printf(__VA_ARGS__)

int vprintf(const char* format, va_list arg);
int vsprintf(const char* format, va_list arg);
int vfprintf(FILE* f, const char* format, va_list arg);

int fscanf(FILE *f, const char* format, ...);
int sscanf(const char* str, const char* format, ...);
int scanf(const char* format, ...);

//int snprintf(char* s, size_t n, const char* format, ...);

void perror(const char *str);

#define getchar iostream_getc

#endif

#ifdef __cplusplus
}
#endif
