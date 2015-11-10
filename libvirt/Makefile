INSTALL  := sudo apt-get install

PREFIX   := --prefix=$(shell pwd)/root
NOSUP    := xen uml openvz vmware phyp xenapi libxl vbox lxc esx hyperv
BFLAGS   += $(foreach var,$(NOSUP), --with-$(var)=no)
LOGFLAGS := LIBVIRT_DEBUG=1  LIBVIRT_LOG_OUTPUTS="1:file:log/virsh.log"

VIRT_DIR := libvirt-1.2.19
VIRT_WEB := http://libvirt.org/sources/
VIRT_TAR := $(VIRT_DIR).tar.gz

all:
	@echo 'usage'
	@echo '  make check'

build:
	cd $(VIRT_DIR) && \
	./configure $(PREFIX) $(BFLAGS) && \
	make -j 4 && \
	make install

hello:
	$(LOGFLAGS) $(VIRT_DIR)/examples/hellolibvirt/hellolibvirt test:///default

check:
	wget $(VIRT_WEB)$(VIRT_TAR)
	tar -xf $(VIRT_TAR)
	mkdir -p log
