#include <stdio.h>
#include <stdlib.h>

void merge(int* arr, int left, int right) {
	int leftMinIndex = left;
	int mid = left + (right - left) / 2;
	int rightMinIndex = mid + 1;
	int resultMinIndex = 0;
	int* resultArray;
	resultArray = (int*)malloc((right + 1) * sizeof(int));

	while (leftMinIndex <= mid && rightMinIndex <= right) {
		if (arr[leftMinIndex] < arr[rightMinIndex]) {
			resultArray[resultMinIndex] = arr[leftMinIndex];
			leftMinIndex++;
		}
		else {
			resultArray[resultMinIndex] = arr[rightMinIndex];
			rightMinIndex++;
		}
		resultMinIndex++;
	}
	while (leftMinIndex <= mid) {
		resultArray[resultMinIndex] = arr[leftMinIndex];
		leftMinIndex++;
		resultMinIndex++;
	}
	while (rightMinIndex <= right) {
		resultArray[resultMinIndex] = arr[rightMinIndex];
		rightMinIndex++;
		resultMinIndex++;
	}
	for (int i = 0; i < resultMinIndex; i++) {
		arr[left + i] = resultArray[i];
	}
}

void mergeSort(int* arr, int left, int right) {
	int temp;
	if (left < right) {
		if (right - left == 1) {
			if (arr[left] > arr[right]) {
				temp = arr[left];
				arr[left] = arr[right];
				arr[right] = temp;
			}
		}
		else {
			mergeSort(arr, left, left + (right - left) / 2);
			mergeSort(arr, left + (right - left) / 2 + 1, right);
			merge(arr, left, right);
		}
	}
}