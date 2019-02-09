ENTRY(_start)

MEMORY {
  brom (rx) : ORIGIN = 0x000000, LENGTH = 512K
  kram (wx) : ORIGIN = 0x100000, LENGTH = 2M
}

SECTIONS {
	. = 0;
	
	_KERNEL_START = SEGMENT_START(.text, .);
	
	.text BLOCK(1K) : ALIGN(1K) {
		. = 0;
	 	*(.vectors)
		. = 1024;
		*(.text)
	} > brom
	
	.rodata BLOCK(1K) : ALIGN(1K) {
		*(.rodata)
	} > brom
	
	_KERNEL_END = .;
	
	. = ORIGIN(kram);
	
	_KRAM_START = .;
	
	.data : ALIGN(1K) {
		*(.data)
	} > kram
	
	.bss : ALIGN(1K) {
		*(COMMON)
		*(.stack)
		*(.bss)
	} > kram
	
	_KSRAM_END = .;
	
	. = ORIGIN(kram)+LENGTH(kram);
	
	_KRAM_END = .;
}
