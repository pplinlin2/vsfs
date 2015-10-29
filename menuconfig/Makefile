CONFIG_SHELL := /bin/bash
HOSTCC  := gcc
SRCARCH := arm
srctree := $(shell pwd)

ifeq ("$(origin V)", "command line")
  KBUILD_VERBOSE = $(V)
endif
ifndef KBUILD_VERBOSE
  KBUILD_VERBOSE = 0
endif

ifeq ($(KBUILD_VERBOSE),1)
  quiet =
  Q =
else
  quiet=quiet_
  Q = @
endif

export HOSTCC CONFIG_SHELL SRCARCH quiet Q srctree
-include .config

CY := '\e[33m'
CE := '\e[0m'
INSTALL := sudo apt-get install

BUSY_DIR  := busybox-1.23.0
BUSY_WEB  := http://busybox.net/downloads/
BUSY_TAR  := $(BUSY_DIR).tar.bz2

LINUX_DIR := linux-3.2
LINUX_WEB := https://www.kernel.org/pub/linux/kernel/v3.0/
LINUX_TAR := $(LINUX_DIR).tar.gz

all:
	@echo 'usage:'
	@echo '  make check'
	@echo '  make menuconfig'
	@echo '  make busybox'
	@echo '  make clean'

busybox: busybox_static-$(CONFIG_ROOTFS_STATIC) show

busybox_static-y:
	cd $(BUSY_DIR) && \
	make defconfig && \
	echo 'CONFIG_STATIC=y' >> .config && \
	make install -j 8

busybox_static-:
	cd $(BUSY_DIR) && \
	make defconfig && \
	make install -j 8

show:
	@echo -ne $(CY)
	@file $(BUSY_DIR)/busybox
	@echo -ne $(CE)

menuconfig:
	make -f scripts/Makefile.build obj=scripts/basic
	make -f scripts/Makefile.build obj=scripts/kconfig menuconfig

clean:
	make -f scripts/Makefile.clean obj=scripts/basic
	make -f scripts/Makefile.clean obj=scripts/kconfig

check:
	$(INSTALL) libncurses5-dev
	wget $(LINUX_WEB)$(LINUX_TAR)
	tar -xf $(LINUX_TAR) $(LINUX_DIR)/scripts/ --strip 1
	wget $(BUSY_WEB)$(BUSY_TAR)
	tar -xf $(BUSY_TAR)
