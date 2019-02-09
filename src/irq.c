#include <stdint.h>

#include "iostream.h"
#include "irq.h"

static volatile char* IN = (char*)0x060000;
static volatile char* OUT = (char*)0x060008;

char serialAvailable = 0;
char serialData = 0;

char isSerialAvailable() {
	return serialAvailable;
}

char getSerialData() {
	serialAvailable = 0;
	return serialData;
}

char trash;

void setIRQLevel(int level) {
	level = level & (0x7);
	uint16_t SR;
	asm volatile ("movew %/sr, %0;": "=d"(SR));
	SR = (SR&(0xf8ff)) | (level<<8);
	asm volatile ("movew %0, %/sr;":: "d"(SR));
}

void __attribute__((interrupt)) irq1() {
	if (!serialAvailable) {
		serialData = IN[0];
		serialAvailable = 1;
	} else {
		trash = IN[0];
	}
}

void __attribute__((interrupt)) irq2() {
	iostream_printf("irq2\n");
}

void __attribute__((interrupt)) irq3() {
	iostream_printf("irq3\n");
}

void __attribute__((interrupt)) irq4() {
	iostream_printf("irq4\n");
}

void __attribute__((interrupt)) irq5() {
	iostream_printf("irq5\n");
}

void __attribute__((interrupt)) irq6() {
	iostream_printf("irq6\n");
}

void __attribute__((interrupt)) irq7() {
	serialData = *IN;
	serialAvailable = 1;
}
