#define TRUE 1
#define FALSE 0

int length(char* string);
int compare_strings(char* string1, char* string2);
void array_input_keyboard(int* array1, int* array2, int size);
void array_input_random(int* array1, int* array2, int size);
void array_choice(char* choice, char* check_k, char* check_r);
void array_size(int* amountofrows);
void array_start_memory(int** array1, int** array2, int sizeofarray);
void array_output(int** array, int size);
void compare_choice(int** array1, int** array2, char* choice, char* check_k, int sizeofarray);
void array_worst(int** array);
void array_free(int** array1, int** array2, int** array_worst1, int** array_worst2);