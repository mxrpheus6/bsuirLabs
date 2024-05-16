CC=gcc
CFLAGS=-W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic -Wextra -Werror

all: consumer producer main

consumer: src/consumer.c src/ring.c
	$(CC) $(CFLAGS) -o $@ $^

producer: src/producer.c src/ring.c
	$(CC) $(CFLAGS) -o $@ $^

main: src/main.c src/ring.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm main producer consumer