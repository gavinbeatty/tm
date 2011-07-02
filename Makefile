SHELL = /bin/sh
.SUFFIXES: .c .o

.PHONY: help all configure config conf confclean install-libdir install-static install-shared install-headers install
help:
	@echo "Targets: help all configure confclean install"

PROJECT_NAME = tm
HOMEPAGE = http://github.com/gavinbeatty/tm
PREFIX ?= /usr/local
EXEC_PREFIX ?= $(PREFIX)
VERSION_MAJOR = 1
VERSION_MINOR = 1
VERSION_PATCH = 0
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)
DESCRIPTION = Simple cross-platform time functions

SED ?= sed
RM ?= rm -f
INSTALL ?= install
INSTALL_DIR ?= $(INSTALL) -d
INSTALL_DATA ?= $(INSTALL) -m 0644
INSTALL_LIB ?= $(INSTALL) -m 0755

gen_cc = @echo '    CC        ' $@;
gen_ld = @echo '    LINK      ' $@;
gen_ar = @echo '    AR        ' $@;
gen_p  = @echo '    GEN       ' $@;

configure: tm.pc src/tm/config.h
config: configure
conf: configure

confclean:
	$(RM) tm.pc src/tm/config.h

all: configure

tm.pc: tm.pc.in
	$(gen_p)$(SED) \
		-e 's#@PROJECT_NAME@#$(PROJECT_NAME)#g' \
		-e 's#@VERSION@#$(VERSION)#g' \
		-e 's#@HOMEPAGE@#$(HOMEPAGE)#g' \
		-e 's#@DESCRIPTION@#$(DESCRIPTION)#g' \
		-e 's#@PREFIX@#$(PREFIX)#g' \
		tm.pc.in > tm.pc

src/tm/config.h: src/tm/config.h.in
	$(gen_p)$(SED) \
		-e 's#@VERSION_MAJOR@#$(VERSION_MAJOR)#g' \
		-e 's#@VERSION_MINOR@#$(VERSION_MINOR)#g' \
		-e 's#@VERSION_PATCH@#$(VERSION_PATCH)#g' \
		-e 's#@VERSION@#$(VERSION)#g' \
		src/tm/config.h.in > src/tm/config.h

SHARED_LIBRARY ?= libtm.so

$(DESTROOT)$(EXEC_PREFIX)/lib$(ADDRESS_MODEL):
	$(INSTALL_DIR) $(DESTROOT)$(EXEC_PREFIX)/lib$(ADDRESS_MODEL)
install-static: configure $(DESTROOT)$(EXEC_PREFIX)/lib$(ADDRESS_MODEL)
	$(INSTALL_LIB) stage/libtm.a $(DESTROOT)$(EXEC_PREFIX)/lib$(ADDRESS_MODEL)/
install-shared: configure $(DESTROOT)$(EXEC_PREFIX)/lib$(ADDRESS_MODEL)
	$(INSTALL_LIB) stage/$(SHARED_LIBRARY) $(DESTROOT)$(EXEC_PREFIX)/lib$(ADDRESS_MODEL)/
install-headers:
	$(INSTALL_DIR) $(DESTROOT)$(PREFIX)/include/tm
	$(INSTALL_DATA) $(wildcard src/tm/*.h) $(DESTROOT)$(PREFIX)/include/tm/
	$(INSTALL_DIR) $(DESTROOT)$(PREFIX)/include/tm/impl
	$(INSTALL_DATA) $(wildcard src/tm/*.h) $(DESTROOT)$(PREFIX)/include/tm/impl/
install: install-static install-shared install-headers
