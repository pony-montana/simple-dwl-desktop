# mew - dynamic menu
# See LICENSE file for copyright and license details.
.POSIX:

# mew version
VERSION = 1.0

# pkg-config
PKG_CONFIG = pkg-config

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# includes and libs
PKGS = fcft pixman-1 wayland-client xkbcommon
INCS = `$(PKG_CONFIG) --cflags $(PKGS)`
LIBS = `$(PKG_CONFIG) --libs $(PKGS)`

# flags
EMCPPFLAGS = -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE -DVERSION=\"$(VERSION)\"
EMCFLAGS   = -pedantic -Wall $(INCS) $(EMCPPFLAGS) $(CFLAGS)
LDLIBS     = $(LIBS)

all: mew

.c.o:
	$(CC) -c $(EMCFLAGS) $<

config.h:
	cp config.def.h $@

mew.o: config.h wlr-layer-shell-unstable-v1-protocol.h xdg-activation-v1-protocol.h xdg-shell-protocol.h

mew: wlr-layer-shell-unstable-v1-protocol.o xdg-activation-v1-protocol.o xdg-shell-protocol.o mew.o
	$(CC) $(LDFLAGS) -o $@ wlr-layer-shell-unstable-v1-protocol.o xdg-activation-v1-protocol.o xdg-shell-protocol.o mew.o $(LDLIBS)

WAYLAND_PROTOCOLS = `$(PKG_CONFIG) --variable=pkgdatadir wayland-protocols`
WAYLAND_SCANNER   = `$(PKG_CONFIG) --variable=wayland_scanner wayland-scanner`

xdg-activation-v1-protocol.h:
	$(WAYLAND_SCANNER) client-header $(WAYLAND_PROTOCOLS)/staging/xdg-activation/xdg-activation-v1.xml $@
xdg-activation-v1-protocol.c:
	$(WAYLAND_SCANNER) private-code $(WAYLAND_PROTOCOLS)/staging/xdg-activation/xdg-activation-v1.xml $@

xdg-shell-protocol.h:
	$(WAYLAND_SCANNER) client-header $(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@
xdg-shell-protocol.c:
	$(WAYLAND_SCANNER) private-code $(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@

wlr-layer-shell-unstable-v1-protocol.h:
	$(WAYLAND_SCANNER) client-header wlr-layer-shell-unstable-v1.xml $@
wlr-layer-shell-unstable-v1-protocol.c:
	$(WAYLAND_SCANNER) private-code wlr-layer-shell-unstable-v1.xml $@
wlr-layer-shell-unstable-v1-protocol.o: xdg-shell-protocol.o

clean:
	rm -f mew *.o *-protocol.*

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f mew mew-run $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/mew
	chmod 755 $(DESTDIR)$(PREFIX)/bin/mew-run
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < mew.1 > $(DESTDIR)$(MANPREFIX)/man1/mew.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/mew.1

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/mew\
		$(DESTDIR)$(PREFIX)/bin/mew-run\
		$(DESTDIR)$(MANPREFIX)/man1/mew.1

.PHONY: all clean install uninstall
