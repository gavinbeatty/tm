SHELL = /bin/sh
.SUFFIXES: .c .o

.PHONY: help all configure config conf confclean
help:
	@echo "Targets: help all configure confclean"

PREFIX ?= /usr/local
EXEC_PREFIX ?= $(PREFIX)
LIBDIR ?= lib
VERSION_MAJOR = 1
VERSION_MINOR = 1
VERSION_PATCH = 0

SED ?= sed
RM ?= rm -f

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
		-e 's#@PREFIX@#$(PREFIX)#g' \
		-e 's#@EXEC_PREFIX@#$(EXEC_PREFIX)#g' \
		-e 's#@VERSION_MAJOR@#$(VERSION_MAJOR)#g' \
		-e 's#@VERSION_MINOR@#$(VERSION_MINOR)#g' \
		-e 's#@VERSION_PATCH@#$(VERSION_PATCH)#g' \
		-e 's#@LIBDIR@#$(LIBDIR)#g' \
		tm.pc.in > tm.pc

src/tm/config.h: src/tm/config.h.in
	$(gen_p)$(SED) \
		-e 's#@VERSION_MAJOR@#$(VERSION_MAJOR)#g' \
		-e 's#@VERSION_MINOR@#$(VERSION_MINOR)#g' \
		-e 's#@VERSION_PATCH@#$(VERSION_PATCH)#g' \
		src/tm/config.h.in > src/tm/config.h

