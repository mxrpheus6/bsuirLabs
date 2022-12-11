#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void str_length(char* str, int* length) {
    int i = 0;
    while (str[i] != '\n') {
        i++;
        (*length)++;
    }
}


void input_string(char* argv, char** string)
{
    int i = 0;
    rewind(stdin);
    while (argv[i] != '\0')
    {
        (*string)[i++] = argv[i];
        (*string) = (char*)realloc((*string), (i + 1) * sizeof(char));
    }
    (*string)[i] = '\0';
}


void merge_sort(int* mas_i, int* mas, int l, int r) {
    int p1 = 0, p2 = 0, mid = (l + r) / 2, pos = 0;
    int* b = NULL;
    int* b_i = NULL;
    b_i = (int*)calloc((r + 1), sizeof(int));
    b = (int*)malloc((r + 1) * sizeof(int));
    int i = 0;
    while (p1 + l <= mid && mid + p2 + 1 <= r) {
        if (p1 > mid || mid + 1 + p2 > r) break;

        if (mas[p1 + l] < mas[mid + 1 + p2]) {
            b[i] = mas[p1 + l];
            b_i[i] = mas_i[p1 + l];
            i++;
            p1++;
        }
        else {
            b[i] = mas[mid + 1 + p2];
            b_i[i] = mas_i[mid + 1 + p2];
            i++;
            p2++;
        }

    }
    while (p1 + l <= mid) {
        b[i] = mas[p1 + l];
        b_i[i] = mas_i[p1 + l];
        i++;
        p1++;
    }
    while (mid + 1 + p2 <= r) {
        b[i] = mas[mid + 1 + p2];
        b_i[i] = mas_i[mid + 1 + p2];
        i++;
        p2++;
    }
    pos = 0;
    for (int i = l; i <= r; i++) {
        mas[i] = b[pos];
        mas_i[i] = b_i[pos];
        pos++;
    }
    free(b);
}
void merge(int* mas_i, int* mas, int left, int right) {
    if (left == right)return;
    int mid = (left + right) / 2;
    merge(mas_i, mas, left, mid);
    merge(mas_i, mas, mid + 1, right);
    merge_sort(mas_i, mas, left, right);
}


void shortest_words(char** str, int* length, int n, int* min) {
    for (int i = 0; i < n; i++) {
        int k = 0;
        min[i] = 999;

        for (int j = 0; j < length[i]; j++) {
            k++;
            if (str[i][j + 1] == ' ' || str[i][j + 1] == '\0' || str[i][j + 1] == '\n') {
                if (min[i] > k) {
                    min[i] = k;
                }
                k = -1;

            }
        }
    }
}



int main(int argc, char** argv)
{


    int* length = NULL;
    int* min = NULL;
    int* min_ind = NULL;
    char** str = NULL;
    int n = 0;
    // printf("Enter a number of strings\n");
    n = argc;
    str = (char**)calloc(n, 1 * sizeof(char*));

    //printf("\nEnter strings\n");
    min = (int*)calloc(n, sizeof(int));
    min_ind = (int*)calloc(n, sizeof(int));
    length = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        min_ind[i] = i;
        str[i] = (char*)calloc(1, 1);
        //printf("%d. ", i + 1);
        input_string(argv[i], &str[i]);
        length[i] = 0;
        str_length(str[i], &length[i]);
    }
    shortest_words(str, length, n, min);
    merge(min_ind, min, 0, n - 1);
    //for (int i = 0; i < n; i++) {
    //    printf("%d ", min[i]);
    //}
    //printf("\n");
    //for (int i = 0; i < n; i++) {
    //    printf("%d ", min_ind[i]);
    //}
    printf("\nSorted array of strings in ascending order of the length of the shortest word in each string\n");
    for (int i = 0; i < n; i++)
        printf("%s\n", str[min_ind[i]]);
    for (int i = 0; i < n; i++) {
        free(str[i]);
    }
    free(str);
    free(min);
    free(min_ind);
    free(length);
    system("pause");
}