CC=gcc
CFLAGS=-W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic

all: parent child

parent: src/parent.c src/stack.c
	$(CC) $(CFLAGS) -o $@ $^

child: src/child.c src/stack.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf child parent
