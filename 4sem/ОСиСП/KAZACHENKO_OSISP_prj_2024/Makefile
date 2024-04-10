CC = gcc
CFLAGS = -std=c11 -g2 -ggdb -pedantic -W -Wall -Wextra
LDFLAGS = -lncurses

.SUFFIXES:
.SUFFIXES: .c .o

DEBUG = ./build/debug
RELEASE = ./build/release
OUT_DIR = $(DEBUG)
vpath %.c src
vpath %.h src
vpath %.o build/debug

ifeq ($(MODE), release)
    CFLAGS = -std=c11 -pedantic -W -Wall -Wextra -Werror
    LDFLAGS += -lncurses  # Добавляем флаг линковки для библиотеки ncurses
    OUT_DIR = $(RELEASE)
    vpath %.o build/linux/release
endif

objects = $(OUT_DIR)/main.o $(OUT_DIR)/device.o $(OUT_DIR)/descriptors.o $(OUT_DIR)/hub.o $(OUT_DIR)/interface.o $(OUT_DIR)/flash_test.o
#objects = main.o lib.o

prog = USBAssist

all: $(prog)

$(prog) : $(objects)
	$(CC) $(CFLAGS) $(objects) -o $@ $(LDFLAGS)

$(OUT_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	@rm -rf $(DEBUG)/* $(RELEASE)/* USBAssist
