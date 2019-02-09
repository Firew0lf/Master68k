/*
Still massively //TODO
*/

#include <math.h>

// trigo

double cos(double x) {
	return 1.0 - (x*x)/2.0 + (x*x*x*x)/24.0;
}

double sin(double x) {
	return x - (x*x*x)/6.0 + (x*x*x*x*x)/120.0;
}

double tan(double x) {
	return sin(x)/cos(x);
}

double acos(double x) {
	return 0.0;
}

double asin(double x) {
	return 1.0;
}

double atan(double x) {
	return 0.0;
}

double atan2(double y, double x) {
	return 0.0;
}

// hyperbolic
double cosh(double x) {
	return (exp(x)+exp(-x))/2.0;
}

double sinh(double x) {
	return (exp(x)-exp(-x))/2.0;
}

double tanh(double x) {
	return sinh(x)/cosh(x);
}

// exp
double exp(double x) {
	return 1.0 + x + (x*x)/2.0 + (x*x*x)/6.0;
}

double frexp(double x, int* exponent) {
	*exponent = (x==0)?0:(int)(1 + log2(x));
	return ldexp(x, 2);
}

double ldexp(double x, int exponent) {
	return x*(1<<exponent);
}

double log(double x) {
	double omx = 1.0 - x;
	return -(x + (x*x)/2.0 + (x*x*x)/3.0 + (x*x*x*x)/4.0);
}

double log2(double x) {
	return log(x)/log(2.0);
}

double log10(double x) {
	return log(x)/log(10.0);
}

// things

double modf(double x, double* integer) {
	*integer = x-fmod(x, 1.0);
	return fmod(x, 1.0);
}

double pow(double x, double y) {
	return exp(y*log(x));
}

double sqrt(double x) {
	return exp(0.5*log(x));
}

double ceil(double x) {
	if (floor(x) == x) {
		return x;
	}
	return floor(x)+1.0;
}

double fabs(double x) {
	return (x<0)?-x:x;
}

double floor(double x) {
	int xi = (int)x;
	return (double)xi; // kinda works
}

double fmod(double x, double y) {
	return x-floor(x/y)*y;
}
