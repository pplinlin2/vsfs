BUSY_DIR  := busybox-1.23.0
BUSY_WEB  := http://busybox.net/downloads/
BUSY_TAR  := $(BUSY_DIR).tar.bz2

MISC_DIR  := miscutils
KBUILD := Kbuild.src
CONFIG := Config.src
APPLET := applets.src.h

all:
	@echo 'usage:'
	@echo '  make check'
	@echo '  make busybox'
	@echo '  make run'

busybox: reset
	cd $(BUSY_DIR) && \
	cp ../newcmd.c $(MISC_DIR) && \
	echo 'lib-$$(CONFIG_NEWCMD)      += newcmd.o' >>  $(MISC_DIR)/$(KBUILD) && \
	sed -i "s/config\ RAIDAUTORUN/config\ NEWCMD\n\tbool\ 'newcmd'\n\tdefault\ y\n\thelp\n\t  test\ command.\n\nconfig\ RAIDAUTORUN/g" $(MISC_DIR)/$(CONFIG) && \
	sed -i "s/IF_NICE/IF_NEWCMD(APPLET(newcmd,\ BB_DIR_USR_BIN,\ BB_SUID_DROP))\nIF_NICE/g" include/$(APPLET) && \
	make defconfig && \
	echo 'CONFIG_NEWCMD=y' >> .config && \
	make install -j 8

reset:
	@cd $(BUSY_DIR)/$(MISC_DIR)/ && \
	cp .$(KBUILD) $(KBUILD) && \
	cp .$(CONFIG) $(CONFIG)
	@cd $(BUSY_DIR)/include/ && cp .$(APPLET) $(APPLET)

run:
	$(BUSY_DIR)/busybox newcmd arg1 arg2

check:
	wget $(BUSY_WEB)$(BUSY_TAR)
	tar -xf $(BUSY_TAR)
	@cd $(BUSY_DIR)/$(MISC_DIR)/ && \
	cp $(KBUILD) .$(KBUILD) && \
	cp $(CONFIG) .$(CONFIG)
	@cd $(BUSY_DIR)/include/ && cp $(APPLET) .$(APPLET)
