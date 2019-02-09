#ifndef IOSTREAM_H
#define IOSTREAM_H

#include <stdarg.h>
#include <stddef.h>

void iostream_setputc(void (*f)(char));
void iostream_setgetc(int  (*f)(void));
void iostream_putc(char c);
int iostream_getc(void);

void iostream_printstr(const char* str);
void iostream_printnum(long n, int base);
int iostream_printf(const char* str, ...);

char* iostream_readline(char* buf, size_t maxlen);

#endif
