#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define MAX_MESSAGE_SIZE 255
#define RING_SIZE 10

typedef struct message {
    uint8_t type;
    uint16_t hash;
    uint8_t size;
    uint8_t data[MAX_MESSAGE_SIZE];
} Message;

typedef struct node {
    Message*  message;
    struct node* next;
    struct node* prev;
} Node;

typedef struct ring {
    Node* head;
    Node* tail;
    size_t produced;
    size_t consumed;
    size_t curr;
    size_t size;
} Ring;

void push(Node**, Node**);
void pop(Node**, Node**);
uint16_t hash(uint8_t* data, size_t len);
void init_mes(Message*);
void print_mes(Message*);