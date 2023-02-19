void array_input(int*** array, int amountofrows, int amountofcols);
void array_size(int* amountofrows, int* amountofcols);
void array_move(int** array, int j, int amountofrows, int amountofcols);
void array_show(int** array, int amountofrows, int amountofcols);
int array_check_negative_col(int** array, int amountofrows, int j);
void array_delete(int*** array, int* amountofcols, int* amountofrows);
void array_free(int** array, int amountofrows);