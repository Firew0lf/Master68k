#ifdef __cplusplus
extern "C" {
#endif

#ifndef TIME_H
#define TIME_H

#include <stdint.h>
#include <stdlib.h>

#define CLOCKS_PER_SEC 1000000 // should change, maybe I'll set it as a variable ?

typedef uint32_t clock_t;
typedef uint32_t time_t;

struct tm {
	int tm_sec; // 0 to 59
	int tm_min; // 0 to 59
	int tm_hour; // 0 to 23
	int tm_mday; // 1 to 31
	int tm_mon; // 0 to 11
	int tm_year; // since 1900
	int tm_wday; // 0 to 6
	int tm_yday; // 0 to 365
	int tm_isdst; // daylight saving time
};

time_t is;

char* asctime(const struct tm *timeptr);
clock_t clock(void);
char* ctime(const time_t* timer);
double difftime(time_t time1, time_t time2);
struct tm* gmtime(const time_t* timer);
struct tm *localtime(const time_t* timer);
time_t mktime(struct tm *timeptr);
size_t strftime(char* str, size_t maxsize, const char* format, const struct tm* timeptr);
time_t time(time_t* timer);

#endif

#ifdef __cplusplus
}
#endif
