# Master68k

M68k minimum code library to run some C/C++ applications.

## What's this ?

*This* is a piece of code aiming to:
 * recreate the C standard library using only what compilers for embeded systems usually provide
 * provide some low-level code specifically for the m68k

## What's done:

STDEmu:
 * [x] Memory allocation (could be more efficient)
 * [x] ctype.h
 * [ ] Everything else

Kernel:
 * [ ] Filesystem/devices support

M68k code:
 * [x] Interrupts

## What it can run:
 * You may be able to launch the [Squirrel](http://www.squirrel-lang.org/) interpreter and run *very* basic code

## Setting up

### Emulator

If you don't have an emulator already set up, you can use the one in this repo.
It is based on [Musashi](https://github.com/kstenerud/Musashi) and ncurses.
Download the musashi repo in the `emu/` directory, without overriding `m68kconf.h`, then:
```
gcc m68kmake.c -o m68kmake
./m68kmake
```
to setup the emulator code, and
```
./build.sh
```
to build the emulator itself.

### Kernel

If you don't already have a C compiler for the `m68k-elf`, GCC will do the job.
You can either build it yourself or download it [here](http://newos.org/toolchains/m68k-elf-8.2.0-Linux-x86_64.tar.xz) (found it on osdev wiki).
Then add it to your path with an `export PATH="${PATH}:**your path here**"` in your `.bashrc` (or equivalent).

Now you can run
```
make
```
to build the kernel. Note that you may need a Lua interpreter to complete the process
without error, but if you don't have one and don't want to install it, you can comment
the corresponding line in `Makefile`, the ROM might just be bigger.

Then run
```
make emulate
```
to test it on the emulator you just built

## (Trying to) run some code

By default, the kernel will run a weak `main` function. You can define another
one in any other file, and it will run instead. Copy-pasting some pre-made code
in the `src/` directory should work.

## Modifying the memory map and peripherals access

For some reason, you may want to run this on real hardware or increase the available
RAM of the emulated system.

### Kernel memory map

It's defined in `link.ld`. `brom`'s origin should always be 0, as that's how m68k
works. `kram` can be anywhere and of any size, just run
```
make clean
make
```
when you change anything.

The input/output ports and functions are defined in `kernel.c` and `irq.c`, you
may want to change it if you run on it real hardware.

### Emulator memory map

Everything is defined in the `#define`s, `m68k_read_memory_8` and `m68k_write_memory_8`.
