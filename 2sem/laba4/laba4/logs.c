#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "logs.h"

char* getString(char* string) {
	fgets(string, 256, stdin);
	string[strlen(string) - 1] = '\0';
}

struct tm* getTime(void) {
	time_t currentTime;
	currentTime = time(NULL);
	struct tm* local = localtime(&currentTime);
	return local;
}

char* fileMark(void) {
	int seconds;
	int minutes;
	int hours;
	int day;
	int month;
	int year;
	char* result = (char*)malloc(20);

	struct tm* local = getTime();

	seconds = local->tm_sec;
	minutes = local->tm_min;
	hours = local->tm_hour;
	day = local->tm_mday;
	month = local->tm_mon + 1;
	year = local->tm_year + 1900;

	sprintf(result, "[%02d.%02d.%04d|%02d:%02d:%02d]", day, month, year, hours, minutes, seconds);

	return result;
}


void createLog(FILE** fp) {
	struct tm* local = getTime();
	int seconds;
	int minutes;
	int hours;
	int day;
	int month;
	int year;
	char* fileName = (char*)malloc(30);

	seconds = local->tm_sec;
	minutes = local->tm_min;
	hours = local->tm_hour;
	day = local->tm_mday;
	month = local->tm_mon + 1;
	year = local->tm_year + 1900;

	sprintf(fileName, "session_%02d-%02d-%04d_%02d-%02d-%02d.log", day, month, year, hours, minutes, seconds);

	*fp = fopen(fileName, "w");
	if (*fp == NULL) {
		printf("Unknown error. Please try again.");
		exit(1);
	}
}

void createMessage(FILE** fp, char* message) {
	fprintf(*fp, "%s\t%s\n", fileMark(), message);
}

void createAddMessage(FILE** fp, char* message, char* object) {
	fprintf(*fp, "%s\t%s%s\n", fileMark(), message, object);
}