######################
# master68k makefile #
######################

### Directories

SOURCEROOT	= src
SOURCE		= $(shell find $(SOURCEROOT) -type d)
DATA		= $(SOURCEROOT)/data
ISODIR	= iso

### Commands

OUTPUT	= rom
TARGET	= m68k-elf

CC	= $(TARGET)-gcc
CPPC	= $(TARGET)-g++
CCLD	= $(CPPC)
CCARGS	= $(foreach dir,$(SOURCE),-I$(dir))
CCFLAGS	= -ffreestanding -O1 -m68010
CPPCFLAGS	= -fno-exceptions -fno-rtti -fno-strict-aliasing

AS	= $(TARGET)-as
ASARGS	=
ASFLAGS	=

LINKLD	= link.ld

EMULATOR	= ./emu/simu

### Automation

CFILES	= $(foreach dir,$(SOURCE),$(wildcard $(dir)/*.c))
CPPFILES = $(foreach dir,$(SOURCE),$(wildcard $(dir)/*.cpp))
ASMFILES	= $(foreach dir,$(SOURCE),$(wildcard $(dir)/*.s))
OBJ	= $(CFILES:.c=.o) $(CPPFILES:.cpp=.o) $(ASMFILES:.s=.o)

DATANAMES	= $(wildcard $(DATA)/*.dat)
DATAHEADERS = $(DATANAMES:.dat=.h)

### Targets

$(OUTPUT).bin: $(OUTPUT).elf
	$(TARGET)-objcopy -O binary --strip-all $(OUTPUT).elf $(OUTPUT).bin
	lua scripts/trimbin.lua $(OUTPUT).bin

$(OUTPUT).elf: $(DATAHEADERS) $(OBJ) $(LINKLD)
	$(CCLD) -T $(LINKLD) $(OBJ) -o $(OUTPUT).elf -nostdlib $(CCFLAGS) -lgcc

$(OUTPUT).nodebug.elf: $(OUTPUT).elf
	$(TARGET)-objcopy --strip-debug $(OUTPUT).elf $(OUTPUT).nodebug.elf

emulate: $(OUTPUT).bin
	$(EMULATOR) $(OUTPUT).bin

emu.log: $(OUTPUT).bin
	$(EMULATOR) $(OUTPUT).bin -l

clean:
	rm -f $(OBJ) $(DATAHEADERS) $(OUTPUT).bin $(OUTPUT).elf $(OUTPUT).nodebug.elf $(FLOPPY) $(ISO)

tellmesrc:
	@echo $(CFILES) $(CPPFILES) $(ASMFILES)

tellmeobj:
	@echo $(OBJ)

tellme: tellmesrc tellmeobj

%.o: %.c
	$(CC) $(CCARGS) -o $@ -c $^ $(CCFLAGS)

%.o: %.cpp
	$(CPPC) $(CCARGS) -o $@ -c $^ $(CCFLAGS) $(CPPCFLAGS)

%.o: %.s
	$(AS) $(ASARGS) $^ -o $@ $(ASFLAGS)

