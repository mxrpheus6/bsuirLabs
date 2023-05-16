#include "file.h"

int typeIdentify(char* string) {
	char* duplicate = (char*)malloc(strlen(string) + 1);

	if (duplicate == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	strcpy(duplicate, string);
	char* pointer = strtok(duplicate, " ");
	while (strcmp(pointer, "A") != 0 && strcmp(pointer, "CNAME") != 0) {
		pointer = strtok(NULL, " ");
	}
	if (strcmp(pointer, "A") == 0)
		return A;
	else if (strcmp(pointer, "CNAME") == 0)
		return CNAME;
	else
		return -1;
}

int typeValid(char* string) {
	FILE* filePointer;
	filePointer = fopen("dns.txt", "r");
	char temp[STRING_SIZE];
	char* pointer;
	while (fgets(temp, STRING_SIZE, filePointer) != NULL) {
		if (typeIdentify(temp) == A) {
			pointer = strtok(temp, " ");
			if (strcmp(pointer, string) == 0)
				return 0;
		}
	}
	return 1;
}

int checkIP(char* ip) {
	int num;
	int dots = 0;
	char* duplicate = (char*)malloc(IP_SIZE);
	
	if (duplicate == NULL) {
		printf("Error. Memory allocation failed");
		exit(1);
	}

	strcpy(duplicate, ip);
	char* pointer;
	
	if (ip == NULL)
		return 0;

	pointer = strtok(duplicate, ".");
	if (pointer == NULL) {
		return 0;
	}

	while (pointer != NULL) {
		if (isdigit(*pointer) == 0)
			return 0;

		num = atoi(pointer);
		if (num < 0 || num > 255)
			return 0;
		dots++;
		pointer = strtok(NULL, ".");
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

int fileSearch(char* key, char** ip) {
	FILE* filePointer = fopen("dns.txt", "r");
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

	if (filePointer == NULL) {
		printf("Error. Can't open\\create file. Try again");
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
				strcpy(*ip, tempValue);
				fclose(filePointer);
				return 0;
			}
			else if (strcmp(tempType, "CNAME") == 0) {
				char tempNewDomain[STRING_SIZE];
				strcpy(tempNewDomain, tempValue);
				fseek(filePointer, 0, SEEK_SET);
				while (fgets(tempLine, STRING_SIZE, filePointer) != NULL) {
					if (sscanf(tempLine, "%s %s %s %s", tempDomain, tempIN, tempType, tempValue) != 4) {
						printf("Inavlid format of string: %s\n", tempLine);
						exit(1);
					}

					if (strcmp(tempDomain, tempNewDomain) == 0) {
						if (strcmp(tempType, "A") == 0) {
							tempValue[strlen(tempValue)] = '\0';
							strcpy(*ip, tempValue);
							fclose(filePointer);
							return 0;
						}
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
	char* temp = NULL;

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