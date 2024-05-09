#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "descriptors.h"
#include "flash.h"
#include "flash_test.h"
#include "input_test.h"
#include "hub.h"
#include "menu.h"

#define MAX_PATH_LEN 4096
#define MAX_FILENAME_LEN 255

#define DEVICES_PATH "/sys/bus/usb/devices"
#define DEV_PATH "/dev/disk/by-id"

int menu() {
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE); 
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    

    int hub_array_size = count_hubs(DEVICES_PATH);
    Hub **hub_array = init_hub_array(hub_array_size);
    parse_hubs(hub_array, hub_array_size, DEVICES_PATH);

    int flash_array_size = count_flash("/proc/partitions");
    Flash** flash_array = init_flash_array(flash_array_size);
    parse_proc_partitions(flash_array, flash_array_size);
    parse_sys_block(flash_array, flash_array_size);
    parse_proc_mounts(flash_array, flash_array_size);

    int current_hub = 0;
    int current_device = 0;
    int max_hub = hub_array_size > 0 ? hub_array_size - 1 : 0;
    int viewing_devices = 0;

    printw("Hub %d/%d\n\n", current_hub + 1, hub_array_size);
    print_help_hubs(stdscr);
    print_hub_console_ncurses(hub_array[current_hub], stdscr);

    int ch;
    while ((ch = getch()) != 'q') {
        if (!viewing_devices) {
            if (ch == 'r') {
                free_hub_array(hub_array, hub_array_size);
                hub_array_size = count_hubs(DEVICES_PATH);
                hub_array = init_hub_array(hub_array_size);
                parse_hubs(hub_array, hub_array_size, DEVICES_PATH);

                free_flash_array(flash_array, flash_array_size);
                flash_array_size = count_flash("/proc/partitions");
                flash_array = init_flash_array(flash_array_size);
                parse_proc_partitions(flash_array, flash_array_size);
                parse_sys_block(flash_array, flash_array_size);
                parse_proc_mounts(flash_array, flash_array_size);
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
            } else if (ch == 'e') {
                if (hub_array[current_hub]->devices_amount > 0) {
                    clear();
                    print_devices_info(hub_array[current_hub], current_device);
                    refresh();
                    viewing_devices = 1;
                } else {
                    clear();
                    printw("No devices found in this hub.");
                    refresh();
                    getch();
                }
            }
        } else {
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
            } else if (ch == 'e') {
                viewing_devices = 0;
                current_device = 0;
            } else if (ch == 't') {
                print_flash_test_info(hub_array[current_hub]->devices[current_device], flash_array, flash_array_size);
                print_mouse_test_info(hub_array[current_hub]->devices[current_device]->name);
                print_keyboard_test_info(hub_array[current_hub]->devices[current_device]->name);
                refresh();
            } else if (ch == 'i') {
                if (hub_array[current_hub]->devices[current_device]->interfaces_amount > 0) {
                    int current_interface = 0;
                    print_interfaces_info(hub_array[current_hub]->devices[current_device], current_interface);
                    print_help_interfaces(stdscr);
                    int max_interface = hub_array[current_hub]->devices[current_device]->interfaces_amount - 1;
                    int exploring_interface = 1;

                    while (exploring_interface) {
                        ch = getch();
                        
                        if (ch == KEY_RIGHT) {
                            if (current_interface < max_interface)
                                current_interface++;
                            else
                                current_interface = 0;
                        } else if (ch == KEY_LEFT) {
                            if (current_interface > 0)
                                current_interface--;
                            else
                                current_interface = max_interface;
                        } else if (ch == 'e') {
                            exploring_interface = 0;
                        }
                        print_interfaces_info(hub_array[current_hub]->devices[current_device], current_interface);
                        print_help_interfaces(stdscr);
                    }
                    clear();
                    print_devices_info(hub_array[current_hub], current_device);
                    print_help_devices(stdscr);
                    refresh();
                } else {
                    clear();
                    printw("No interfaces found for this device.");
                    refresh();
                    getch();
                }
            }
        }

        clear();
        if (!viewing_devices) {
            printw("Hub %d/%d\n\n", current_hub + 1, hub_array_size);
            print_hub_console_ncurses(hub_array[current_hub], stdscr);
            print_help_hubs(stdscr);
        } else {
            print_devices_info(hub_array[current_hub], current_device);
            print_help_devices(stdscr);
        }
        refresh();
    }

    endwin();
    free_hub_array(hub_array, hub_array_size);
    return EXIT_SUCCESS;
}

void print_hub_console_ncurses(Hub *hub, WINDOW *win) {
    attron(A_BOLD);
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
    attroff(A_BOLD);
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

void print_interfaces_info(Device *device, int current_interface) {
    clear();
    mvprintw(0, 0, "Device Name: %s", device->name);
    mvprintw(1, 0, "Interface %d/%d\n", current_interface + 1, device->interfaces_amount);
    
    int row = 3;
    if (device->interfaces_amount > 0) {
        mvprintw(row++, 4, "Number: %d", device->interfaces[current_interface]->number);
        mvprintw(row++, 4, "Name: %s", device->interfaces[current_interface]->name);
        mvprintw(row++, 4, "Alternate Number: %d", device->interfaces[current_interface]->alternate_number);
        mvprintw(row++, 4, "Class: %s", device->interfaces[current_interface]->device_class);
        mvprintw(row++, 4, "Subclass: %s", device->interfaces[current_interface]->device_subclass);
        mvprintw(row++, 4, "Protocol: %d\n", device->interfaces[current_interface]->protocol);
    } else {
        mvprintw(row++, 2, "No interfaces found for this device.");
    }
    refresh();
}

void print_help_interfaces(WINDOW *win) {
    int row, col;
    getmaxyx(win, row, col);

    attron(A_REVERSE);
    mvprintw(row - 3, col / 2 - strlen("[ Interfaces ]") / 2, "[ Interfaces ]");
    attroff(A_REVERSE);

    wmove(win, row - 1, 0);
    attron(A_STANDOUT);
    wprintw(win, "<-/->");
    attroff(A_STANDOUT);
    wprintw(win, ": Scroll    ");
    attron(A_STANDOUT);
    wprintw(win, "E");
    attroff(A_STANDOUT);
    wprintw(win, ": Exit   ");
}

void print_help_devices(WINDOW *win) {
    int row, col;
    getmaxyx(win, row, col);

    attron(A_REVERSE);
    mvprintw(row - 3, col / 2 - strlen("[ Devices ]") / 2, "[ Devices ]");
    attroff(A_REVERSE);

    wmove(win, row - 1, 0);
    attron(A_STANDOUT);
    wprintw(win, "<-/->");
    attroff(A_STANDOUT);
    wprintw(win, ": Scroll    ");
    attron(A_STANDOUT);
    wprintw(win, "I");
    attroff(A_STANDOUT);
    wprintw(win, ": Interfaces   ");
    attron(A_STANDOUT);
    wprintw(win, "T");
    attroff(A_STANDOUT);
    wprintw(win, ": Test      ");
    attron(A_STANDOUT);
    wprintw(win, "Q");
    attroff(A_STANDOUT);
    wprintw(win, ": Quit      ");
    wrefresh(win);
}

void print_help_hubs(WINDOW *win) {
    int row, col;
    getmaxyx(win, row, col);

    attron(A_REVERSE);
    mvprintw(row - 3, col / 2 - strlen("[ Welcome to USBAssist! ]") / 2, "[ Welcome to USBAssist! ]");
    attroff(A_REVERSE);

    wmove(win, row - 1, 0);
    attron(A_STANDOUT);
    wprintw(win, "<-/->");
    attroff(A_STANDOUT);
    wprintw(win, ": Scroll    ");
    attron(A_STANDOUT);
    wprintw(win, "E");
    attroff(A_STANDOUT);
    wprintw(win, ": Explore   ");
    attron(A_STANDOUT);
    wprintw(win, "R");
    attroff(A_STANDOUT);
    wprintw(win, ": Refresh   ");
    attron(A_STANDOUT);
    wprintw(win, "Q");
    attroff(A_STANDOUT);
    wprintw(win, ": Quit      ");
    wrefresh(win);
}