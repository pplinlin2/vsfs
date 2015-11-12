INSTALL  := sudo apt-get -y install
PACKAGE  := libyajl-dev pkg-config libxml2-dev libdevmapper-dev libpciaccess-dev libudev-dev libnl-dev

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
	@echo '  make build'
	@echo '  make hello'

build:
	cd $(VIRT_DIR) && \
	./configure $(PREFIX) $(BFLAGS) && \
	make -j 4 && \
	make install

hello:
	$(LOGFLAGS) $(VIRT_DIR)/examples/hellolibvirt/hellolibvirt test:///default

check:
	$(INSTALL) $(PACKAGE)
	wget $(VIRT_WEB)$(VIRT_TAR)
	tar -xf $(VIRT_TAR)
	mkdir -p log
