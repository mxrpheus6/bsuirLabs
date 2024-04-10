#include "flash_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KB 1024
#define MB 1024 * 1000

void create_test_file(const char* filename, long long int file_size) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    char byte;
    for (long long int i = 0; i < file_size; i++) {
        byte = rand() % 256;
        fwrite(&byte, sizeof(char), 1, file);
    }

    fclose(file);
}

double test_usb_write_speed(const char* usb_path, const char* test_file_path) {
    FILE* test_file = fopen(test_file_path, "rb");
    if (!test_file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    FILE* usb_drive = fopen(usb_path, "wb");
    if (!usb_drive) {
        perror("Error opening USB drive file");
        exit(EXIT_FAILURE);
    }


    fseek(test_file, 0, SEEK_END);
    int file_size = 16 * MB;
    rewind(test_file);

    char buffer[16 * MB];

    fread(buffer, sizeof(char), 16 * MB, test_file);

    clock_t start_time = clock();
    fwrite(buffer, sizeof(char), 16 * MB, usb_drive);
    clock_t end_time = clock();
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    fclose(test_file);
    fclose(usb_drive);

    return file_size / total_time / MB;
}

double test_usb_read_speed(const char* usb_path, const char* test_file_path) {
    FILE* test_file = fopen(test_file_path, "rb");
    if (!test_file) {
        perror("Error opening test file");
        exit(EXIT_FAILURE);
    }
    
    FILE* usb_drive = fopen(usb_path, "rb");
    if (!usb_drive) {
        perror("Error opening USB drive file");
        exit(EXIT_FAILURE);
    }

    char buffer[16 * MB];

    clock_t start_time = clock();
    fread(buffer, sizeof(char), 16 * MB, usb_drive);
    clock_t end_time = clock();
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    double average_speed = (16 * MB) / total_time / MB;

    fclose(test_file);
    fclose(usb_drive);

    return average_speed;
}