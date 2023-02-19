#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1000

int main(int argc, char** argv) {
    char buffer[BUFFER_SIZE];
    char* delimiters = "<>";
    char* token;

    /* открытие файла */
    FILE* file = fopen("file.html", "r");
    if (file == NULL) {
        printf("error: could not open file\n");
        return 1;
    }

    /* чтение файла в память */
    fread(buffer, BUFFER_SIZE, 1, file);

    /* закрытие файла */
    fclose(file);

    /* разбиение строки на токены */
    token = strtok(buffer, delimiters);
    while (token != NULL) {
        /* проверка токена на наличие какого-либо конкретного тега, например, для поиска тега <title>: /
        if (strcmp(token, "title") == 0) {
        / поиск закрывающего тега /
        token = strtok(NULL, delimiters);
        while (strcmp(token, "/title") != 0) {
        / вывод содержимого тега */
        printf("%s\n", token);
        token = strtok(NULL, delimiters);
    }
}