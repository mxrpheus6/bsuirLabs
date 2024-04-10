#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>
#include <ncurses.h>

#include "descriptors.h"
#include "hub.h"

#define MAX_PATH_LEN 4096
#define MAX_FILENAME_LEN 255

#define DEVICES_PATH "/sys/bus/usb/devices"

#define MAX_PAGES 10 // Максимальное количество страниц

void print_hub_console_ncurses(Hub *hub, WINDOW *win);
void print_devices_info(Hub *hub, int current_device);
void print_help(WINDOW *win);

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int hubs_count = count_hubs(DEVICES_PATH);
    Hub **hub_array = init_hub_array(hubs_count);

    parse_hubs(hub_array, hubs_count, DEVICES_PATH);

    int current_hub = 0;
    int current_device = 0;
    int max_hub = hubs_count > 0 ? hubs_count - 1 : 0;
    int viewing_devices = 0; // Флаг режима просмотра устройств

    int ch;
    while ((ch = getch()) != 'q') {
        if (!viewing_devices) {
            if (ch == 'r') {
                free_hub_array(hub_array, hubs_count);
                hubs_count = count_hubs(DEVICES_PATH);
                hub_array = init_hub_array(hubs_count);
                parse_hubs(hub_array, hubs_count, DEVICES_PATH);
            }
            if (ch == KEY_RIGHT) {
                if (current_hub < max_hub)
                    current_hub++;
                else
                    current_hub = 0;
            } else if (ch == KEY_LEFT) {
                if (current_hub > 0)
                    current_hub--;
                else
                    current_hub = max_hub;
            } else if (ch == '\n') {
                if (hub_array[current_hub]->devices_amount > 0) {
                    clear();
                    print_devices_info(hub_array[current_hub], current_device);
                    refresh();
                    viewing_devices = 1; // Вход в режим просмотра устройств
                } else {
                    clear();
                    printw("No devices found in this hub.");
                    refresh();
                    getch(); // Чтобы ожидать нажатия клавиши перед очисткой экрана
                }
            }
        } else { // Режим просмотра устройств
            if (ch == KEY_RIGHT) {
                if (current_device < hub_array[current_hub]->devices_amount - 1)
                    current_device++;
                else
                    current_device = 0;
            } else if (ch == KEY_LEFT) {
                if (current_device > 0)
                    current_device--;
                else
                    current_device = hub_array[current_hub]->devices_amount - 1;
            } else if (ch == '\n') {
                viewing_devices = 0; // Выход из режима просмотра устройств
            }
        }

        clear();
        if (!viewing_devices) {
            printw("Hub %d/%d\n\n", current_hub + 1, hubs_count);
            print_hub_console_ncurses(hub_array[current_hub], stdscr);
        } else {
            print_devices_info(hub_array[current_hub], current_device);
        }
        print_help(stdscr); // Вывод подсказки по клавишам
        refresh();
    }

    endwin();
    free(hub_array);
    return EXIT_SUCCESS;
}

void print_hub_console_ncurses(Hub *hub, WINDOW *win) {
    mvwprintw(win, 2, 2, "Hub Name: %s", hub->name);
    mvwprintw(win, 3, 2, "Manufacturer: %s", hub->manufacturer);
    mvwprintw(win, 4, 2, "Bus: %d", hub->bus);
    mvwprintw(win, 5, 2, "Serial Number: %s", hub->serial_number);
    mvwprintw(win, 6, 2, "Ports Amount: %d", hub->ports_amount);
    mvwprintw(win, 7, 2, "Speed: %d Mbps", hub->speed);
    mvwprintw(win, 8, 2, "Address: %d", hub->address);
    mvwprintw(win, 9, 2, "USB Version: %.2f", hub->usb_version);
    mvwprintw(win, 10, 2, "Device Class: %s", hub->device_class);
    mvwprintw(win, 11, 2, "Device Subclass: %s", hub->device_subclass);
    mvwprintw(win, 12, 2, "Protocol: %d", hub->protocol);
    mvwprintw(win, 13, 2, "Max Endpoint Size: %d", hub->max_endpoint_size);
    mvwprintw(win, 14, 2, "Vendor ID: %s", hub->id_vendor);
    mvwprintw(win, 15, 2, "Product ID: %s", hub->id_product);
    mvwprintw(win, 16, 2, "Revision: %s", hub->revision);
    mvwprintw(win, 17, 2, "Interfaces Amount: %d", hub->interfaces_amount);
    mvwprintw(win, 18, 2, "Devices Amount: %d", hub->devices_amount);
    wrefresh(win);
}

void print_devices_info(Hub *hub, int current_device) {
    clear();
    mvprintw(0, 0, "Hub Name: %s", hub->name);
    mvprintw(1, 0, "Device %d/%d\n", current_device + 1, hub->devices_amount);
    
    int row = 3;
    if (hub->devices_amount > 0) {
        mvprintw(row++, 2, "Device Name: %s", hub->devices[current_device]->name);
        mvprintw(row++, 2, "Manufacturer: %s", hub->devices[current_device]->manufacturer);
        mvprintw(row++, 2, "Bus: %d", hub->devices[current_device]->bus);
        mvprintw(row++, 2, "Serial Number: %s", hub->devices[current_device]->serial_number);
        mvprintw(row++, 2, "Speed: %dMbps", hub->devices[current_device]->speed);
        mvprintw(row++, 2, "Address: %d", hub->devices[current_device]->address);
        mvprintw(row++, 2, "USB Version: %.2f", hub->devices[current_device]->usb_version);
        mvprintw(row++, 2, "Device Class: %s", hub->devices[current_device]->device_class);
        mvprintw(row++, 2, "Device Subclass: %s", hub->devices[current_device]->device_subclass);
        mvprintw(row++, 2, "Protocol: %d", hub->devices[current_device]->protocol);
        mvprintw(row++, 2, "Vendor ID: %s", hub->devices[current_device]->id_vendor);
        mvprintw(row++, 2, "Product ID: %s", hub->devices[current_device]->id_product);
        mvprintw(row++, 2, "Revision: %s", hub->devices[current_device]->revision);
        mvprintw(row++, 2, "Number Of Interfaces: %d\n", hub->devices[current_device]->interfaces_amount);
    } else {
        mvprintw(row++, 2, "No devices found in this hub.");
    }

    refresh();
}

void print_help(WINDOW *win) {
    int row, col;
    getmaxyx(win, row, col);
    attron(A_REVERSE);
    mvprintw(row - 3, col / 2 - strlen("[ Welcome to USBAssist! ]") / 2, "[ Welcome to USBAssist! ]");
    mvprintw(row - 2, col / 2 - strlen("Enter: Show Devices") / 2, "Enter");
    attroff(A_REVERSE);
    printw(": Show Devices");
    attron(A_REVERSE);
    mvprintw(row - 1, col / 2 - strlen("Q: Exit   R: Refresh") / 2, "Q");
    attroff(A_REVERSE);
    printw(": Exit   ");
    attron(A_REVERSE);
    mvprintw(row - 1, col / 2 - strlen("Refr") / 2, "R");
    attroff(A_REVERSE);
    printw(": Refresh");
    attroff(A_REVERSE);
}

