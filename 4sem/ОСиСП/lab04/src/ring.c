#include "ring.h"

void init_ring(Ring* ring) {
    if (ring == NULL) {
        return;
    }

    ring->head = 0;
    ring->tail = 0;
    ring->produced = 0;
    ring->consumed = 0;
}

bool is_empty(Ring* ring) {
    return (ring->head == 0 && ring->tail == 0);
}

bool is_full(Ring* ring) {
    return ((ring->head + 1) % RING_SIZE) == ring->tail;
}

void push_ring(Ring* ring, Message data) {
    ring->data[ring->head] = data;
    ring->head = (ring->head + 1) % RING_SIZE;
}

Message pop_ring(Ring* ring) {
    Message data = ring->data[ring->tail];
    ring->tail = (ring->tail + 1) % RING_SIZE;
    return data;
}