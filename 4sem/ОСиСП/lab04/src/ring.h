#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_MESSAGE_SIZE 255
#define RING_SIZE 10

typedef struct {
    uint8_t type;
    uint16_t hash;
    uint8_t size;
    uint8_t data[MAX_MESSAGE_SIZE];
} Message;

typedef struct {
    size_t head;
    size_t tail;
    size_t produced;
    size_t consumed;
    Message data[RING_SIZE];
} Ring;

void init_ring(Ring* ring);
bool is_empty(Ring* ring);
bool is_full(Ring* ring);
void push_ring(Ring* ring, Message data);
Message pop_ring(Ring* ring);