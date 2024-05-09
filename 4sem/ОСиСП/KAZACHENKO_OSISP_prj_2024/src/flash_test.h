#ifndef FLASH_TEST_H
#define FLASH_TEST_H

#include <stddef.h>
#include <stdio.h>
#include <ncurses.h>
#include "device.h"
#include "flash.h"

typedef enum test_file_sizes {
    MB16 = 16,
    MB128 = 128,
    MB512 = 512,
    MB1024 = 1024,
    MB2048 = 2048
} test_file_sizes;

double test_usb_write_speed(WINDOW* win, const char* mount_path, int file_size);
double test_usb_read_speed(WINDOW* win, const char* mount_path, int file_size);

int print_flash_test_info(Device* device, Flash** flash_array, int flash_array_size);

#endif // FLASH_TEST_H