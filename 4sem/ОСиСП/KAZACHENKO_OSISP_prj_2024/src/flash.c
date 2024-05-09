#define _DEFAULT_SOURCE
#include "flash.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <sys/statvfs.h>

#define PARTITIONS_PATH "/proc/partitions"
#define MOUNTS_PATH "/proc/mounts"
#define SYS_BLOCK_PATH "/sys/block/"
#define VENDOR_PATH "/device/vendor"
#define MODEL_PATH "/device/model"
#define DEV_PATH "/dev/disk/by-id"

#define MAX_PATH_LEN 4096
#define MAX_LINE_LENGTH 256

extern char *strdup(const char *s);

Flash* create_flash() {
    Flash* flash = malloc(sizeof(Flash));
    if (flash == NULL) {
        printf("Failed to allocate memory for Flash");
        exit(EXIT_FAILURE);
    }
    
    flash->part = NULL;
    flash->mount = NULL;
    flash->model = NULL;
    flash->vendor = NULL;
    flash->size_mb = 0;
    flash->available_size_mb = 0;

    return flash;
}


Flash** init_flash_array(int size) {
    Flash **flash_array = (Flash**)malloc(size * sizeof(Flash*));

    if (flash_array == NULL) {
        printf("Failed to allocate memory for Flash array");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        flash_array[i] = create_flash();
    }

    return flash_array;
}

void free_flash(Flash* flash) {
    free(flash->part);
    free(flash->model);
    free(flash->mount);
    free(flash->vendor);

    free(flash);
}

void free_flash_array(Flash** flash_array, int size) {
    for (int i = 0; i < size; ++i) {
        free_flash(flash_array[i]);
    }
    free(flash_array);
}

int count_flash(const char* path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening flash");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    char device[10];

    int counter = 0;
    while (fgets(buffer, 256, file)) {
        int is_block = 1;
        if (sscanf(buffer, "%*d %*d %*d %s", device) == 1) {
            if (strncmp(device, "sd", 2) == 0) {
                int device_index = 2;
                while (device[device_index] != '\0' && device[device_index] != '\n') {
                    if (isdigit(device[device_index]) != 0) {
                        is_block = 0;
                        break;
                    }
                    device_index++;
                }
                if (is_block == 1) {
                    counter++;
                }
            }
        }
    }

    fclose(file);

    return counter;
}

void parse_proc_partitions(Flash** flash_array, int size) {
    FILE *file = fopen(PARTITIONS_PATH, "r");
    if (file == NULL) {
        perror("Error opening /proc/partitions");
        exit(EXIT_FAILURE);
    }

    int array_index = 0;
    char buffer[256];
    char device[10];
    long long usb_drive_size;

    while (fgets(buffer, 256, file) && array_index < size) {
        int is_block = 1;
        if (sscanf(buffer, "%*d %*d %lld %s", &usb_drive_size, device) == 2) {
            if (strncmp(device, "sd", 2) == 0) {
                int device_index = 2;
                while (device[device_index] != '\0' && device[device_index] != '\n') {
                    if (isdigit(device[device_index]) != 0) {
                        is_block = 0;
                        break;
                    }
                    device_index++;
                }
                if (is_block == 1) {
                    flash_array[array_index]->part = strdup(device);
                    flash_array[array_index]->size_mb = (int)(usb_drive_size / 1024);
                    array_index++;
                }
            }
        }
    }

    fclose(file);
}

void parse_sys_block(Flash** flash_array, int size) {
    for (int i = 0; i < size; i++) {
        FILE* file;
        char buffer[256];
        char full_path[MAX_PATH_LEN];

        snprintf(full_path, sizeof(full_path), "%s%s%s", SYS_BLOCK_PATH, flash_array[i]->part, MODEL_PATH);
        file = fopen(full_path, "r");
        fgets(buffer, 256, file);
        buffer[strlen(buffer) - 1] = '\0';
        flash_array[i]->model = strdup(buffer);
        fclose(file);

        snprintf(full_path, sizeof(full_path), "%s%s%s", SYS_BLOCK_PATH, flash_array[i]->part, VENDOR_PATH);
        file = fopen(full_path, "r");
        fgets(buffer, 256, file);
        buffer[strlen(buffer) - 1] = '\0';
        flash_array[i]->vendor = strdup(buffer);
        fclose(file);
    }
}

void parse_proc_mounts(Flash** flash_array, int size) {

    FILE* file = fopen(MOUNTS_PATH, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int i = 0;
    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL && i < size) {
        char temp[MAX_LINE_LENGTH];
        char mount[MAX_LINE_LENGTH];
        
        if (sscanf(buffer, "%s %s %*s", temp, mount) == 2) {
            if (flash_array[i] != NULL && flash_array[i]->part != NULL) {
                if (strncmp(temp + 5, flash_array[i]->part, 3) == 0) {
                    flash_array[i]->mount = strdup(mount);
                    struct statvfs stat;
                    int ret = statvfs(mount, &stat);
                    if (ret == 0) {
                        flash_array[i]->available_size_mb = (long long int)(stat.f_bfree * stat.f_frsize) / 1024 / 1024;
                    }
                    i++;
                }
            }
        }
    }

    fclose(file);
}

char* readpart_by_id(const char* serial_number) {
    if (serial_number == NULL) {
        return NULL;
    }
    
    DIR *dir;
    struct dirent *entry;
    char link_target[MAX_PATH_LEN];
    char symlink_path[MAX_PATH_LEN];

    dir = opendir(DEV_PATH);
    if (dir == NULL) {
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_LNK) {
            snprintf(symlink_path, sizeof(symlink_path), "%s/%s", DEV_PATH, entry->d_name);
            ssize_t nbytes = readlink(symlink_path, link_target, MAX_PATH_LEN - 1);
            if (nbytes != -1) {
                link_target[nbytes] = '\0';
                
                char *pos = strstr(entry->d_name, serial_number);
                if (pos != NULL && strstr(symlink_path, "part") == NULL) {
                    closedir(dir);
                    return strdup(link_target);
                }
            }
        }
    }

    closedir(dir);
    return NULL;
}