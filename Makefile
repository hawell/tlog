NAME = tlog
MAJOR = 1
MINOR = 0
PATCH = 0
PREFIX = /usr/local
LIBNAME = lib$(NAME)-$(MAJOR).$(MINOR).$(PATCH).a
export LIBNAME
export PREFIX

.PHONY: src

all:
	$(MAKE) -C src
	
clean:
	$(MAKE) -C src clean
	
install:
	$(MAKE) -C src install
	install -D -m 644 $(LIBNAME) $(PREFIX)/lib/$(LIBNAME) 