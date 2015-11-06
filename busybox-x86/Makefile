ARCH := x86
QEMU := qemu-system-x86_64
INSTALL := sudo apt-get install

LINUX_DIR := linux-3.2
LINUX_WEB := https://www.kernel.org/pub/linux/kernel/v3.0/
LINUX_TAR := $(LINUX_DIR).tar.gz
LINUX_BIN := bzImage

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
	make defconfig && \
	echo 'CONFIG_STATIC=y' >> .config && \
	make install -j 8

rootfs:
	cd $(BUSY_DIR)/_install && \
	mkdir -p proc sys dev etc etc/init.d && \
	echo '#!/bin/sh' > $(RCS) && \
	echo 'mount -t proc none /proc' >> $(RCS) && \
	echo 'mount -t sysfs none /sys' >> $(RCS) && \
	echo '/sbin/mdev -s' >> $(RCS) && \
	chmod +x $(RCS) && \
	find . | cpio -o --format=newc | gzip -c > ../../$(BUSY_BIN)

linux:
	cd $(LINUX_DIR) && \
	make mrproper && \
	make defconfig && \
	make all -j 8

.PHONY: qemu check clean
qemu:
	@echo -e '\e[33mPress "Ctrl + a" and then "x" to exit\e[0m'
	$(QEMU) -kernel $(LINUX_DIR)/arch/$(ARCH)/boot/$(LINUX_BIN) -initrd $(BUSY_BIN) -nographic -append "console=ttyS0 rdinit=/sbin/init"

check:
	$(INSTALL) qemu-system-x86
	wget $(LINUX_WEB)$(LINUX_TAR)
	tar -xf $(LINUX_TAR)
	wget $(BUSY_WEB)$(BUSY_TAR)
	tar -xf $(BUSY_TAR)
	
clean:
	rm $(BUSY_BIN)
