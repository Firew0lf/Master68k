#include <stdio.h>

#include "malloc.h"
#include "iostream.h"
#include "irq.h"
#include "trap.h"

//#define K_MEMTEST
//#define K_MISCTEST
#define K_VERBOSE // doesn't affect tests

extern char _KERNEL_START[];
extern char _KERNEL_END[];
extern char _KRAM_START[];
extern char _KSRAM_END[];
extern char _KRAM_END[];

static volatile char* IN  = (char*)(0x060000);
static volatile char* OUT = (char*)(0x060008);

void kputc(char c) {
	*OUT = c;
}

int kgetc() {
	setIRQLevel(0);
	while (!isSerialAvailable());
	*OUT = getSerialData();
	return getSerialData();
}

int __attribute((weak)) main(int argc, char** argv) {
	printf("No main() function provided, so I'm just gonna count up to 10\n");
	int i;
	for (i=0; i<11; i++) {
		printf("%d ", i);
	}
	printf("\nDone\n");
	return 0;
}

void kernel_main(void) {
	// init everything
	iostream_setputc(kputc);
	iostream_setgetc(kgetc);
	#ifdef K_VERBOSE
	printf("KSTART: 0x%p | KEND: 0x%p\nRAMSTART: 0x%p | SRAMEND: 0x%p | RAMEND: 0x%p\n", _KERNEL_START, _KERNEL_END, _KRAM_START, _KSRAM_END, _KRAM_END);
	printf("Free memory: %dB\n", (size_t)(_KRAM_END - _KSRAM_END));
	#endif
	
	setIRQLevel(7);
	int i;
	#ifdef K_MEMTEST
	printf("Memtest...\n");
	for (i=(int)_KSRAM_END; i<(int)_KRAM_END; i++) {
		*((unsigned char*)i) = (i%0xfd)+1;
	}
	for (i=(int)_KSRAM_END; i<(int)_KRAM_END; i++) {
		if (*((unsigned char*)i) != ((i%0xfd)+1)) {
			printf("Memory error at 0x%x: expected %d, got %d\n", i, (i%0xfd)+1, *((unsigned char*)i));
		}
		//*((unsigned char*)i) = 0;
	}
	#endif
	
	malloc_init(_KSRAM_END, (size_t)(_KRAM_END - _KSRAM_END));
	#ifdef K_VERBOSE
	printf("malloc blocks: %d, %dB each\n", malloc_blocksCount(), MALLOC_BLOCK_SIZE);
	printf("=> %dB allocatable memory\n", malloc_blocksCount()*MALLOC_BLOCK_SIZE);
	#endif
	
	setIRQLevel(0);
	
	#ifdef K_MISCTEST
	// test all the ports !!!
	char c = 'a';
	for (;c<='z';c++) {
		*OUT = c;
	}
	printf("\nABC passed\n");
	printf("Test string: %s\n", "test string");
	
	char* charlist = kmalloc(128);
	if (charlist == NULL) {
		printf("Couldn't allocate memory, terminating.\n");
		return;
	}
	for (i=0; i<128; i++) {
		charlist[i] = (char)i;
	}
	for (i=0; i<128; i++) {
		if (charlist[i] != i) {
			printf("Memory access error at %p\n", &charlist[i]);
			return;
		}
	}
	kfree(charlist);
	printf("Memory allocation passed, pointing at 0x%p\n", charlist);
	
	printf("Type any character to test I/O, press [Enter] to continue\n");
	for(;;) {
		if (isSerialAvailable()) {
			char c = getSerialData();
			printf("%c", c);
			if (c == '\n')
				break;
		}
	}
	printf("Mirror test passed\n");
	#endif
	
	char* argv[] = {""};
	main(0, argv);
	
	for(;;);
}
