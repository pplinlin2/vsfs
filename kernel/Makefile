ROOT := rootfs
BIN  := init

CROSS_COMPILE := arm-linux-gnueabi-
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy

ARCH := arm
QEMU := qemu-system-arm
INSTALL := sudo apt-get install
EXPORT += export ARCH=$(ARCH)
EXPORT += export CROSS_COMPILE=$(CROSS_COMPILE)

LINUX_DIR := linux-3.2
LINUX_WEB := https://www.kernel.org/pub/linux/kernel/v3.0/
LINUX_TAR := $(LINUX_DIR).tar.gz
LINUX_BIN := zImage

all:
	@echo 'usage:'
	@echo '  make check'
	@echo '  make '$(ROOT)
	@echo '  make linux'
	@echo '  make qemu'
	@echo '  make clean'

$(ROOT): $(BIN)
	echo $< | cpio -o --format=newc > $@

$(BIN):
	$(CC) -static init.c -o $@

linux:
	cd $(LINUX_DIR) && \
	$(EXPORT) && \
	make mrproper && \
	make vexpress_defconfig && \
	make all -j 8

.PHONY: qemu check clean
qemu:
	@echo -e '\e[33mPress "Ctrl + a" and then "x" to exit\e[0m'
	$(QEMU) -M vexpress-a9 -kernel $(LINUX_DIR)/arch/$(ARCH)/boot/$(LINUX_BIN) -initrd $(ROOT) -nographic -append "console=ttyAMA0"

check:
	$(INSTALL) gcc-arm-linux-gnueabi
	$(INSTALL) $(QEMU)
	$(INSTALL) u-boot-tools
	wget $(LINUX_WEB)$(LINUX_TAR)
	tar -xf $(LINUX_TAR)
	
clean:
	rm $(BIN) $(ROOT)
