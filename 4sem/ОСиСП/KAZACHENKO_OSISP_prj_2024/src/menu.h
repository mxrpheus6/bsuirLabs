#include <ncurses.h>
#include "hub.h"

int menu();
void print_hub_console_ncurses(Hub *hub, WINDOW *win);
void print_devices_info(Hub *hub, int current_device);
void print_interfaces_info(Device *device, int current_interface);
void print_help_interfaces(WINDOW *win);
void print_help_devices(WINDOW *win);
void print_help_hubs(WINDOW *win);