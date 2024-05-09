#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE
#include "flash_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define KB 1024
#define MB (1024 * 1024)

#define TEST_FILE "test_file"
#define MAX_PATH_LEN 4096

void print_progress(WINDOW* win, int row, int col, char* message, double progress) {
    const int bar_width = 18;
    int pos = bar_width * progress;
    mvwprintw(win, row, col, "%s", message);
    mvwprintw(win, row, col + strlen(message) + 2, "[%*s]", bar_width, "");
    for (int i = 0; i < pos; ++i) {
        mvwprintw(win, row, col + strlen(message) + 2 + 1 + i, "=");
    }
    mvwprintw(win, row, col + strlen(message) + 2 + 1 + bar_width + 1, "  %.0f%%", progress * 100.0);
    wrefresh(win);
}

double test_usb_write_speed(WINDOW* win, const char* mount_path, int file_size) {
    char full_path[MAX_PATH_LEN];
    snprintf(full_path, sizeof(full_path), "%s/%s", mount_path, TEST_FILE);

    FILE* file = fopen(full_path, "wb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int fd = fileno(file);
    if (posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED) != 0) {
        perror("Error disabling file cache");
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[KB];
    memset(buffer, 1, KB);
    unsigned long long int bytes_written = 0;
    unsigned long long int bytes_to_write = file_size * MB;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    while (bytes_written < bytes_to_write) {
        fwrite(buffer, KB, 1, file);
        bytes_written += KB;
        fflush(file);

        double progress = (double)bytes_written / bytes_to_write;
        print_progress(win, 5, 2, "Writing:", progress);
    }

    fclose(file);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double total_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) /1000000000.0;

    return file_size / total_time;
}

double test_usb_read_speed(WINDOW* win, const char* mount_path, int file_size) {
    char full_path[MAX_PATH_LEN];
    snprintf(full_path, sizeof(full_path), "%s/%s", mount_path, TEST_FILE);

    FILE* file = fopen(full_path, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int fd = fileno(file);
    if (posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED) != 0) {
        perror("Error disabling file cache");
        exit(EXIT_FAILURE);
    }

    struct timespec start, end;
    unsigned char buffer[KB];
    unsigned long long int bytes_read = 0;
    unsigned long long int bytes_to_read = file_size * MB;
    clock_gettime(CLOCK_MONOTONIC, &start);
    while (bytes_read < bytes_to_read) {
        fread(buffer, KB, 1, file);
        bytes_read += KB;

        double progress = (double)bytes_read / bytes_to_read;
        print_progress(win, 6, 2, "Reading:", progress);
    }

    fclose(file);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double total_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) /1000000000.0;

    if (remove(full_path) != 0) {
        perror("Error deleting file");
    }

    return file_size / total_time;
}

int print_flash_test_info(Device* device, Flash** flash_array, int flash_array_size) {
    int is_usb_exist = 0;
    int flash_index;
    for (flash_index = 0; flash_index < flash_array_size; flash_index++) {
        char* this_part = readpart_by_id(device->serial_number);
        if (this_part == NULL) {
            break;
        }
        if (strstr(this_part, flash_array[flash_index]->part) != NULL) {
            is_usb_exist = 1;
            break;
        }
    }

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int win_height = 10;
    int win_width = 40;

    int starty = (max_y - win_height) / 2;
    int startx = (max_x - win_width) / 2;

    WINDOW* test_win = newwin(win_height, win_width, starty, startx);
    box(test_win, 0, 0);

    if (is_usb_exist == 0) {
        refresh();
        delwin(test_win);
        return 0;
    }

    mvwprintw(test_win, 1, 2, "Model: %s", flash_array[flash_index]->model);
    mvwprintw(test_win, 2, 2, "Vendor: %s", flash_array[flash_index]->vendor);
    mvwprintw(test_win, 3, 2, "Size (Mb): %d", flash_array[flash_index]->size_mb);
    mvwprintw(test_win, 4, 2, "Available size (Mb): %d", flash_array[flash_index]->available_size_mb);
    mvwprintw(test_win, 5, 2, "Part: %s", flash_array[flash_index]->part);
    mvwprintw(test_win, 6, 2, "Mount: %s", flash_array[flash_index]->mount);
    mvwprintw(test_win, 8, 2, "Start testing? [y/n]");
    
    wrefresh(test_win);

    int choice = wgetch(test_win);
    if (choice == 'y' || choice == 'Y') {
        werase(test_win);
        box(test_win, 0, 0);

        mvwprintw(test_win, 1, 2, "Test file sizes:");
        mvwprintw(test_win, 2, 2, "1. 16 MB");
        mvwprintw(test_win, 3, 2, "2. 128 MB");
        mvwprintw(test_win, 4, 2, "3. 512 MB");
        mvwprintw(test_win, 5, 2, "4. 1024 MB");
        mvwprintw(test_win, 6, 2, "5. 2048 MB");
        mvwprintw(test_win, 7, 2, "Choose file size (or 'e' to exit)");

        wrefresh(test_win);

        while(1) {
            choice = wgetch(test_win);
            test_file_sizes selected_size;
            switch (choice) {
                case '1':
                    selected_size = MB16;
                    if ((int)selected_size > flash_array[flash_index]->available_size_mb) {
                        mvwprintw(test_win, 8, 2, "Invalid choice!");
                        wrefresh(test_win);
                        continue;
                    }
                    break;
                case '2':
                    selected_size = MB128;
                    if ((int)selected_size > flash_array[flash_index]->available_size_mb) {
                        mvwprintw(test_win, 8, 2, "Selected size more than available");
                        wrefresh(test_win);
                        continue;
                    }
                    break;
                case '3':
                    selected_size = MB512;
                    if ((int)selected_size > flash_array[flash_index]->available_size_mb) {
                        mvwprintw(test_win, 8, 2, "Selected size more than available");
                        wrefresh(test_win);
                        continue;
                    }
                    break;
                case '4':
                    selected_size = MB1024;
                    if ((int)selected_size > flash_array[flash_index]->available_size_mb) {
                        mvwprintw(test_win, 8, 2, "Selected size more than available");
                        wrefresh(test_win);
                        continue;
                    }
                    break;
                case '5':
                    selected_size = MB2048;
                    if ((int)selected_size > flash_array[flash_index]->available_size_mb) {
                        mvwprintw(test_win, 8, 2, "Selected size more than available");
                        wrefresh(test_win);
                        continue;
                    }
                    break;
                case 'e':
                    delwin(test_win);
                    return 0;
                default:
                    mvwprintw(test_win, 8, 2, "Invalid choice!\t\t   ");
                    wrefresh(test_win);
                    continue;
            }
            werase(test_win);
            box(test_win, 0, 0);
            mvwprintw(test_win, 1, 2, "Selected test file size: %d Mb", selected_size);
            mvwprintw(test_win, 2, 2, "Test in process...");
            wrefresh(test_win);
            double write_speed = test_usb_write_speed(test_win, flash_array[flash_index]->mount, selected_size);
            double read_speed = test_usb_read_speed(test_win, flash_array[flash_index]->mount, selected_size);
            mvwprintw(test_win, 2, 2, "Success!\t\t");
            mvwprintw(test_win, 5, 2, "Write speed: %.2f Mb/s\t      ", write_speed);
            mvwprintw(test_win, 6, 2, "Read speed: %.2f Mb/s\t      ", read_speed);
            mvwprintw(test_win, 8, 2, "Press any button to exit");
            wrefresh(test_win);
            wgetch(test_win);
            break;
        }
    }
    delwin(test_win);
    return 1;
}