#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "descriptors.h"

#define MAX_PATH_LEN 4096
#define MAX_DESC_VALUE_LEN 256

#define DEVICES_PATH "/sys/bus/usb/devices"

char* read_descriptor(const char *path, const char *desc) {
    char full_path[MAX_PATH_LEN];

    snprintf(full_path, sizeof(full_path), "%s/%s", path, desc);

    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        return NULL;
    }

    char* line = malloc(MAX_DESC_VALUE_LEN * sizeof(char));
    if (line == NULL) {
        fclose(file);
        return NULL;
    }

    fgets(line, MAX_DESC_VALUE_LEN, file);

    line[strlen(line) - 1] = '\0';

    fclose(file);

    return line;
}