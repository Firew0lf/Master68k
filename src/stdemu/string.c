#include <string.h>
#include <stdlib.h>

#ifdef STRING_H_DEBUG
#include <stdio.h>
#endif

void* memchr(const void* str, int c, size_t n) {
	size_t i;
	for (i=0; i<n; i++) {
		if (((const unsigned char*)str)[i] == (unsigned char)c) {
			return (void*)(str+i);
		}
	}
	return NULL;
}

int memcmp(const void* str1, const void* str2, size_t n) {
	size_t i;
	#ifdef STRING_H_DEBUG
	printf("memcmp(%s, %s): ", str1, str2);
	#endif
	for (i=0; i<n; i++) {
		if (((const char*)str1)[i] != ((const char*)str2)[i]) {
			#ifdef STRING_H_DEBUG
			printf("%d\n", ((const char*)str1)[i] - ((const char*)str2)[i]);
			#endif
			return ((const char*)str1)[i] - ((const char*)str2)[i];
		}
	}
	#ifdef STRING_H_DEBUG
	printf("0\n");
	#endif
	return 0;
}

void* memcpy(void* dest, const void* src, size_t n) {
	size_t i;
	for (i=0; i<n; i++) {
		((unsigned char*)dest)[i] = ((const unsigned char*)src)[i];
	}
	return dest;
}

void* memmove(void* dest, const void* src, size_t n) {
	unsigned char* buff = malloc(n);
	if (buff == NULL) {
		return NULL;
	}
	size_t i;
	for (i=0; i<n; i++) {
		buff[i] = ((unsigned char*)src)[i];
	}
	for (i=0; i<n; i++) {
		((unsigned char*)dest)[i] = buff[i];
	}
	free(buff);
	return dest;
}

void* memset(void* str, int c, size_t n) {
	size_t i;
	for (i=0; i<n; i++) {
		((char*)(str))[i] = (char)c;
	}
	return str;
}

char* strchr(const char* str, int c) {
	return (char*)memchr(str, c, strlen(str));
}

int strcmp(const char* str1, const char* str2) {
	size_t s1 = strlen(str1);
	size_t s2 = strlen(str2);
	return memcmp(str1, str2, (s1<s2)?s1:s2);
}

int strncmp(const char* str1, const char* str2, size_t n) {
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	if (len1 < n) {
		n = len1;
	}
	if (len2 < n) {
		n = len2;
	}
	return memcmp(str1, str2, n);
}

char* strcpy(char* dest, const char* src) {
	memcpy(dest, src, strlen(src)+1);
	return dest;
}

char* strerror(int errnum) {
	switch (errnum) {
		case 0:
			return "no error";
	}
	
	return "error";
}

size_t strlen(const char* str) {
	size_t i;
	for (i=0; str[i]; i++);
	return i;
}

char* strpbrk(const char* str1, const char* str2) {
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t i;
	size_t j;
	for (i=0; i<len1; i++) {
		for (j=0; j<len2; j++) {
			if (str1[i] == str2[j]) {
				return (char*)&(str1[i]);
			}
		}
	}
	return NULL;
}

char* strrchr(const char* str, int c) {
	size_t len = strlen(str);
	size_t i;
	for (i=len; i>=0; i--) {
		if (str[i] == c) {
			return (char*)&str[i];
		}
	}
	return NULL;
}

size_t strspn(const char* str1, const char* str2) {
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t out = 0;
	size_t i;
	while (out < len1) {
		char isIn2 = 0;
		for (i=0; i<len2; i++) {
			if (str1[out] == str2[i]) {
				isIn2 = 1;
				break;
			}
		}
		if (!isIn2) {
			return out;
		}
		out++;
	}
	return len1;
}

char* strstr(const char* haystack, const char* needle) {
	size_t len1 = strlen(haystack);
	size_t len2 = strlen(needle);
	size_t i, j; // haystack pointer, needle pointer
	for (i=0; i<(len2-len1+1); i++) {
		for (j=0; j<len2; j++) {
			if (haystack[i+j] != needle[j])
				break;
		}
		if (j == len2)
			return ((char*)(haystack+i));
	} 
	return NULL;
}
