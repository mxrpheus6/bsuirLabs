#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#define TRUE 1
#define FALSE 0

//void merge(char*** arr, int left, int right) {
//	int leftMinIndex = left;
//	int mid = left + (right - left) / 2;
//	int rightMinIndex = mid + 1;
//	int resultMinIndex = 0;
//	char** resultArray;
//	resultArray = (char**)malloc(2 * sizeof(char*));
//
//	while (leftMinIndex <= mid && rightMinIndex <= right) {
//		if (wordCounter(&(*arr), leftMinIndex) < wordCounter(&(*arr), rightMinIndex)) {
//			resultArray[resultMinIndex] = (char*)malloc(stringLength(arr[leftMinIndex]));
//			for (int i = 0; i < stringLength((*arr)[leftMinIndex]); i++)
//			{
//				resultArray[resultMinIndex][i] = (*arr)[leftMinIndex][i];
//			}
//			leftMinIndex++;
//		}
//		else {
//			resultArray[resultMinIndex] = (char*)malloc(stringLength((*arr)[rightMinIndex]) * sizeof(char));
//			for (int i = 0; i < stringLength((*arr)[rightMinIndex]); i++)
//			{
//				resultArray[resultMinIndex][i] = (*arr)[rightMinIndex][i];
//			}
//			rightMinIndex++;
//		}
//		resultMinIndex++;
//	}
//	while (wordCounter(&(*arr), leftMinIndex) <= mid) {
//		for (int i = 0; i < stringLength((*arr)[leftMinIndex]); i++)
//		{
//			resultArray[resultMinIndex][i] = (*arr)[leftMinIndex][i];
//		}
//		leftMinIndex++;
//		resultMinIndex++;
//	}
//	while (wordCounter(&(*arr), rightMinIndex - 1) <= right) {
//		for (int i = 0; i < stringLength((*arr)[rightMinIndex]); i++)
//		{
//			resultArray[resultMinIndex][i] = (*arr)[rightMinIndex][i];
//		}
//		rightMinIndex++;
//		resultMinIndex++;
//	}
//	for (int i = 0; i < resultMinIndex; i++) {
//		(*arr)[left + i] = resultArray[i];
//	}
//}
//
//void mergeSort(char*** arr, int left, int right) {
//	char** temp;
//	if (left < right) {
//		if (right - left == 1) {
//			if (evenCheck(&(*arr), left) == TRUE && evenCheck(&(*arr), right) == TRUE) {
//				if (wordCounter(&(*arr), left) > wordCounter(&(*arr), right)) {
//					temp = (char*)malloc(stringLength(&(*arr)));
//					temp = (*arr)[left];
//					(*arr)[left] = (*arr)[right];
//					(*arr)[right] = temp;
//				}
//			}
//		}
//		else {
//			mergeSort(arr, left, left + (right - left) / 2);
//			mergeSort(arr, left + (right - left) / 2 + 1, right);
//			merge(arr, left, right);
//		}
//	}
//}

void merge(int*** arr, int left, int right) {
	int leftMinIndex = left;
	int mid = left + (right - left) / 2;
	int rightMinIndex = mid + 1;
	int resultMinIndex = 0;
	int amount = 1;
	int** resultArray;
	resultArray = (int**)calloc((right + 1), sizeof(int*));
	for (int i = 0; i < 4; i++) {
		resultArray[i] = (int*)calloc(2, sizeof(int));
	}

	while (leftMinIndex <= mid && rightMinIndex <= right) {
		if ((*arr)[leftMinIndex][amount] <= (*arr)[rightMinIndex][amount]) {
			for (int i = 0; i < 2; i++) {
				resultArray[resultMinIndex][i] = (*arr)[leftMinIndex][i];
			}
			leftMinIndex++;
		}
		else {
			for (int i = 0; i < 2; i++) {
				resultArray[resultMinIndex][i] = (*arr)[rightMinIndex][i];
			}
			rightMinIndex++;
		}
		resultMinIndex++;
	}
	while (leftMinIndex <= mid) {
		for (int i = 0; i < 2; i++) {
			resultArray[resultMinIndex][i] = (*arr)[leftMinIndex][i];
		}
		leftMinIndex++;
		resultMinIndex++;
	}
	while (rightMinIndex <= right) {
		for (int i = 0; i < 2; i++) {
			resultArray[resultMinIndex][i] = (*arr)[rightMinIndex][i];
		}
		rightMinIndex++;
		resultMinIndex++;
	}
	for (int i = 0; i < resultMinIndex; i++) {
		for (int j = 0; j < 2; j++) {
			(*arr)[left + i][j] = resultArray[i][j];

		}
	}
}

void mergeSort(int*** arr, int left, int right) {
	int* temp;
	temp = (int*)calloc(2, sizeof(int));

	if (left < right) {
		if (right - left == 1) {
			if ((*arr)[left][1] > (*arr)[right][1]) {
				for (int i = 0; i < 2; i++) {
					temp[i] = (*arr)[left][i];
				}
				for (int i = 0; i < 2; i++) {
					(*arr)[left][i] = (*arr)[right][i];
				}
				for (int i = 0; i < 2; i++) {
					(*arr)[right][i] = temp[i];
				}
			}
		}
		else {
			mergeSort(arr, left, left + (right - left) / 2);
			mergeSort(arr, left + (right - left) / 2 + 1, right);
			merge(arr, left, right);
		}
	}
}