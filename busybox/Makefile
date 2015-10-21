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

BUSY_DIR  := busybox-1.23.0
BUSY_WEB  := http://busybox.net/downloads/
BUSY_TAR  := $(BUSY_DIR).tar.bz2
BUSY_BIN  := rootfs.img.gz
RCS  := etc/init.d/rcS

all:
	@echo 'usage:'
	@echo '  make check'
	@echo '  make busybox'
	@echo '  make rootfs'
	@echo '  make linux'
	@echo '  make qemu'
	@echo '  make clean'

busybox:
	cd $(BUSY_DIR) && \
	$(EXPORT) && \
	make defconfig && \
	echo 'CONFIG_STATIC=y' >> .config && \
	make install -j 8

rootfs:
	cd $(BUSY_DIR)/_install && \
	mkdir proc sys dev etc etc/init.d && \
	echo '#!/bin/sh' > $(RCS) && \
	echo 'mount -t proc none /proc' >> $(RCS) && \
	echo 'mount -t sysfs none /sys' >> $(RCS) && \
	echo '/sbin/mdev -s' >> $(RCS) && \
	chmod +x $(RCS) && \
	find . | cpio -o --format=newc | gzip -c > ../../$(BUSY_BIN)

linux:
	cd $(LINUX_DIR) && \
	$(EXPORT) && \
	make mrproper && \
	make vexpress_defconfig && \
	make all -j 8

.PHONY: qemu check clean
qemu:
	@echo -e '\e[33mPress "Ctrl + a" and then "x" to exit\e[0m'
	$(QEMU) -M vexpress-a9 -kernel $(LINUX_DIR)/arch/$(ARCH)/boot/$(LINUX_BIN) -initrd $(BUSY_BIN) -nographic -append "console=ttyAMA0 rdinit=/sbin/init"

check:
	$(INSTALL) gcc-arm-linux-gnueabi
	$(INSTALL) $(QEMU)
	wget $(LINUX_WEB)$(LINUX_TAR)
	tar -xf $(LINUX_TAR)
	wget $(BUSY_WEB)$(BUSY_TAR)
	tar -xf $(BUSY_TAR)
	
clean:
	rm $(BUSY_BIN)
