#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

#include "interface.h"
#include "descriptors.h"

#define MAX_FILENAME_LEN 512
#define DESCRIPTOR_FILENAME "uevent"
#define DRIVER_DESCRIPTOR "DRIVER"

Interface* create_interface() {
    Interface *interface = malloc(sizeof(Interface));
    if (interface == NULL) {
        printf("Interface malloc error");
        exit(EXIT_FAILURE);
    }

    interface->number = 0;
    interface->name = NULL;
    interface->alternate_number = 0;
    interface->device_class = NULL;
    interface->device_subclass = NULL;
    interface->protocol = 0;

    return interface;
}

Interface** init_interface_array(int size) {
    Interface **interfaces = malloc(size * sizeof(Interface*));

    if (interfaces == NULL) {
        printf("Interfaces malloc error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        interfaces[i] = create_interface();
    }

    return interfaces;
}

void free_interface(Interface *interface) {
    free(interface->name);
    free(interface->device_class);
    free(interface->device_subclass);

    free(interface);
}

void free_interface_array(Interface **interface_array, int size) {
    for (int i = 0; i < size; ++i) {
        free_interface(interface_array[i]);
    }
    free(interface_array);
}

int count_interfaces(const char* path) {
    DIR *dir;
    struct dirent *entry;
    regex_t regex;
    const char *pattern = "[0-9]+-[0-9]+:[0-9]+\\.[0-9]+";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Failed to compile regular expression");
        exit(EXIT_FAILURE);
    }

    dir = opendir(path);
    if (dir == NULL) {
        printf("Error opening %s path", path);
        exit(EXIT_FAILURE);
    }

    int counter = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (regexec(&regex, entry->d_name, 0, NULL, 0) == 0) {
            counter++;
        }
    }

    closedir(dir);
    regfree(&regex);

    return counter;
}

char* read_driver_descriptor(const char* path) {
    FILE* file;
    char descriptor_path[MAX_FILENAME_LEN];
    char line[256];
    char* driver_name = NULL;

    snprintf(descriptor_path, sizeof(descriptor_path), "%s/%s", path, DESCRIPTOR_FILENAME);

    file = fopen(descriptor_path, "r");
    if (file == NULL) {
        printf("Error opening descriptor file\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, DRIVER_DESCRIPTOR) == line) {
            char* value_start = strchr(line, '=') + 1;
            char* newline_pos = strchr(value_start, '\n');
            if (newline_pos != NULL) {
                *newline_pos = '\0';
            }
            driver_name = strdup(value_start);
            break;
        }
    }

    fclose(file);
    return driver_name;
}

void parse_interfaces(Interface **interface_array, const char* path) {
    DIR *dir;
    struct dirent *entry;
    regex_t regex;
    const char *pattern = "[0-9]+-[0-9]+:[0-9]+\\.[0-9]+";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Failed to compile regular expression");
        exit(EXIT_FAILURE);
    }

    dir = opendir(path);
    if (dir == NULL) {
        printf("Error opening %s path", path);
        exit(EXIT_FAILURE);
    }

    int interface_index = 0;
    while ((entry = readdir(dir)) != NULL) {

        if (regexec(&regex, entry->d_name, 0, NULL, 0) != 0) {
            continue;
        }

        char full_path[MAX_FILENAME_LEN];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        interface_array[interface_index]->number = atoi(read_descriptor(full_path, INTERFACE_NUMBER_FILENAME));
        interface_array[interface_index]->name = read_driver_descriptor(full_path);
        interface_array[interface_index]->alternate_number = atoi(read_descriptor(full_path, ALTERNATE_NUMBER_FILENAME));
        interface_array[interface_index]->device_class = read_descriptor(full_path, CLASS_FILENAME);
        interface_array[interface_index]->device_subclass = read_descriptor(full_path, SUBCLASS_FILENAME);
        interface_array[interface_index]->protocol = atoi(read_descriptor(full_path, PROTOCOL_FILENAME));

        interface_index++;
        
    }

    closedir(dir);
    regfree(&regex);
}