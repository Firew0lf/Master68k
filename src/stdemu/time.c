#include "time.h"

clock_t clock(void) {
	return 1; // TODO processor time interrupt
}

double difftime(time_t time1, time_t time2) {
	return (double)(time2 - time1);
}

struct tm* gmtime(const time_t* timer) {
	return NULL;
}

struct tm* localtime(const time_t* timer) {
	return gmtime(timer); // GMT rules, at least it did in the 70's
}

time_t mktime(struct tm* timeptr) {
	return 1;
}

size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr) {
	str[0] = 0;
	return 0;
}

time_t time(time_t* timer) {
	return 1; // January 1st, 1970, 00h00m01s
}
