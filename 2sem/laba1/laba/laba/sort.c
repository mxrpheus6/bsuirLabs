#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structeres.h"

int compareName(const void* a, const void* b) {
	const Smartphone* firstThing = (const Smartphone*)a;
	const Smartphone* secondThing = (const Smartphone*)b;
	int firstInt = (int)firstThing->name[0];
	int secondInt = (int)secondThing->name[0];
	if (firstInt >= 65 && firstInt <= 90) {
		firstInt += 32;
	}
	if (secondInt >= 65 && secondInt <= 90) {
		secondInt += 32;
	}
	return firstInt - secondInt;
}

int compareDiag(const void* a, const void* b) {
	const Smartphone* firstThing = (const Smartphone*)a;
	const Smartphone* secondThing = (const Smartphone*)b;
	if (firstThing->screenSize > secondThing->screenSize) {
		return 1;
	}
	else if (firstThing->screenSize < secondThing->screenSize) {
		return -1;
	}
	else {
		return 0;
	}
}

int compareRam(const void* a, const void* b) {
	const Smartphone* firstThing = (const Smartphone*)a;
	const Smartphone* secondThing = (const Smartphone*)b;
	return firstThing->ram - secondThing->ram;
}

int compareMemory(const void* a, const void* b) {
	const Smartphone* firstThing = (const Smartphone*)a;
	const Smartphone* secondThing = (const Smartphone*)b;
	return firstThing->memory - secondThing->memory;
}

int compareCamera(const void* a, const void* b) {
	const Smartphone* firstThing = (const Smartphone*)a;
	const Smartphone* secondThing = (const Smartphone*)b;
	return firstThing->cameraResolution - secondThing->cameraResolution;
}

int compareBattery(const void* a, const void* b) {
	const Smartphone* firstThing = (const Smartphone*)a;
	const Smartphone* secondThing = (const Smartphone*)b;
	return firstThing->battery - secondThing->battery;
}

int compareTwoDiff(const void* a, const void* b) {
	const Smartphone* firstThing = (const Smartphone*)a;
	const Smartphone* secondThing = (const Smartphone*)b;
	if (firstThing->battery < secondThing->battery) {
		return -1;
	}
	else if (firstThing->battery > secondThing->battery) {
		return 1;
	}
	else {
		if (firstThing->cameraResolution < secondThing->cameraResolution) {
			return -1;
		}
		else if (firstThing->cameraResolution > secondThing->cameraResolution) {
			return 1;
		}
		else {
			return 0;
		}
	}

}