SRC = clr.c
TARGET = clr

CFLAGS += -O3 -D_XOPEN_SOURCE -Wall -W -pedantic

PREFIX ?= /usr/local

.PHONY: install uninstall clean

$(TARGET): $(SRC)
	$(CC) -o "$@" "$?" $(CFLAGS)

install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

uninstall:
	$(RM) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

clean:
	$(RM) -f $(TARGET)
