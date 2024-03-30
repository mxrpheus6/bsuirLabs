#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

#include "descriptors.h"

#include "hub.h"

#define MAX_PATH_LEN 4096
#define MAX_FILENAME_LEN 255

#define DEVICES_PATH "/sys/bus/usb/devices"

int main() {
    int hubs_count = count_hubs(DEVICES_PATH);
    Hub **hub_array = init_hub_array(hubs_count);

    parse_hubs(hub_array, hubs_count, DEVICES_PATH);

    for (int i = 0; i < hubs_count; i++) {
        print_hub_console(hub_array[i]);
    }
    //print_hub_ncurses(hub_array, hubs_count);
    
    free(hub_array);

    return EXIT_SUCCESS;
}