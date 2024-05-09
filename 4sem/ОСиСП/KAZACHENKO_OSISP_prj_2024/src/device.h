#ifndef DEVICE_H
#define DEVICE_H

#include "interface.h"

typedef struct {
    char* name;
    char* manufacturer;
    char* serial_number;
    int speed;
    int bus;
    int address;
    float usb_version;
    char* device_class;
    char* device_subclass;
    int protocol;
    int max_endpoint_size;
    char* id_vendor;
    char* id_product;
    char* revision;
    int interfaces_amount;
    Interface **interfaces;
} Device;

Device* create_device();
Device** init_device_array(int size);
void free_device(Device *device);
void free_device_array(Device **device_array, int size);

int count_deivces(const char* path);
void parse_devices(Device **device_array, const char* path);

#endif // DEVICE_H