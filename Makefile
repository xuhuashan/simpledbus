CC		?= gcc
INSTALL 	?= install
LUA		?= lua
LUA_ABIVER	?= 5.1

#CFLAGS		= -march=native -O2 -Wall -fpic -pedantic
CFLAGS		?= -O2 -Wall -fPIC -pedantic

PREFIX		= /usr/local
LUA_LIBDIR	= $(PREFIX)/lib/lua/$(LUA_ABIVER)
LUA_DATADIR	= $(PREFIX)/share/lua/$(LUA_ABIVER)

EXPAT_CFLAGS	= $(shell pkg-config --cflags expat)
EXPAT_LIBS	= $(shell pkg-config --libs expat)
DBUS_CFLAGS	= $(shell pkg-config --cflags dbus-1)
DBUS_LIBS	= $(shell pkg-config --libs dbus-1)
LUA_CFLAGS	= $(shell pkg-config --cflags $(LUA))
LUA_LIBS	= $(shell pkg-config --libs $(LUA))

override CFLAGS	+= -fPIC $(EXPAT_CFLAGS) $(DBUS_CFLAGS) $(LUA_CFLAGS)
override LDFLAGS += -shared $(EXPAT_LIBS) $(DBUS_LIBS) $(LUA_LIBS)

sources = add.c push.c parse.c simpledbus.c
headers = $(sources:.c=.h)
objects = $(sources:.c=.o)

programs = core.so

.PHONY: all strip indent clean install uninstall

all: $(programs)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c $<

core.so: $(objects)
	$(CC) $(LDFLAGS) $(objects) -o $@

allinone: CFLAGS+=-DALLINONE
allinone:
	$(CC) $(CFLAGS) $(LDFLAGS) simpledbus.c -o core.so

simpledbus:
	@echo "LuaRocks is silly..."

strip:
	@for i in $(programs); do echo strip $$i; strip "$$i"; done

indent:
	indent -kr -i8 *.c *.h

clean:
	rm -f *.so *.o *.c~ *.h~ $(programs)

install: core.so
	$(INSTALL) -m755 -D core.so \
		$(DESTDIR)$(LUA_LIBDIR)/simpledbus/core.so
	$(INSTALL) -m644 -D simpledbus.lua \
		$(DESTDIR)$(LUA_DATADIR)/simpledbus.lua

uninstall:
	rm -rf $(DESTDIR)$(LUA_LIBDIR)/simpledbus
	rm -f $(DESTDIR)$(LUA_DATADIR)/simpledbus.lua

