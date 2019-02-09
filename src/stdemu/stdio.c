#include <string.h>
#include <stdio.h>
#include "iostream.h"

static const char* charplaceholder = "DUCK";

int fclose(FILE* stream) {
	return 0;
}

FILE* fopen(const char *filename, const char *mode) {
	return NULL; // No filesystem, what did you expect ?
}

FILE* freopen(const char* filename, const char* mode, FILE* stream) {
	return NULL;
}

FILE* tmpfile(void) {
	return NULL;
}

size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream) {
	strcpy(ptr, charplaceholder);
	return 0;
}

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream) {
	if (stream == stdout) {
		size_t i;
		for (i=0; i<size*nmemb; i++) {
			iostream_putc(((char*)ptr)[i]);
		}
	}
	return 0;
}

int fgetc(FILE* stream) {
	return 0;
}

int putc(int c, FILE* stream) {
	return c;
}

int ungetc(int c, FILE* stream) {
	return c;
}

void clearerr(FILE* stream) {

}

long int ftell(FILE* stream) {
	return 0;
}

int fseek(FILE* stream, long int offset, int whence) {
	return 0;
}

int fputs(const char* str, FILE* stream) {
	if (stream == stdout) {
		iostream_printf(str);
		return strlen(str);
	}
	return 1;
}

char* fgets(char* str, int n, FILE* stream) {
	if (stream == stdin) {
		return iostream_readline(str, n);
	}
	printf("[fgets]Not implemented\n");
	strcpy(str, charplaceholder);
	return str;
}

int setvbuf(FILE* stream, char* buffer, int mode, size_t size) {
	return 0;
}

int feof(FILE* stream) {
	return 0;
}

int ferror(FILE* stream) {
	return 0;
}

int fflush(FILE* stream) {
	return 0;
}

int remove(const char* filename) {
	return 0;
}

int rename(const char* old_filename, const char* new_filename) {
	return 0;
}

char* tmpnam(char* str) {
	return strcpy(str, "IMADUCK.TXT");
}

/*int fprintf(FILE *f, const char *format, ...) {
	if (f == stdout) {
		printf(format, ...);
	} else if (f == stderr) {
		printf(format, ...);
	}
	return 0;
}*/

int sprintf(char* str, const char* format, ...) {
	strcpy(str, format);
	return 0; // TODO
}

int snprintf(char* str, size_t n, const char* format, ...) {
	strcpy(str, format);
	return 0; // TODO
}

int vprintf(const char* format, va_list arg) {
	printf(format);
	return 0;
}

int vfprintf(FILE* f, const char* format, va_list arg) {
	printf(format);
}

int vsnprintf(char* str, size_t n, const char* format, va_list arg) {
	strcpy(str, format);
	return 0;
}

int fscanf(FILE *f, const char* format, ...) {
	return 0; // TODO
}
