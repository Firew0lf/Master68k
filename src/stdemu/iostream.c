#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

#include <string.h>
#include <stdlib.h>

#include "iostream.h"

#ifndef EOF
#define EOF -1
#endif

static void (*putc)(char) = NULL;
static int  (*getc)(void) = NULL;
static int  (*ungetc)(int) = NULL;

void iostream_setputc(void (*f)(char)) {
	putc = f;
}

void iostream_setgetc(int (*f)(void)) {
	getc = f;
}

void iostream_setungetc(int (*f)(int)) {
	ungetc = f;
}

void iostream_putc(char c) {
	putc(c);
}

int iostream_getc(void) {
	return getc();
}

int iostream_ungetc(int c) {
	return ungetc(c);
}

/******************
* Printing things *
******************/

void iostream_printstr(const char* str) {
	int i;
	for (i=0; str[i]; i++) {
		putc(str[i]);
	}
}

static const char numchar[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
void iostream_printnum(long n, int base) {
	if (n==0) {
		putc('0');
		return;
	}
	
	if (n<0) {
		putc('-');
		n = -n;
	}
	// check how long will the number be
	size_t numsize = -1;
	int d = n; // divised number
	while (d > 0) {
		d /= base;
		numsize++;
	}
	
	// write the number, without any malloc
	int c; // current character
	int i;
	for (c=numsize; c; c--) {
		// divide the number c times
		d = n;
		for (i=0; i<c; i++) {
			d /= base;
		}
		// print the digit
		putc(numchar[d%base]);
	}
	putc(numchar[n%base]);
}

static int countFormats(const char* str) {
	int c = 0;
	int i;
	for (i=0; str[i]; i++) {
		if (str[i] == '%') {
			c++;
		}
	}
	return c;
}

int iostream_printf(const char* str, ...) {
	int fcount = countFormats(str);
	if (fcount == 0) {
		iostream_printstr(str);
		return strlen(str);
	}
	va_list args;
	va_start(args, str);
	
	size_t i;
	int f = 0;
	for (i=0; str[i]; i++) {
		if (str[i] == '%') {
			i++;
			switch (str[i]) {
				case 'l': // long
					i++; // should be "%ld"
					iostream_printnum(va_arg(args, long), 10);
					break;
				
				case 'd': // decimal number
					iostream_printnum(va_arg(args, int), 10);
					break;
				
				case 'x': // hexadecimal number
					iostream_printnum(va_arg(args, int), 16);
					break;
				
				case 'b': // binary number, not standard
					iostream_printnum(va_arg(args, int), 2);
					break;
				
				case 'p': // pointer
					iostream_printnum((int)va_arg(args, void*), 16);
					break;
				
				case 's': // string
					iostream_printstr(va_arg(args, char*));
					break;
				
				case 'c': // character
					putc((char)va_arg(args, int));
					break;
				
				default:
					break; // I don't know this pokemon
			}
			f++;
		} else {
			putc(str[i]);
		}
	}
	va_end(args);
	return strlen(str); // I'm cheating here
}

/*****************
* Getting things *
*****************/

char* iostream_readline(char* buf, size_t maxlen) {
	if (buf == NULL) {
		buf = malloc(maxlen+1);
		if (buf == NULL) {
			return NULL; // couldn't allocate memory
		}
	}
	int readchar = 0;
	size_t i = 0;
	while (i < maxlen-1) {
		int readchar = getc();
		if (readchar == '\n' || readchar == EOF) break;
		buf[i] = (char)readchar;
		putc(readchar);
		i++;
	}
	buf[i] = 0;
	return buf;
}

int iostream_scanf(const char* format, ...) {
	va_list args;
	va_start(args, format);
	size_t i;
	size_t len = 0;
	for (i=0; format[i]; i++) {
		if (format[i] == ' ') { // whitespace
			int c;
			while ((c = getc()) != ' ' && c != '\n' && c != '\t' && c != EOF) len++;
			ungetc(c);
		} else if (format[i] == '%') {
			i++;
			switch (format[i]) {
				case 'c': // single character
					*va_arg(args, char*) = (char)getc();
					break;
				
				case 's':
					iostream_readline(va_arg(args, char*), 1024);
					break;
				
				default:
					break;
			}
		}
	}
	va_end(args);
	return 0;
}
