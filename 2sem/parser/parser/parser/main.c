#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1000

int main(int argc, char** argv) {
    char buffer[BUFFER_SIZE];
    char* delimiters = "<>";
    char* token;

    /* �������� ����� */
    FILE* file = fopen("file.html", "r");
    if (file == NULL) {
        printf("error: could not open file\n");
        return 1;
    }

    /* ������ ����� � ������ */
    fread(buffer, BUFFER_SIZE, 1, file);

    /* �������� ����� */
    fclose(file);

    /* ��������� ������ �� ������ */
    token = strtok(buffer, delimiters);
    while (token != NULL) {
        /* �������� ������ �� ������� ������-���� ����������� ����, ��������, ��� ������ ���� <title>: /
        if (strcmp(token, "title") == 0) {
        / ����� ������������ ���� /
        token = strtok(NULL, delimiters);
        while (strcmp(token, "/title") != 0) {
        / ����� ����������� ���� */
        printf("%s\n", token);
        token = strtok(NULL, delimiters);
    }
}