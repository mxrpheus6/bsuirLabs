#include "file.h"

int typeIdentify(const char* string) {
	char* duplicate = (char*)malloc(strlen(string) + 1);

	if (duplicate == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	strcpy_s(duplicate, strlen(string) + 1, string);
	const char* pointer;
	char* nextToken;

	pointer = strtok_s(duplicate, " ", &nextToken);
	while (pointer != NULL) {
		if (strcmp(pointer, "A") == 0)
			return A;
		else if (strcmp(pointer, "CNAME") == 0)
			return CNAME;

		pointer = strtok_s(NULL, " ", &nextToken);
	}

	free(duplicate);
	return -1;
}

int typeValid(const char* string) {
	FILE* filePointer;
	errno_t err = fopen_s(&filePointer, "dns.txt", "r");
	if (err != 0) {
		printf("Error opening file");
		exit(1);
	}

	char temp[STRING_SIZE];
	const char* pointer;
	char* nextToken;

	while (fgets(temp, STRING_SIZE, filePointer) != NULL) {
		if (typeIdentify(temp) == A) {
			pointer = strtok_s(temp, " ", &nextToken);
			if (strcmp(pointer, string) == 0)
				return 0;
		}
	}

	fclose(filePointer);
	return 1;
}

int checkIP(const char* ip) {
	int num;
	int dots = 0;
	char* duplicate = (char*)malloc(IP_SIZE);

	if (duplicate == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	strcpy_s(duplicate, IP_SIZE, ip);
	const char* pointer;
	char* nextToken;

	if (ip == NULL)
		return 0;

	pointer = strtok_s(duplicate, ".", &nextToken);
	if (pointer == NULL) {
		return 0;
	}

	while (pointer != NULL) {
		if (!isdigit(*pointer))
			return 0;

		num = atoi(pointer);
		if (num < 0 || num > 255)
			return 0;
		dots++;
		pointer = strtok_s(NULL, ".", &nextToken);
	}

	if (dots != 4)
		return 0;

	return 1;
}

void getIP(char* ip) {
	printf("Please, enter IP adress: ");
	fgets(ip, IP_SIZE, stdin);
	ip[strlen(ip) - 1] = '\0';
	while (checkIP(ip) == 0) {
		printf("Error. Invalid IP adress. Please, try again: ");
		fgets(ip, IP_SIZE, stdin);
		ip[strlen(ip) - 1] = '\0';
	}
}

void addToFile(char* domenName) {
	int userInput;
	char ip[IP_SIZE];
	FILE* dnsFile = fopen("dns.txt", "a+");
	if (dnsFile == NULL) {
		printf("Error. Can't open\\create file. Try again");
		exit(1);
	}
	printf("Please, choose a type (Adress - 1, Cannonical Name - 2): ");
	while (((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n') || (userInput < 1 || userInput > 2)) {
		printf("Invalid input. Please, enter correct number (1 or 2): ");
		rewind(stdin);
	}
	if (userInput == 1) {
		getIP(ip);
		fprintf(dnsFile, "\n%s IN A %s", domenName, ip);
	}
	else {
		char newDomen[DOMEN_SIZE];
		printf("Plaese, enter main domen: ");
		fgets(newDomen, DOMEN_SIZE, stdin);
		newDomen[strlen(newDomen) - 1] = '\0';
		while (typeValid(newDomen) != 0) {
			printf("Error. You must write existing one: ");
			fgets(newDomen, DOMEN_SIZE, stdin);
			newDomen[strlen(newDomen) - 1] = '\0';
		}
		fprintf(dnsFile, "\n%s IN CNAME %s", domenName, newDomen);
	}
	fclose(dnsFile);
}

int fileSearch(const char* key, char** ip) {
	FILE* filePointer;
	errno_t err = fopen_s(&filePointer, "dns.txt", "r");
	if (err != 0) {
		printf("Error. Can't open\\create file. Try again");
		exit(1);
	}

	char tempLine[STRING_SIZE];
	char tempDomain[DOMEN_SIZE];
	char tempIN[IN_SIZE];
	char tempType[TYPE_SIZE];
	char tempValue[IP_SIZE];
	*ip = (char*)malloc(STRING_SIZE);

	if (*ip == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	while (fgets(tempLine, STRING_SIZE, filePointer) != NULL) {
		if (sscanf(tempLine, "%s %s %s %s", tempDomain, tempIN, tempType, tempValue) != 4) {
			printf("Inavlid format of string: %s\n", tempLine);
			exit(1);
		}

		if (strcmp(tempDomain, key) == 0) {
			if (strcmp(tempType, "A") == 0) {
				tempValue[strlen(tempValue)] = '\0';
				strcpy_s(*ip, STRING_SIZE, tempValue);
				fclose(filePointer);
				return 0;
			}

			else if (strcmp(tempType, "CNAME") == 0) {
				char tempNewDomain[STRING_SIZE];
				strcpy_s(tempNewDomain, STRING_SIZE, tempValue);
				fseek(filePointer, 0, SEEK_SET);

				while (fgets(tempLine, STRING_SIZE, filePointer) != NULL) {
					if (sscanf(tempLine, "%s %s %s %s", tempDomain, tempIN, tempType, tempValue) != 4) {
						printf("Inavlid format of string: %s\n", tempLine);
						exit(1);
					}

					if (strcmp(tempDomain, tempNewDomain) == 0 && strcmp(tempType, "A") == 0) {
						tempValue[strlen(tempValue)] = '\0';
						strcpy_s(*ip, STRING_SIZE, tempValue);
						fclose(filePointer);
						return 0;
					}
				}
			}
		}
	}
	fclose(filePointer);
	return -1;
}


char* cacheSearch(Cache* cache, char* key) {
	char* searchResult = (char*)malloc(STRING_SIZE);
	QNode* tempNode = hashTableSearch(cache->hashTable, key, &searchResult);

	if (tempNode != NULL) {
		printf("HIT\n");
		moveToHead(&cache->head, &cache->tail, tempNode);
		return searchResult;
	}
	else {
		char* domainName = NULL;
		char* ip = NULL;
		printf("MISS\n");
		int fileSearchResult = fileSearch(key, &ip);

		if (fileSearchResult == -1) {
			printf("Error. There is no your domen in dns database.\nPlease, create new one.\n");
			addToFile(key);
			printf("Succesifully added!\n");
			cacheSearch(cache, key);
		}
		else if (fileSearchResult == 0) {
			domainName = key;
			cacheInsert(cache, domainName, ip);
			return ip;
		}
	}
}