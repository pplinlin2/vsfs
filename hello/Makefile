BIN := test.bin
ELF := test.elf

CROSS_COMPILE := arm-linux-gnueabi-
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy

CPU  := arm926ej-s
QEMU := qemu-system-arm
INSTALL := sudo apt-get install

all: $(BIN)
	@echo 'done'

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $^ $@

$(ELF):
	$(AS) -mcpu=$(CPU) startup.s -o startup.o
	$(CC) -c -mcpu=$(CPU) test.c -o test.o
	$(LD) -T test.ld test.o startup.o -o $@

.PHONY: qemu check clean
qemu:
	@echo 'Press "Ctrl + a" and then "x" to exit'
	$(QEMU) -M versatilepb -nographic -kernel $(BIN)

check:
	$(INSTALL) gcc-arm-linux-gnueabi
	$(INSTALL) $(QEMU)
	
clean:
	rm *.o $(BIN) $(ELF)
