#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "hub.h"
#include "descriptors.h"
#include "ncurses.h"

#define MAX_PATH_LEN 4096
#define MAX_FILENAME_LEN 512

#define DEVICES_PATH "/sys/bus/usb/devices"

Hub* create_hub() {
    Hub* hub = malloc(sizeof(Hub));
    if (hub == NULL) {
        printf("Failed to allocate memory for Hub");
        exit(EXIT_FAILURE);
    }
    
    hub->name = NULL;
    hub->manufacturer = NULL;
    hub->ports_amount = 0;
    hub->speed = 0;
    hub->bus = 0;
    hub->address = 0;
    hub->usb_version = 0.0f;
    hub->device_class = NULL;
    hub->device_subclass = NULL;
    hub->protocol = 0;
    hub->id_vendor = NULL;
    hub->id_product = NULL;
    hub->revision = NULL;
    hub->interfaces_amount = 0;
    hub->devices_amount = 0;
    hub->interfaces = NULL;
    hub->devices = NULL;

    return hub;
}


Hub** init_hub_array(int size) {
    Hub **hubs = malloc(size * sizeof(Hub*));

    if (hubs == NULL) {
        printf("Failed to allocate memory for Hub array");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        hubs[i] = create_hub();
    }

    return hubs;
}

int count_hubs(const char *path) {
    DIR* dir;
    struct dirent *entry;

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

        if (strncmp(entry->d_name, "usb", 3) == 0) {
            counter++;
    
        }
    }

    closedir(dir);

    return counter++;
}

void parse_hubs(Hub **hub_array, int size, const char *path) {
    DIR* dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        printf("Error opening %s path", path);
        exit(EXIT_FAILURE);
    }

    int hub_index = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        if (strncmp(entry->d_name, "usb", 3) == 0) {
            char full_path[MAX_PATH_LEN];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

            hub_array[hub_index]->name = read_descriptor(full_path, NAME_FILENAME);
            hub_array[hub_index]->manufacturer = read_descriptor(full_path, MANUFACTURER_FILENAME);
            hub_array[hub_index]->serial_number = read_descriptor(full_path, SERIAL_NUMBER_FILENAME);
            hub_array[hub_index]->ports_amount = atoi(read_descriptor(full_path, NUMBER_OF_PORTS_FILENAME));
            hub_array[hub_index]->speed = atoi(read_descriptor(full_path, SPEED_FILENAME));
            hub_array[hub_index]->bus = atoi(read_descriptor(full_path, BUS_FILENAME));
            hub_array[hub_index]->address = atoi(read_descriptor(full_path, DEVICE_NUMBER_FILENAME));
            hub_array[hub_index]->usb_version = atof(read_descriptor(full_path, USB_VERSION_FILENAME));
            hub_array[hub_index]->device_class = read_descriptor(full_path, DEVICE_CLASS_FILENAME);
            hub_array[hub_index]->device_subclass = read_descriptor(full_path, DEVICE_SUBCLASS_FILENAME);
            hub_array[hub_index]->protocol = atoi(read_descriptor(full_path, DEVICE_PROTOCOL_FILENAME));
            hub_array[hub_index]->max_endpoint_size = atoi(read_descriptor(full_path, MAX_ENDPOINT_SIZE_FILENAME));
            hub_array[hub_index]->id_vendor = read_descriptor(full_path, VENDOR_ID_FILENAME);
            hub_array[hub_index]->id_product = read_descriptor(full_path, PRODUCT_ID_FILENAME);
            hub_array[hub_index]->revision = read_descriptor(full_path, DEVICE_REVISION_FILENAME);
            hub_array[hub_index]->interfaces_amount = atoi(read_descriptor(full_path, NUMBER_OF_INTERFACES_FILENAME));
            hub_array[hub_index]->devices_amount = count_deivces(full_path);

            hub_array[hub_index]->interfaces = init_interface_array(hub_array[hub_index]->interfaces_amount);
            parse_interfaces(hub_array[hub_index]->interfaces, full_path);
    
            if (hub_array[hub_index]->devices_amount != 0) {
                hub_array[hub_index]->devices = init_device_array(hub_array[hub_index]->devices_amount);
                parse_devices(hub_array[hub_index]->devices, full_path);
            }

            hub_index++;
        }

        if (hub_index == size) {
            break;
        }
    }

    closedir(dir);
}

void print_hub_console(Hub *hub) {
    printf("Hub Name: %s\n", hub->name);
    printf("Manufacturer: %s\n", hub->manufacturer);
    printf("Bus: %d\n", hub->bus);
    printf("Serial Number: %s\n", hub->serial_number);
    printf("Ports Amount: %d\n", hub->ports_amount);
    printf("Speed: %dMbps\n", hub->speed);
    printf("Address: %d\n", hub->address);
    printf("USB Version: %.2f\n", hub->usb_version);
    printf("Device Class: %s\n", hub->device_class);
    printf("Device Subclass: %s\n", hub->device_subclass);
    printf("Protocol: %d\n", hub->protocol);
    printf("Max Endpoint Size: %d\n", hub->max_endpoint_size);
    printf("Vendor ID: %s\n", hub->id_vendor);
    printf("Product ID: %s\n", hub->id_product);
    printf("Revision: %s\n", hub->revision);
    printf("Number Of Interfaces: %d\n\n", hub->interfaces_amount);

    for (int i = 0; i < hub->interfaces_amount; i++) {
        printf("\tInterface Number: %d\n", hub->interfaces[i]->number);
        printf("\tName: %s\n", hub->interfaces[i]->name);
        printf("\tAlternate Number: %d\n", hub->interfaces[i]->alternate_number);
        printf("\tClass: %s\n", hub->interfaces[i]->device_class);
        printf("\tSubClass: %s\n", hub->interfaces[i]->device_subclass);
        printf("\tProtocol: %d\n\n", hub->interfaces[i]->protocol);
    }

    for (int i = 0; i < hub->devices_amount; i++) {
        printf("\t\tDevice Name: %s\n", hub->devices[i]->name);
        printf("\t\tManufacturer: %s\n", hub->devices[i]->manufacturer);
        printf("\t\tBus: %d\n", hub->devices[i]->bus);
        printf("\t\tSerial Number: %s\n", hub->devices[i]->serial_number);
        printf("\t\tSpeed: %dMbps\n", hub->devices[i]->speed);
        printf("\t\tAddress: %d\n", hub->devices[i]->address);
        printf("\t\tUSB Version: %.2f\n", hub->devices[i]->usb_version);
        printf("\t\tDevice Class: %s\n", hub->devices[i]->device_class);
        printf("\t\tDevice Subclass: %s\n", hub->devices[i]->device_subclass);
        printf("\t\tProtocol: %d\n", hub->devices[i]->protocol);
        printf("\t\tVendor ID: %s\n", hub->devices[i]->id_vendor);
        printf("\t\tProduct ID: %s\n", hub->devices[i]->id_product);
        printf("\t\tRevision: %s\n", hub->devices[i]->revision);
        printf("\t\tNumber Of Interfaces: %d\n\n", hub->devices[i]->interfaces_amount);

        for (int j = 0; j < hub->devices[i]->interfaces_amount; j++)  {
        printf("\t\t\tInterface Number: %d\n", hub->devices[i]->interfaces[j]->number);
        printf("\t\t\tName: %s\n", hub->devices[i]->interfaces[j]->name);
        printf("\t\t\tAlternate Number: %d\n", hub->devices[i]->interfaces[j]->alternate_number);
        printf("\t\t\tClass: %s\n", hub->devices[i]->interfaces[j]->device_class);
        printf("\t\t\tSubClass: %s\n", hub->devices[i]->interfaces[j]->device_subclass);
        printf("\t\t\tProtocol: %d\n\n", hub->devices[i]->interfaces[j]->protocol);
        }
    }
}

#include <ncurses.h>

void print_hub_ncurses(Hub *hubs[], int num_hubs) {
    // Инициализация ncurses
    initscr();
    start_color();
    // Определение цветовых пар
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // стандартный цвет
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // жёлтый для выделения
    // Установка стандартного цвета
    attron(COLOR_PAIR(1));

    // Цикл по всем переданным хабам
    for (int h = 0; h < num_hubs; h++) {
        Hub *hub = hubs[h];

        // Вывод информации о хабе
        printw("Hub Name: %s\n", hub->name);
        printw("Manufacturer: %s\n", hub->manufacturer);
        printw("Bus: %d\n", hub->bus);
        printw("Serial Number: %s\n", hub->serial_number);
        printw("Ports Amount: %d\n", hub->ports_amount);
        printw("Speed: %dMbps\n", hub->speed);
        printw("Address: %d\n", hub->address);
        printw("USB Version: %.2f\n", hub->usb_version);
        printw("Device Class: %s\n", hub->device_class);
        printw("Device Subclass: %s\n", hub->device_subclass);
        printw("Protocol: %d\n", hub->protocol);
        printw("Max Endpoint Size: %d\n", hub->max_endpoint_size);
        printw("Vendor ID: %s\n", hub->id_vendor);
        printw("Product ID: %s\n", hub->id_product);
        printw("Revision: %s\n", hub->revision);
        printw("Number Of Interfaces: %d\n\n", hub->interfaces_amount);

        // Вывод информации о каждом интерфейсе
        for (int i = 0; i < hub->interfaces_amount; i++) {
            printw("\tInterface Number: %d\n", hub->interfaces[i]->number);
            printw("\tName: %s\n", hub->interfaces[i]->name);
            printw("\tAlternate Number: %d\n", hub->interfaces[i]->alternate_number);
            printw("\tClass: %s\n", hub->interfaces[i]->device_class);
            printw("\tSubClass: %s\n", hub->interfaces[i]->device_subclass);
            printw("\tProtocol: %d\n\n", hub->interfaces[i]->protocol);
        }

        // Вывод информации о подключенных устройствах
        for (int i = 0; i < hub->devices_amount; i++) {
            printw("\t\tDevice Name: %s\n", hub->devices[i]->name);
            printw("\t\tManufacturer: %s\n", hub->devices[i]->manufacturer);
            printw("\t\tBus: %d\n", hub->devices[i]->bus);
            printw("\t\tSerial Number: %s\n", hub->devices[i]->serial_number);
            printw("\t\tSpeed: %dMbps\n", hub->devices[i]->speed);
            printw("\t\tAddress: %d\n", hub->devices[i]->address);
            printw("\t\tUSB Version: %.2f\n", hub->devices[i]->usb_version);
            printw("\t\tDevice Class: %s\n", hub->devices[i]->device_class);
            printw("\t\tDevice Subclass: %s\n", hub->devices[i]->device_subclass);
            printw("\t\tProtocol: %d\n", hub->devices[i]->protocol);
            printw("\t\tVendor ID: %s\n", hub->devices[i]->id_vendor);
            printw("\t\tProduct ID: %s\n", hub->devices[i]->id_product);
            printw("\t\tRevision: %s\n", hub->devices[i]->revision);
            printw("\t\tNumber Of Interfaces: %d\n\n", hub->devices[i]->interfaces_amount);

            // Вывод информации о каждом интерфейсе устройства
            for (int j = 0; j < hub->devices[i]->interfaces_amount; j++) {
                printw("\t\t\tInterface Number: %d\n", hub->devices[i]->interfaces[j]->number);
                printw("\t\t\tName: %s\n", hub->devices[i]->interfaces[j]->name);
                printw("\t\t\tAlternate Number: %d\n", hub->devices[i]->interfaces[j]->alternate_number);
                printw("\t\t\tClass: %s\n", hub->devices[i]->interfaces[j]->device_class);
                printw("\t\t\tSubClass: %s\n", hub->devices[i]->interfaces[j]->device_subclass);
                printw("\t\t\tProtocol: %d\n\n", hub->devices[i]->interfaces[j]->protocol);
            }
        }

        printw("Press any key to continue to the next hub...\n");
        refresh();
        int ch;
        // Добавим обработку специальных клавиш, чтобы избежать закрытия программы
        while ((ch = getch()) != ERR) {
            if (ch != KEY_RESIZE) {
                break;
            }
        }
        clear();
    }
    endwin();
}
