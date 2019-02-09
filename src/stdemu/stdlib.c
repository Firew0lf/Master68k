#include <stdlib.h>
#include <string.h>
#include <ctype.h>

double strtod(const char* str, char** endptr) {
	size_t len = strlen(str);
	int digits = 0;
	int fpoint = 0; // digits after a dot
	char afterdot = 0; // set to 1 after a dot if found
	
	char isneg = (str[0]=='-')?1:0;
	size_t i = isneg;
	for (; (isdigit(str[i]) || str[i] == '.') && i < len; i++) {
		if (str[i] == '.') {
			afterdot = 1;
			continue;
		}
		digits = digits*10 + (str[i]-'0');
		if (afterdot) fpoint++;
	}
	*endptr = (char*)str+i;
	
	double out = (double)digits;
	for (i=0; i < fpoint; i++) {
		out /= 10.0;
	}
	return (isneg?-1.0:1.0)*out;
}

static const char charbase[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}; // should go to 36... ohwell
//const unsigned char maxbase = 16;
long int strtol(const char *str, char** endptr, int base) {
	if (base > (sizeof(charbase) / sizeof(char))) {
		return 0;
	}
	long int out = 0;
	char isneg = (str[0]=='-')?1:0;
	size_t i = isneg;
	for (;;i++) { // scan string one char at a time
		size_t v;
		for (v=0; v<base; v++) {
			if (str[i] == charbase[v]) {
				out *= base;
				out += v;
				break;
			}
		}
		if (v == base) break;
	}
	*endptr = (char*)str+i;
	
	return (isneg?-1:1)*out;
}

unsigned long int strtoul(const char *str, char** endptr, int base) {
	return (unsigned long int)strtoul(str, endptr, base);
}

void abort(void) {
	for (;;);
}

char* getenv(const char* name) {
	return NULL;
}

int system(const char* string) {
	return -1;
}

void exit(int status) {
	for(;;);
}

int abs(int x) {
	return (x<0)?-x:x;
}

int rand(void) {
	return 10; // chosen by tossing 10 coins and counting the tails.
	           // who's your god now
}

void srand(unsigned int seed) {
	return; // I DON'T GIVE A *beep*
}
