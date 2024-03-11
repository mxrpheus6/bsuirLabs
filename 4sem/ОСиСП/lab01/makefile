CC = gcc
CFLAGS_RELEASE = -std=c11 -pedantic -W -Wall -Wextra -Werror
CFLAGS_DEBUG = -g -ggdb -std=c11 -pedantic -W -Wall -Wextra

.PHONY: all clean

MODE = release

ifeq ($(MODE), release)
	CFLAGS = $(CFLAGS_RELEASE)
	TARGET = dirwalk
else
	CFLAGS = $(CFLAGS_DEBUG)
	TARGET = dirwalk_debug
endif

all: $(TARGET)

$(TARGET): src/dirwalk.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f dirwalk dirwalk_debug