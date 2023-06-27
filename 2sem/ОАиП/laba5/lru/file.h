#pragma once
#include <ctype.h>

#include "hash.h"
#include "list.h"

#define IP_SIZE 17
#define TYPE_SIZE 6
#define IN_SIZE 3
#define DOMEN_SIZE 256
#define STRING_SIZE 256

typedef enum Types{
	A = 1,
	CNAME = 2
}Types;

int typeIdentify(char* string);
int typeValid(char* string);
int checkIP(char* ip);
void getIP(char* ip);
void addToFile(char* domenName);
int fileSearch(char* key, char** ip);
int checkCNAME(FILE* filePointer, const char* tempValue, char** ip);
char* cacheSearch(Cache* cache, char* key);
