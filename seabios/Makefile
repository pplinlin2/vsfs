INSTALL := sudo apt-get install
QEMU    := qemu-system-x86_64

VNCIP   := *-external ip-*
VNCPORT := 7

DFLAG   := -chardev stdio,id=seabios -device isa-debugcon,iobase=0x402,chardev=seabios
DLEVEL  := 3
TFLAG   := -boot order=cd -cdrom Core-current.iso

TEST_ISO := http://distro.ibiblio.org/tinycorelinux/5.x/x86/release/Core-current.iso
BIOS_DIR := seabios-1.8.2
BIOS_WEB := http://code.coreboot.org/p/seabios/downloads/get/
BIOS_TAR := $(BIOS_DIR).tar.gz
BIOS_BIN := out/bios.bin

all:
	@echo 'usage:'
	@echo '  make check'
	@echo '  make build'
	@echo '  make qemu:  Run bios.bin for debugging'
	@echo '  make qemu2: Run real vm'

build:
	make -C $(BIOS_DIR) defconfig
	sed -i 's/CONFIG_DEBUG_LEVEL=.*/CONFIG_DEBUG_LEVEL=3/g' $(BIOS_DIR)/.config
	make -C $(BIOS_DIR)

test:
	ifconfig 

qemu:
	$(QEMU) -bios $(BIOS_DIR)/$(BIOS_BIN) -vnc localhost:$(VNCPORT) $(DFLAG)

qemu2:
	$(QEMU) -bios $(BIOS_DIR)/$(BIOS_BIN) -vnc $(VNCIP):$(VNCPORT) $(TFLAG) $(DFLAG)

check:
	$(INSTALL) qemu-system-x86
	$(INSTALL) iasl
	wget $(TEST_ISO)
	wget $(BIOS_WEB)$(BIOS_TAR)
	tar -xf $(BIOS_TAR)
