CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk+-3.0 gtk-layer-shell-0)
LIBS = $(shell pkg-config --libs gtk+-3.0 gtk-layer-shell-0)
BINARY = daniel

all: $(BINARY)

$(BINARY): daniel.c
	$(CC) -o $(BINARY) daniel.c $(CFLAGS) $(LIBS)

clean:
	rm -f $(BINARY)

install: $(BINARY)
	mkdir -p ~/.local/bin
	cp $(BINARY) ~/.local/bin/
	echo "✅ Daniel instalado en ~/.local/bin/$(BINARY)"

run: $(BINARY)
	./$(BINARY)

.PHONY: all clean install run
