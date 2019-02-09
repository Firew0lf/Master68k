#ifdef __cplusplus
extern "C" {
#endif

#ifndef MATH_H
#define MATH_H

#include <stdint.h>

/* typedefs
typedef double double_t;
typedef float  float_t;*/

#ifndef MATH_PI
#define MATH_PI 3.1415926535898
#endif

#ifndef MATH_E
#define MATH_E 2.718281828459
#endif

const static union {uint64_t i; double f;} _HUGE_BITS __attribute__((used)) = {0x7FF0000000000000}; // positive infinity double
#define HUGE_VAL (_HUGE_BITS.f)

// trigo
double cos(double x);
double sin(double x);
double tan(double x);

double acos(double x);
double asin(double x);
double atan(double x);
double atan2(double y, double x);

// hyperbolic
double cosh(double x);
double sinh(double x);
double tanh(double x);

double acosh(double x);
double asinh(double x);
double atanh(double x);

// exp/log
double exp(double x);
double frexp(double x, int *exponent);
double ldexp(double x, int exponent);
double log(double x);
double log2(double x);
double log10(double x);

// things
double modf(double x, double* integer);
double mod(double x, double *integer);
double pow(double x, double y);
double sqrt(double x);

double ceil(double x);
double fabs(double x);
double floor(double x);
double fmod(double x, double y);

#endif

#ifdef __cplusplus
}
#endif
