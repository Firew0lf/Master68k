#ifdef __cplusplus

#include <stdio.h>

extern "C" {
	void __cxa_pure_virtual() {
		printf("__cxa_pure_virtual()\n");
	}
}
#endif
