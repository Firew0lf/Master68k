#include <stddef.h>
#include "locale.h"

static const struct lconv locale = {
	".",
	" ",
	"",
	"c",
	"c",
	".",
	" ",
	"",
	"+",
	"-",
	2,
	2,
	0,
	0,
	0,
	0,
	0
};

char *setlocale(int category, const char *locale) {
	return NULL;
}

struct lconv *localeconv(void) {
	return ((struct lconv*)&locale);
}
