#include "device.h"

typedef struct {    
    char* name;
    char* manufacturer;
    char* serial_number;
    int ports_amount;
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
    int devices_amount;
    Interface **interfaces;
    Device **devices;
} Hub;

Hub* create_hub();
Hub** init_hub_array(int size);

void parse_hubs(Hub **hub_array, int size, const char *path);
void print_hub_console(Hub *hub);
void print_hub_ncurses(Hub *hubs[], int num_hubs);
int count_hubs(const char *path);