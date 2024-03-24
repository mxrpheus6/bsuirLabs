CC = gcc
CFLAGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic

.PHONY: clean

all: parent child

parent: src/parent.c
	$(CC) $(CFLAGS) src/parent.c -o parent
child: src/child.c
	$(CC) $(CFLAGS) src/child.c -o child
clean:
	rm parent child