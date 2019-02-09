#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include <ncurses.h>

#include "m68k.h"

// Memory
#define MAX_ADDR 0xffffff
#define RAM_BASE 0x100000
#define RAM_SIZE 0x200000
#define ROM_BASE 0x000000
//#define ROM_SIZE 0x040000

// Peripherals
#define ATA_BASE 0x040000
#define TEXT_IN  0x060000
#define TEXT_OUT 0x060008

int run = 1;

int romsize;
unsigned char* romdata;
unsigned char* ramdata;

void stawp(int sig) {
	switch (sig) {
		case SIGINT:
			printf("\nInterrupted.\n");
			break;
		case SIGTERM:
			printf("\nTerminated.\n");
			break;
	}
	free(romdata);
	free(ramdata);
	printf("[EMU]Free'd ROM and RAM data.\n");
	run = 0;
	printf("[EMU]Halted CPU.\n");
}

int irqLevel = 0;

WINDOW* console;
FILE* logfile = NULL;
void console_write(char val) {
	//printf("%c", val);
	//fflush(stdout);
	//wprintw(console, "%c", val);
	if (logfile != NULL) {
		fputc(val, logfile);
	}
	waddch(console, val);
	wrefresh(console);
}

// READ
unsigned int m68k_read_memory_8(unsigned int address) {
	// Text in
	if (address >= TEXT_IN && address < (TEXT_IN+0x8)) {
		m68k_set_irq(M68K_IRQ_NONE);
		irqLevel = 0;
		
		int c = getch();
		if (c > 0) {
			return c%256;
		}
		return 0;//0;
	}
	// Text out
	else if (address == TEXT_OUT && address < (TEXT_OUT+0x8)) {
		return 0;
	}
	// RAM read
	else if (address >= RAM_BASE && address < RAM_BASE+RAM_SIZE) {
		return ramdata[address-(RAM_BASE)];
	}
	// ROM read
	else if (address >= ROM_BASE && address < ROM_BASE+romsize) {
		return romdata[address];
	}
	
	printw("[EMU]Bus error: 0x%x\n", address);
	run = 0;
	return 0;
}

unsigned int m68k_read_memory_16(unsigned int address) {
	return m68k_read_memory_8(address+1) + (m68k_read_memory_8(address)<<8);
}
unsigned int m68k_read_memory_32(unsigned int address) {
	return m68k_read_memory_16(address+2) + (m68k_read_memory_16(address)<<16);
}

// DISASM READ
unsigned int m68k_read_disassembler_8(unsigned int address) {
	return m68k_read_memory_8(address);
}

unsigned int m68k_read_disassembler_16(unsigned int address) {
	return m68k_read_memory_16(address);
}

unsigned int m68k_read_disassembler_32(unsigned int address) {
	return m68k_read_memory_32(address);
}

// WRITE
void m68k_write_memory_8(unsigned int address, unsigned int value) {
	if (address >= RAM_BASE && address < RAM_BASE+RAM_SIZE) {
		ramdata[address-(RAM_BASE)] = value;
	} else if (address == TEXT_IN) {
		
	} else if (address == TEXT_OUT) {
		console_write((char)(value&0xff));
	}
}
void m68k_write_memory_16(unsigned int address, unsigned int value) {
	m68k_write_memory_8(address+1, value&0xff);
	m68k_write_memory_8(address, (value&0xff00)>>8);
}
void m68k_write_memory_32(unsigned int address, unsigned int value) {
	m68k_write_memory_16(address+2, value&0xffff);
	m68k_write_memory_16(address, (value&0xffff0000)>>16);
}

int main(int argc, char* argv[]) {
	signal(SIGINT, stawp);
	signal(SIGTERM, stawp);
	
	FILE* rom = NULL;
	
	if (argc < 2) {
		printf("Usage: %s <rom file>\n", argv[0]);
		return 1;
	}
	
	for (int i=1; i<argc; i++) {
		if (argv[i][0] == '-') { // parameter
			switch (argv[i][1]) {
				case 'l':
					logfile = fopen("emu.log", "w");
					if (logfile != NULL) {
						printf("[EMU]Enabled logging\n");
					} else {
						printf("Can't open emu.log\n");
						return 1;
					}
					break;
				
				default:
					printf("Invalid argument: %s\n", argv[i]);
					break;
			}
		} else if (rom == NULL) {
			rom = fopen(argv[i], "r");
			if (rom == NULL) {
				printf("No such file: %s\n", argv[i]);
				return 1;
			}
		} else {
			printf("Invalid argument: %s\n", argv[i]);
		}
	}
	if (rom == NULL) {
		printf("No rom file");
		return 1;
	}
	
	fseek(rom, 0, SEEK_END);
	romsize = ftell(rom);
	printf("[EMU]Rom file size: %d bytes\n", romsize);
	fseek(rom, 0, SEEK_SET);
	
	ramdata = malloc(RAM_SIZE);
	if (ramdata == NULL) {
		printf("Failed to allocate RAM space. Exiting.\n");
		fclose(rom);
		return 1;
	}
	printf("[EMU]Allocated RAM data.\n");
	
	romdata = malloc(romsize);
	if (romdata == NULL) {
		printf("Failed to allocate ROM space. Exiting.\n");
		fclose(rom);
		free(ramdata);
		return 1;
	}
	printf("[EMU]Allocated ROM data.\n");
	
	for (int i=0; i<romsize;i++) {
		if (i < RAM_SIZE) {
			romdata[i] = fgetc(rom);
		} else if (ROM_BASE+i >= RAM_BASE) {
			ramdata[(i+ROM_BASE) - RAM_BASE]; // could be an external elf loader in real circuits
		}
	}
	fclose(rom);
	printf("[EMU]Loaded ROM data.\n");
	
	initscr();
	raw();
	//keypad(stdscr, TRUE);
	noecho();
	cbreak();
	//scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	
	console = newwin(0, 0, 1, 0);
	scrollok(console, TRUE);
	
	WINDOW* statusWin = newwin(1, 0, 0, 0);
	wattron(statusWin, A_REVERSE);
	//halfdelay(1);
	
	m68k_init();
	m68k_set_cpu_type(M68K_CPU_TYPE_68010);
	m68k_pulse_reset();
	
	char* statusLine = malloc(80);
	if (statusLine == NULL) {
		printw("[EMU]Not enough memory\n");
		run = 0;
	}
	while(run) {
		m68k_execute(100);
		
		if (irqLevel == 0) {
			int ch = getch();
			if (ch != ERR) {
				ungetch(ch);
				m68k_set_irq(M68K_IRQ_1);
				irqLevel = 1;
			}
		}
		
		snprintf(statusLine, 80, "PC: %06X | SP: %06X", m68k_get_reg(NULL, M68K_REG_PC), m68k_get_reg(NULL, M68K_REG_SP));
		mvwprintw(statusWin, 0, 0, statusLine);
		wrefresh(statusWin);
	}
	
	printw("[EMU]Stopping emulation, press [ENTER] to continue\n");
	for (;;) {
		int ch = getch();
		if (ch == '\n') {
			break;
		}
	}
	
	delwin(statusWin);
	delwin(console);
	endwin();
	if (logfile != NULL)
		fclose(logfile);
	
	printf("[EMU]Stopped emulation.\n");
	
	return 0;
}
