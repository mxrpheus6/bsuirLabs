#include "hash.h"

unsigned long hashFunc(const char* key) {
	unsigned long hash = 5381;
	int symbol;
	while (symbol = *key++) {
		if (symbol == '\0')
			break;
		hash = ((hash << 5) + hash) + symbol;
	}
	return hash;
}

LinkedList* createLinkedListElem(void) {
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

	if (list == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	list->item = NULL;
	list->next = NULL;
	return list;
}

LinkedList* insertLinkedList(LinkedList* list, HashTableItem* item) {
	if (list == NULL) {
		LinkedList* head = createLinkedListElem();
		head->item = item;
		head->next = NULL;
		list = head;
		return list;
	}
	else {
		LinkedList* temp = list;
		LinkedList* node = createLinkedListElem();
		while (temp->next != NULL)
			temp = temp->next;
		node->item = item;
		node->next = NULL;
		temp->next = node;
		return list;
	}
}

void freeLinkedList(LinkedList* head) {
	LinkedList* temp = NULL;
	if (head == NULL)
		return;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp->item->head->value);
		free(temp->item->key);
		free(temp->item);
		free(temp);
	}
}

LinkedList** createOverflowBuckets(const HashTable* hashTable) {
	LinkedList** buckets = (LinkedList**)calloc(hashTable->capacity, hashTable->capacity * sizeof(LinkedList*));

	if (buckets == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	return buckets;
}

void freeOverflowBuckets(HashTable* hashTable) {
	LinkedList** buckets = hashTable->overflowBuckets;
	for (int i = 0; i < hashTable->capacity; i++)
		freeLinkedList(buckets[i]);
	free(buckets);
}

HashTableItem* createItem(const char* key, QNode* head) {
	HashTableItem* item = (HashTableItem*)malloc(sizeof(HashTableItem));

	if (item == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	item->key = (char*)malloc(strlen(key) + 1);

	if (item->key == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	strcpy(item->key, key);
	item->head = head;
	return item;
}

HashTable* createTable(int capacity) {
	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));

	if (hashTable == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	hashTable->capacity = capacity;
	hashTable->count = 0;
	hashTable->items = (HashTableItem**)calloc(capacity, capacity * sizeof(HashTableItem*));

	if (hashTable->items == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	hashTable->overflowBuckets = createOverflowBuckets(hashTable);
	return hashTable;
}

void freeItem(HashTableItem* item) {
	free(item->head->value);
	free(item->key);
	free(item);
}

void freeTable(HashTable* hashTable) {
	HashTableItem* item = NULL;
	for (int i = 0; i < hashTable->capacity; i++) {
		item = hashTable->items[i];
		if (item != NULL)
			freeItem(item);
	}
	freeOverflowBuckets(hashTable);
	free(hashTable);
}

void handleCollision(HashTable* hashTable, int index, HashTableItem* item) {
	LinkedList* head = hashTable->overflowBuckets[index];
	if (head == NULL) {
		head = createLinkedListElem();
		head->item = item;
		head->next = NULL;
		hashTable->overflowBuckets[index] = head;
		return;
	}
	else {
		LinkedList* current = hashTable->overflowBuckets[index];
		while (current != NULL) {
			current = current->next;
		}
		hashTable->overflowBuckets[index] = insertLinkedList(head, item);
		return;
	}
}

void hashTableInsert(HashTable* hashTable, char* key, QNode* head) {
	int index = hashFunc(key) % hashTable->capacity;
	HashTableItem* item = createItem(key, head);
	const HashTableItem* currentItem = hashTable->items[index];
	
	if (currentItem == NULL) {
		hashTable->items[index] = item;
		hashTable->count++;
	}
	else {
		handleCollision(hashTable, index, item);
		return;
	}
}

QNode* hashTableSearch(const HashTable* hashTable, char* key, char** string) {
	int index = hashFunc(key) % hashTable->capacity;
	HashTableItem* currentItem = hashTable->items[index];
	LinkedList* head = hashTable->overflowBuckets[index];
	while (currentItem != NULL) {
		if (strcmp(currentItem->key, key) == 0) {
			strcpy(*string, currentItem->head->value);
			return currentItem->head;
		}
		if (head == NULL)
			return NULL;
		currentItem = head->item;
		head = head->next;
	}
	return NULL;
}

void hashTableDelete(HashTable* hashTable, char* key) {
	int index = hashFunc(key) % hashTable->capacity;
	HashTableItem* item = hashTable->items[index];
	LinkedList* head = hashTable->overflowBuckets[index];

	if (item == NULL) 
		return;
	else {
		if (head == NULL && strcmp(item->key, key) == 0) {
			freeItem(item);//
			hashTable->items[index] = NULL;
			hashTable->count--;
		}
		else if (head != NULL) {
			if (strcmp(item->key, key) == 0) {
				LinkedList* node = head;
				head = head->next;
				node->next = NULL;
				hashTable->items[index] = createItem(node->item->key, node->item->head);
				hashTable->overflowBuckets[index] = head;
				return;
			}
			LinkedList* curr = head;
			LinkedList* prev = NULL;
			while (curr != NULL) {
				if (strcmp(curr->item->key, key) == 0) {
					if (prev == NULL) {
						hashTable->overflowBuckets[index] = head->next;
						curr->next = NULL;
						return;
					}
					else {
						prev->next = curr->next;
						curr->next = NULL;
						return;
					}
				}
				curr = curr->next;
				prev = curr;
			}
		}
	}
}