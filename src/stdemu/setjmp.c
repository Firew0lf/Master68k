#include "setjmp.h"

int setjmp(jmp_buf environment) {
	return 0;
}

void longjmp(jmp_buf environment, int value) {
	// TODO
}
