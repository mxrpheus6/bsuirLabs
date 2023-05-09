#pragma once

#include <stdlib.h>
#include <string.h>

#include"list.h"

typedef struct QNode QNode;
typedef struct HashTable HashTable;

typedef struct HashTableItem {
	char* key;
	QNode* head;
}HashTableItem;

typedef struct LinkedList {
	HashTableItem* item;
	struct linkedList* next;
}LinkedList;

typedef struct HashTable {
	int capacity;
	int count;
	HashTableItem** items;
	LinkedList** overflowBuckets;
}HashTable;

LinkedList* createLinkedListElem(void);
LinkedList* insertLinkedList(LinkedList* list, HashTableItem* item);
void freeLinkedList(LinkedList* head);
unsigned long hashFunc(char* key);
LinkedList** createOverflowBuckets(HashTable* hashTable);
void freeOverflowBuckets(HashTable* hashTable);
HashTableItem* createItem(char* key, QNode* head);
HashTable* createTable(int capacity);
void freeItem(HashTableItem* item);
void freeTable(HashTable* hashTable);
void handleCollision(HashTable* hashTable, int index, HashTableItem* item);
void hashTableInsert(HashTable* hashTable, char* key, QNode* head);
QNode* hashTableSearch(HashTable* hashTable, char* key, char** string);
void hashTableDelete(HashTable* hashTable, char* key);