#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <regex.h>

#include "device.h"
#include "descriptors.h"

#define MAX_PATH_LEN 4096

Device* create_device() {
    Device *device = malloc(sizeof(Device));
    if (device == NULL) {
        printf("Error malloc for device");
        exit(EXIT_FAILURE);
    }

    device->name = NULL;
    device->manufacturer = NULL;
    device->serial_number = NULL;
    device->speed = 0;
    device->bus = 0;
    device->address = 0;
    device->usb_version = 0.0f;
    device->device_class = NULL;
    device->device_subclass = NULL;
    device->protocol = 0;
    device->max_endpoint_size = 0;
    device->id_vendor = NULL;
    device->id_product = NULL;
    device->revision = NULL;
    device->interfaces_amount = 0;
    device->interfaces = NULL;

    return device;
}

Device** init_device_array(int size) {
    Device **devices = malloc(size * sizeof(Device*));

    for (int i = 0; i < size; i++) {
        devices[i] = create_device();
    }

    return devices;
}


int count_deivces(const char* path) {
    DIR *dir;
    struct dirent *entry;
    regex_t regex;
    const char *pattern = "[0-9]+-[0-9]+$";

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

void parse_devices(Device **device_array, const char* path) {
    DIR *dir;
    struct dirent *entry;
    regex_t regex;
    const char *pattern = "[0-9]+-[0-9]+$";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Failed to compile regular expression");
        exit(EXIT_FAILURE);
    }

    dir = opendir(path);
    if (dir == NULL) {
        printf("Error opening %s path", path);
        exit(EXIT_FAILURE);
    }

    int device_index = 0;
    while ((entry = readdir(dir)) != NULL) {

        if (regexec(&regex, entry->d_name, 0, NULL, 0) != 0) {
            continue;
        }

        char full_path[MAX_PATH_LEN];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        device_array[device_index]->name = read_descriptor(full_path, NAME_FILENAME);
        device_array[device_index]->manufacturer = read_descriptor(full_path, MANUFACTURER_FILENAME);
        device_array[device_index]->serial_number = read_descriptor(full_path, SERIAL_NUMBER_FILENAME);
        device_array[device_index]->speed = atoi(read_descriptor(full_path, SPEED_FILENAME));
        device_array[device_index]->bus = atoi(read_descriptor(full_path, BUS_FILENAME));
        device_array[device_index]->address = atoi(read_descriptor(full_path, DEVICE_NUMBER_FILENAME));
        device_array[device_index]->usb_version = atof(read_descriptor(full_path, USB_VERSION_FILENAME));
        device_array[device_index]->device_class = read_descriptor(full_path, DEVICE_CLASS_FILENAME);
        device_array[device_index]->device_subclass = read_descriptor(full_path, DEVICE_SUBCLASS_FILENAME);
        device_array[device_index]->protocol = atoi(read_descriptor(full_path, DEVICE_PROTOCOL_FILENAME));
        device_array[device_index]->max_endpoint_size = atoi(read_descriptor(full_path, MAX_ENDPOINT_SIZE_FILENAME));
        device_array[device_index]->id_vendor = read_descriptor(full_path, VENDOR_ID_FILENAME);
        device_array[device_index]->id_product = read_descriptor(full_path, PRODUCT_ID_FILENAME);
        device_array[device_index]->revision = read_descriptor(full_path, DEVICE_REVISION_FILENAME);
        device_array[device_index]->interfaces_amount = atoi(read_descriptor(full_path, NUMBER_OF_INTERFACES_FILENAME));
        
        device_array[device_index]->interfaces = init_interface_array(device_array[device_index]->interfaces_amount);
        parse_interfaces(device_array[device_index]->interfaces, full_path);

        device_index++;
    }

    closedir(dir);
    regfree(&regex);
}