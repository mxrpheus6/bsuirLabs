#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

#define CACHE_SIZE 4

typedef struct QNode QNode;
typedef struct HashTable HashTable;

typedef struct QNode {
	char* key;
	char* value;
	struct QNode* next;
	struct QNode* prev;
}QNode;

typedef struct Cache {
	int count;
	HashTable* hashTable;
	QNode* head;
	QNode* tail;
}Cache;

Cache* createCache(int size);
QNode* createNode(char* key, char* value);
void freeDoubleLinkedList(Cache* cache);
void moveToHead(QNode** head, QNode** tail, QNode* elem);
void enQueue(QNode** head, QNode** tail, char* key, char* value);
void deQueue(QNode** head, QNode** tail);
void cacheInsert(Cache* cache, char* key, char* value);
void printCache(Cache* cache);