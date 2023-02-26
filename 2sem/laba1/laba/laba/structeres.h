#pragma once
#include <stdio.h>

typedef enum {
	SMALL = 2,
	CHINA = 3,
	MEDIUM = 4,
	INTERMEDIATE = 6,
	HIGH = 8
} RamTypes;

typedef struct {
	char* name;
	float screenSize;
	RamTypes ram;
	int memory;
	int battery;
} Smartphone;

void initStruct(Smartphone* pointer);
void createStructArr(Smartphone** pointer, int* count);
void addToStruct(Smartphone** pointer, int* count);
void printStructArray(Smartphone* pointer, int count);
void deleteStruct(Smartphone** array, int* count);