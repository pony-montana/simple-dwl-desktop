.POSIX:

VERSION = 0

PREFIX = /usr/local

PKG_CONFIG = pkg-config

PKGS = wayland-client xkbcommon
INCS = `$(PKG_CONFIG) --cflags $(PKGS)`
LIBS = `$(PKG_CONFIG) --libs $(PKGS)`

WLCPPFLAGS = -DVERSION=\"$(VERSION)\"
WLCFLAGS   = -pedantic -Wall $(INCS) $(WLCPPFLAGS) $(CPPFLAGS) $(CFLAGS)
LDLIBS     = $(LIBS) -lcrypt

SRC = wlock.c single-pixel-buffer-v1-protocol.c ext-session-lock-v1-protocol.c viewporter-protocol.c
OBJ = $(SRC:.c=.o)

all: wlock
.c.o:
	$(CC) -o $@ $(WLCFLAGS) -c $<

wlock.o: single-pixel-buffer-v1-protocol.h ext-session-lock-v1-protocol.h viewporter-protocol.h

wlock: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

WAYLAND_PROTOCOLS = `$(PKG_CONFIG) --variable=pkgdatadir wayland-protocols`
WAYLAND_SCANNER   = `$(PKG_CONFIG) --variable=wayland_scanner wayland-scanner`

single-pixel-buffer-v1-protocol.c:
	$(WAYLAND_SCANNER) private-code $(WAYLAND_PROTOCOLS)/staging/single-pixel-buffer/single-pixel-buffer-v1.xml $@
single-pixel-buffer-v1-protocol.h:
	$(WAYLAND_SCANNER) client-header $(WAYLAND_PROTOCOLS)/staging/single-pixel-buffer/single-pixel-buffer-v1.xml $@
ext-session-lock-v1-protocol.c:
	$(WAYLAND_SCANNER) private-code $(WAYLAND_PROTOCOLS)/staging/ext-session-lock/ext-session-lock-v1.xml $@
ext-session-lock-v1-protocol.h:
	$(WAYLAND_SCANNER) client-header $(WAYLAND_PROTOCOLS)/staging/ext-session-lock/ext-session-lock-v1.xml $@
viewporter-protocol.c:
	$(WAYLAND_SCANNER) private-code $(WAYLAND_PROTOCOLS)/stable/viewporter/viewporter.xml $@
viewporter-protocol.h:
	$(WAYLAND_SCANNER) client-header $(WAYLAND_PROTOCOLS)/stable/viewporter/viewporter.xml $@

clean:
	rm -f wlock *.o *-protocol.*

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f wlock $(DESTDIR)$(PREFIX)/bin
	chmod 4755 $(DESTDIR)$(PREFIX)/bin/wlock

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/wlock

.PHONY: all clean install uninstall
