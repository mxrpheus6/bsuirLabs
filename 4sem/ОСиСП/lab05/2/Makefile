CC=gcc
CFLAGS=-W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic -Wextra -Werror

all: main

main: src/main.c src/ring.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BIN_DIR)