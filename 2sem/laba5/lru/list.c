#include "list.h"

Cache* createCache(int size) {
	Cache* cache = (Cache*)malloc(sizeof(Cache));

	if (cache == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	cache->hashTable = createTable(size);
	cache->head = cache->tail = NULL;
	cache->count = 0;
	return cache;
}

QNode* createNode(char* key, char* value) {
	QNode* node = (QNode*)calloc(1, sizeof(QNode));

	if (node == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	node->key = (char*)malloc(strlen(key) + 1);

	if (node->key == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	strcpy(node->key, key);
	node->value = (char*)malloc(strlen(value) + 1);

	if (node->value == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	strcpy(node->value, value);
	node->next = node->prev = NULL;
	return node;
}

void freeDoubleLinkedList(Cache* cache) {
	freeTable(cache->hashTable);
	free(cache);
}

void moveToHead(QNode** head, QNode** tail, QNode* elem) {
	if (*head == NULL || elem == *head) {
		return;
	}
	QNode* current = *head;
	while (current != NULL && current != elem) {
		current = current->next;
	}
	if (current == NULL) {
		return;
	}
	else if (*tail == current) {
		*tail = (*tail)->prev;
	}

	if (current->prev != NULL) {
		current->prev->next = current->next;
	}
	if (current->next != NULL) {
		current->next->prev = current->prev;
	}
	current->next = *head;
	current->prev = NULL;
	(*head)->prev = current;
	*head = current;
}

void enQueue(QNode** head, QNode** tail, char* key, char* value) {
	QNode* temp = createNode(key, value);
	if ((*head) == NULL) {
		(*head) = temp;
		(*tail) = temp;
	}
	else {
		temp->next = (*head);
		(*head)->prev = temp;
		(*head) = temp;
	}
}

void deQueue(QNode** head, QNode** tail) {
	if ((*head) == (*tail))
		(*head) = NULL;
	QNode* temp = (*tail);
	(*tail) = (*tail)->prev;
	if ((*tail) != NULL)
		(*tail)->next = NULL;
	free(temp);
}

void cacheInsert(Cache* cache, char* key, char* value) {
	if (cache->count >= cache->hashTable->capacity) {
		hashTableDelete(cache->hashTable, cache->tail->key);
		deQueue(&cache->head, &cache->tail);
	}
	enQueue(&cache->head, &cache->tail, key, value);
	hashTableInsert(cache->hashTable, key, cache->head);
	cache->count++;
}

void printCache(Cache* cache) {
	QNode* node = cache->head;
	while (node != NULL) {
		printf("%s:%s\n", node->key, node->value);
		node = node->next;
	}
}