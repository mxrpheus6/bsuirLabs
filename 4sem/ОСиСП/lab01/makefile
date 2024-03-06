CC = gcc
RELEASE = -std=c11 -pedantic -W -Wall -Wextra -Werror
DEBUG = -g -ggdb -std=c11 -pedantic -W -Wall -Wextra

.PHONY: clean release debug

all: release

release: dirwalk.c makefile
	$(CC) $(RELEASE) dirwalk.c -o dirwalk
debug: dirwalk.c makefile
	$(CC) $(DEBUG) dirwalk.c -o dirwalk_debug
clean:
	rm -f dirwalk dirwalk_debug